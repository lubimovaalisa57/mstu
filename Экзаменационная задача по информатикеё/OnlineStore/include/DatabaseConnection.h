#ifndef DATABASECONNECTION_H
#define DATABASECONNECTION_H

#include <iostream>
#include <vector>
#include <memory>
#include <pqxx/pqxx>

template<typename T>
class DatabaseConnection {
private:
    std::unique_ptr<pqxx::connection> conn;

public:
    DatabaseConnection(const std::string& connection_string) {
        try {
            conn = std::make_unique<pqxx::connection>(connection_string);
            if (conn->is_open()) {
                std::cout << "Connected to database\n";
            }
        } catch (const std::exception &e) {
            std::cerr << "Connection error: " << e.what() << std::endl;
        }
    }

    ~DatabaseConnection() {
        if (conn && conn->is_open()) {
            conn->close();
        }
    }

    std::vector<std::vector<std::string>> executeQuery(const std::string& query) {
        std::vector<std::vector<std::string>> result;
        try {
            pqxx::work txn(*conn);
            pqxx::result res = txn.exec(query);

            for (const auto& row : res) {
                std::vector<std::string> row_data;
                for (const auto& field : row) {
                    row_data.push_back(field.c_str());
                }
                result.push_back(row_data);
            }
            txn.commit();
        } catch (const std::exception &e) {
            std::cerr << "Query error: " << e.what() << std::endl;
        }
        return result;
    }

    void executeNonQuery(const std::string& query) {
        try {
            pqxx::work txn(*conn);
            txn.exec(query);
            txn.commit();
        } catch (const std::exception &e) {
            std::cerr << "Non-query error: " << e.what() << std::endl;
            throw;
        }
    }

    void beginTransaction() {
        try {
            pqxx::work txn(*conn);
            txn.exec("BEGIN");
            txn.commit();
        } catch (const std::exception &e) {
            std::cerr << "Begin transaction error: " << e.what() << std::endl;
        }
    }

    void commitTransaction() {
        try {
            pqxx::work txn(*conn);
            txn.exec("COMMIT");
            txn.commit();
        } catch (const std::exception &e) {
            std::cerr << "Commit transaction error: " << e.what() << std::endl;
        }
    }

    void rollbackTransaction() {
        try {
            pqxx::work txn(*conn);
            txn.exec("ROLLBACK");
            txn.commit();
        } catch (const std::exception &e) {
            std::cerr << "Rollback transaction error: " << e.what() << std::endl;
        }
    }

    void createFunction(const std::string& function_sql) {
        executeNonQuery(function_sql);
    }

    void createTrigger(const std::string& trigger_sql) {
        executeNonQuery(trigger_sql);
    }

    std::string getTransactionStatus() {
        try {
            auto result = executeQuery("SELECT current_setting('transaction_isolation')");
            if (!result.empty()) {
                return result[0][0];
            }
        } catch (...) {}
        return "unknown";
    }

    bool isConnected() const {
        return conn && conn->is_open();
    }
};

#endif