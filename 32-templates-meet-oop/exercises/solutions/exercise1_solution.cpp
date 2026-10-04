#include <concepts>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

class Student {
private:
    std::string id;
    std::string name;
    double average;

public:
    Student(std::string i, std::string n, double avg) : id(i), name(n), average(avg) {}
    std::string getId() const { return id; }
    std::string getName() const { return name; }
    double getAverage() const { return average; }
};

class Book {
private:
    std::string isbn;
    std::string title;
    bool borrowed = false;

public:
    Book(std::string i, std::string t) : isbn(i), title(t) {}
    std::string getId() const { return isbn; }
    std::string getTitle() const { return title; }
    bool isBorrowed() const { return borrowed; }
    void borrow() { borrowed = true; }
};

template <typename T>
concept HasId = requires(const T& item) {
    { item.getId() } -> std::convertible_to<std::string>;
};

template <HasId T, int MaxItems>
class Repository {
private:
    std::vector<T> items;

public:
    void add(const T& item);
    T* find(const std::string& id);
    bool remove(const std::string& id);
    int size() const;

    template <typename Predicate>
    int countIf(Predicate p) const {
        int count = 0;
        for (const T& item : items) {
            if (p(item)) {
                count++;
            }
        }
        return count;
    }
};

template <HasId T, int MaxItems>
void Repository<T, MaxItems>::add(const T& item) {
    if (find(item.getId()) != nullptr) {
        throw std::invalid_argument("duplicate ID " + item.getId());
    }
    if (size() >= MaxItems) {
        throw std::length_error("repository is full (" + std::to_string(MaxItems) + " items)");
    }
    items.push_back(item);
}

template <HasId T, int MaxItems>
T* Repository<T, MaxItems>::find(const std::string& id) {
    for (T& item : items) {
        if (item.getId() == id) {
            return &item;
        }
    }
    return nullptr;
}

template <HasId T, int MaxItems>
bool Repository<T, MaxItems>::remove(const std::string& id) {
    for (size_t i = 0; i < items.size(); i++) {
        if (items[i].getId() == id) {
            items.erase(items.begin() + i);
            return true;
        }
    }
    return false;
}

template <HasId T, int MaxItems>
int Repository<T, MaxItems>::size() const {
    return static_cast<int>(items.size());
}

int main() {
    Repository<Student, 3> roboticsClub;
    roboticsClub.add(Student("MP-001", "Ama", 84));
    roboticsClub.add(Student("MP-002", "Kojo", 71));

    try {
        roboticsClub.add(Student("MP-001", "Ama again", 84));
    } catch (const std::invalid_argument& e) {
        std::cout << "Refused: " << e.what() << std::endl;
    }

    roboticsClub.add(Student("MP-003", "Esi", 92));
    try {
        roboticsClub.add(Student("MP-004", "Yaw", 66));
    } catch (const std::length_error& e) {
        std::cout << "Refused: " << e.what() << std::endl;
    }

    if (Student* s = roboticsClub.find("MP-003")) {
        std::cout << "Found " << s->getName() << std::endl;
    }
    int strong = roboticsClub.countIf([](const Student& s) { return s.getAverage() >= 80; });
    std::cout << strong << " of " << roboticsClub.size() << " members average 80+" << std::endl;

    roboticsClub.remove("MP-002");
    std::cout << "After removing MP-002: " << roboticsClub.size() << " members" << std::endl;

    Repository<Book, 10> library;
    library.add(Book("978-0385474542", "Things Fall Apart"));
    library.add(Book("978-0582642218", "Anowa"));
    library.find("978-0582642218")->borrow();
    int out = library.countIf([](const Book& b) { return b.isBorrowed(); });
    std::cout << out << " of " << library.size() << " books on loan" << std::endl;

    // Repository<int, 5> numbers;
    //   error: template constraint failure for 'template<class T, int MaxItems>
    //          requires HasId<T> class Repository'
    //   note: the required expression 'item.getId()' is invalid
    return 0;
}
