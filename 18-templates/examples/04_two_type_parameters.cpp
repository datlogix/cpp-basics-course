// A template can have more than one type parameter - this is exactly
// std::map<K, V>'s own shape.
#include <iostream>
#include <string>

template <typename K, typename V>
class KeyValue {
private:
    K key;
    V value;

public:
    KeyValue(K k, V v) : key(k), value(v) {}

    void print() {
        std::cout << key << ": " << value << std::endl;
    }
};

int main() {
    KeyValue<std::string, double> reading("R1", 220.0);
    reading.print();

    KeyValue<int, std::string> idToName(1, "Ama");
    idToName.print();

    return 0;
}
