#include <iostream>
#include <string>
#include <vector>

struct Book {
    std::string title;
    std::string author;
    int year;
};

int main() {
    std::vector<int> temperatures = {21, 25, 19, 30, 22};

    int sum = 0;
    int highest = temperatures[0];
    int lowest = temperatures[0];

    for (int t : temperatures) {
        sum += t;
        if (t > highest) highest = t;
        if (t < lowest) lowest = t;
    }

    double average = static_cast<double>(sum) / temperatures.size();

    std::cout << "Sum: " << sum << std::endl;
    std::cout << "Average: " << average << std::endl;
    std::cout << "Highest: " << highest << std::endl;
    std::cout << "Lowest: " << lowest << std::endl;

    std::vector<Book> library;
    library.push_back({"Things Fall Apart", "Chinua Achebe", 1958});
    library.push_back({"Homegoing", "Yaa Gyasi", 2016});
    library.push_back({"Changes", "Ama Ata Aidoo", 1991});

    for (Book b : library) {
        std::cout << b.title << " by " << b.author << " (" << b.year << ")" << std::endl;
    }

    return 0;
}
