#include "../include/Customer.h"
#include "../include/PaymentStrategy.h"
#include <iostream>
#include <iomanip>
#include <memory>

Customer::Customer(int id, std::string n, std::string e,
                   std::shared_ptr<DatabaseConnection<std::string>> database)
    : User(id, std::move(n), std::move(e), "customer", database),
      current_order_id(-1) {}

void Customer::showMenu() {
    std::cout << "\nМеню покупателя:\n";
    std::cout << "1. Создать заказ\n";
    std::cout << "2. Добавить товар в заказ\n";
    std::cout << "3. Удалить товар из заказа\n";
    std::cout << "4. Мои заказы\n";
    std::cout << "5. Статус заказа\n";
    std::cout << "6. Оплатить заказ\n";
    std::cout << "7. Вернуть заказ\n";
    std::cout << "8. История статусов\n";
    std::cout << "0. Выход\n";
    std::cout << "Выбор: ";
}

void Customer::performAction(int choice) {
    switch(choice) {
        case 1: createOrder(); break;
        case 2: addToOrder(); break;
        case 3: removeFromOrder(); break;
        case 4: viewMyOrders(); break;
        case 5: viewOrderStatusCustomer(); break;
        case 6: makePayment(); break;
        case 7: returnOrder(); break;
        case 8: {
            std::cout << "Введите ID заказа: ";
            int order_id;
            std::cin >> order_id;
            viewOrderStatusHistory(order_id);
            break;
        }
        default:
            std::cout << "Неверный выбор\n";
    }
}

void Customer::createOrder() {
    std::cout << "\nСоздание заказа\n";

    std::string query = "INSERT INTO orders (user_id, status, total_price) VALUES (" +
                       std::to_string(user_id) + ", 'pending', 0) RETURNING order_id";

    try {
        db->beginTransaction();
        auto result = db->executeQuery(query);
        db->commitTransaction();

        if (!result.empty() && !result[0].empty()) {
            current_order_id = std::stoi(result[0][0]);
            std::cout << "Заказ создан. ID: " << current_order_id << "\n";
            logAudit("order", current_order_id, "create");
        }
    } catch (const std::exception& e) {
        db->rollbackTransaction();
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }
}

void Customer::addToOrder() {
    if (current_order_id == -1) {
        std::cout << "Сначала создайте заказ\n";
        return;
    }

    std::cout << "\nДобавление товара в заказ\n";
    displayProducts();

    std::cout << "Введите ID продукта: ";
    int product_id;
    std::cin >> product_id;

    std::cout << "Введите количество: ";
    int quantity;
    std::cin >> quantity;

    std::string query = "INSERT INTO order_items (order_id, product_id, quantity, price) "
                       "SELECT " + std::to_string(current_order_id) + ", " +
                       std::to_string(product_id) + ", " +
                       std::to_string(quantity) + ", price "
                       "FROM products WHERE product_id = " + std::to_string(product_id);

    try {
        db->beginTransaction();
        db->executeNonQuery(query);

        query = "UPDATE orders SET total_price = ("
                "SELECT SUM(quantity * price) FROM order_items "
                "WHERE order_id = " + std::to_string(current_order_id) +
                ") WHERE order_id = " + std::to_string(current_order_id);

        db->executeNonQuery(query);
        logAudit("order", current_order_id, "update");
        db->commitTransaction();

        std::cout << "Товар добавлен\n";
        displayCart(current_order_id);

    } catch (const std::exception& e) {
        db->rollbackTransaction();
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }
}

void Customer::removeFromOrder() {
    if (current_order_id == -1) {
        std::cout << "Нет активного заказа\n";
        return;
    }

    std::cout << "\nУдаление товара из заказа\n";
    displayCart(current_order_id);

    std::cout << "Введите ID продукта для удаления: ";
    int product_id;
    std::cin >> product_id;

    try {
        std::string query = "DELETE FROM order_items WHERE order_id = " +
                           std::to_string(current_order_id) +
                           " AND product_id = " + std::to_string(product_id);

        db->beginTransaction();
        db->executeNonQuery(query);

        query = "UPDATE orders SET total_price = ("
                "SELECT COALESCE(SUM(quantity * price), 0) FROM order_items "
                "WHERE order_id = " + std::to_string(current_order_id) +
                ") WHERE order_id = " + std::to_string(current_order_id);

        db->executeNonQuery(query);
        logAudit("order", current_order_id, "update");
        db->commitTransaction();

        std::cout << "Товар удален\n";
        displayCart(current_order_id);

    } catch (const std::exception& e) {
        db->rollbackTransaction();
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }
}

void Customer::viewMyOrders() {
    std::cout << "\nМои заказы:\n";

    std::string query = "SELECT order_id, status, total_price, order_date FROM orders "
                       "WHERE user_id = " + std::to_string(user_id) +
                       " ORDER BY order_date DESC";

    auto result = db->executeQuery(query);

    if (result.empty()) {
        std::cout << "Заказов нет\n";
        return;
    }

    std::cout << "ID  | Статус       | Сумма   | Дата\n";
    std::cout << "----|--------------|---------|----------------\n";

    for (const auto& row : result) {
        std::cout << std::setw(4) << row[0] << " | "
                  << std::setw(12) << row[1] << " | "
                  << std::setw(7) << row[2] << " | "
                  << row[3] << "\n";
    }
}

void Customer::makePayment() {
    if (current_order_id == -1) {
        std::cout << "Нет активного заказа\n";
        return;
    }

    std::string check_query = "SELECT status, total_price FROM orders WHERE order_id = " +
                             std::to_string(current_order_id);
    auto result = db->executeQuery(check_query);

    if (result.empty()) {
        std::cout << "Заказ не найден\n";
        return;
    }

    std::string status = result[0][0];
    double amount = std::stod(result[0][1]);

    if (status != "pending") {
        std::cout << "Заказ уже не в ожидании. Статус: " << status << "\n";
        return;
    }

    std::cout << "\nОплата заказа\n";
    std::cout << "Сумма к оплате: " << amount << "\n";
    std::cout << "Выберите способ оплаты:\n";
    std::cout << "1. Банковская карта\n";
    std::cout << "2. Электронный кошелек\n";
    std::cout << "3. СБП\n";
    std::cout << "0. Отмена\n";
    std::cout << "Выбор: ";

    int choice;
    std::cin >> choice;

    std::unique_ptr<PaymentStrategy> strategy;

    switch(choice) {
        case 1:
            strategy = std::make_unique<CreditCardPayment>();
            break;
        case 2:
            strategy = std::make_unique<EWalletPayment>();
            break;
        case 3:
            strategy = std::make_unique<SBPPayment>();
            break;
        case 0:
            std::cout << "Отмена\n";
            return;
        default:
            std::cout << "Неверный выбор\n";
            return;
    }

    std::cout << "Обработка платежа...\n";

    if (strategy->pay(amount)) {
        std::string query = "UPDATE orders SET status = 'processing' WHERE order_id = " +
                           std::to_string(current_order_id);

        try {
            db->beginTransaction();
            db->executeNonQuery(query);

            query = "INSERT INTO payments (order_id, amount, payment_method, payment_status) "
                    "VALUES (" + std::to_string(current_order_id) + ", " +
                    std::to_string(amount) + ", '" + strategy->getName() + "', 'completed')";

            db->executeNonQuery(query);
            logAudit("order", current_order_id, "payment");
            db->commitTransaction();

            std::cout << "Оплата успешна\n";
            current_order_id = -1;
        } catch (const std::exception& e) {
            db->rollbackTransaction();
            std::cerr << "Ошибка: " << e.what() << std::endl;
        }
    } else {
        std::cout << "Ошибка оплаты\n";
    }
}

void Customer::returnOrder() {
    std::cout << "\nВозврат заказа\n";

    std::string query = "SELECT order_id, total_price, order_date FROM orders "
                       "WHERE user_id = " + std::to_string(user_id) +
                       " AND status = 'completed' "
                       "ORDER BY order_date DESC";

    auto orders = db->executeQuery(query);

    if (orders.empty()) {
        std::cout << "Нет завершенных заказов\n";
        return;
    }

    std::cout << "Завершенные заказы:\n";
    for (const auto& order : orders) {
        std::cout << "ID: " << order[0] << ", Сумма: " << order[1]
                  << ", Дата: " << order[2] << "\n";
    }

    std::cout << "Введите ID заказа: ";
    int order_id;
    std::cin >> order_id;

    try {
        std::string query = "UPDATE orders SET status = 'returned' WHERE order_id = " +
                           std::to_string(order_id) + " AND user_id = " + std::to_string(user_id);

        db->beginTransaction();
        db->executeNonQuery(query);
        logAudit("order", order_id, "return");
        db->commitTransaction();

        std::cout << "Заявка на возврат отправлена\n";

    } catch (const std::exception& e) {
        db->rollbackTransaction();
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }
}

void Customer::viewOrderStatusCustomer() {
    if (current_order_id == -1) {
        std::cout << "Нет активного заказа\n";
        return;
    }

    viewOrderStatus(current_order_id);
}

void Customer::displayProducts() {
    std::cout << "\nДоступные товары:\n";

    auto result = db->executeQuery("SELECT product_id, name, price, stock_quantity FROM products WHERE stock_quantity > 0");

    if (result.empty()) {
        std::cout << "Товаров нет\n";
        return;
    }

    for (const auto& row : result) {
        std::cout << "ID: " << row[0] << ", " << row[1]
                  << ", Цена: " << row[2] << ", На складе: " << row[3] << "\n";
    }
}

void Customer::displayCart(int order_id) {
    std::cout << "\nКорзина заказа " << order_id << ":\n";

    std::string query = "SELECT p.name, oi.quantity, oi.price, (oi.quantity * oi.price) as total "
                       "FROM order_items oi "
                       "JOIN products p ON oi.product_id = p.product_id "
                       "WHERE oi.order_id = " + std::to_string(order_id);

    auto items = db->executeQuery(query);

    if (items.empty()) {
        std::cout << "Корзина пуста\n";
        return;
    }

    double total = 0;
    for (const auto& item : items) {
        double item_total = std::stod(item[3]);
        total += item_total;
        std::cout << item[0] << " x" << item[1] << " по " << item[2] << " = " << item_total << "\n";
    }

    std::cout << "Итого: " << total << "\n";
}