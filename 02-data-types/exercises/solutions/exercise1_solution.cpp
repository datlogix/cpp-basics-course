#include <iostream>
#include <string>

int main() {
    int itemCount = 3;
    double pricePerItem = 4.50;
    double totalPrice = itemCount * pricePerItem;
    std::cout << "Total price: " << totalPrice << std::endl;

    char firstInitial = 'D';
    std::cout << "First initial: " << firstInitial << std::endl;

    bool isOnSale = false;
    std::cout << "On sale: " << isOnSale << std::endl;

    std::string storeName = "Makers Place";
    std::cout << "Welcome to " << storeName << "!" << std::endl;

    return 0;
}
