#include <iostream>
//using namespace std;
int main()
{
    const int size = 10;
    int array[size];
    for (int i = 0; i < size; i++) {
    std::cout << "Введите элемент " << i + 1 << ": ";
    std::cin >> array[i];
    std::cout<<array[i]<<std::endl;
}   
    for (int i = 0; i < size; i++) {
    std::cout<<array[i]<<' ';
}
    std::cout<<std::endl;
    int sum=0;
    for (int i = 0; i < size; i++) {
    sum += array[i];
    }
    std::cout << "Сумма всех элементов массива: " << sum << std::endl;

    int maxElement = array[0]; 
    for (int i = 1; i < size; i++) {
    if (array[i] > maxElement) {
    maxElement = array[i]; 
}
}
std::cout << "Максимальный элемент массива: " << maxElement << std::endl;

    void bubbleSort(int array[],int size); {
    for (int i = 0; i < size - 1; i++) {
    for (int j = 0; j < size - i - 1; j++) {
    if (array[j] < array[j + 1]) {
    int temp = array[j];
    array[j] = array[j + 1];
    array[j + 1] = temp;
}
}
}
}
 for (int i = 0; i < size; i++) {
    std::cout<<array[i]<<' ';
 }
 std::cout<<std::endl;
    return 0;
}