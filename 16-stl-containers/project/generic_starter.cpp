// Module 16 Project - Track A: Inventory Tracker
// See project/README.md for requirements.
#include <iostream>
#include <map>
#include <string>

int main() {
    const int RESTOCK_THRESHOLD = 5;
    std::map<std::string, int> inventory;

    int choice;
    do {
        std::cout << std::endl;
        std::cout << "1. Add item" << std::endl;
        std::cout << "2. Restock item" << std::endl;
        std::cout << "3. Sell item" << std::endl;
        std::cout << "4. Print inventory" << std::endl;
        std::cout << "5. Print low-stock items" << std::endl;
        std::cout << "6. Exit" << std::endl;
        std::cout << "Choose an option: ";
        std::cin >> choice;

        std::string name;
        int amount;

        switch (choice) {
            case 1:
                // TODO: read name and starting quantity, add to inventory.
                break;
            case 2:
                // TODO: read name and amount, increase inventory[name].
                break;
            case 3:
                // TODO: read name and amount, decrease inventory[name],
                // never below 0.
                break;
            case 4:
                // TODO: print every item and quantity (sorted by name for free).
                break;
            case 5:
                // TODO: print every item with quantity < RESTOCK_THRESHOLD.
                break;
            case 6:
                std::cout << "Goodbye!" << std::endl;
                break;
            default:
                std::cout << "Invalid option." << std::endl;
        }
    } while (choice != 6);

    return 0;
}
