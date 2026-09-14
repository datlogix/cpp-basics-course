// struct: group different types together under one name.
// A vector of structs is one of the most useful patterns you'll ever use.
#include <iostream>
#include <string>
#include <vector>

struct Student {
    std::string name;
    int age;
    double gpa;
};

int main() {
    Student s1;
    s1.name = "Kofi";
    s1.age = 20;
    s1.gpa = 3.7;

    std::cout << s1.name << " is " << s1.age << " with GPA " << s1.gpa << std::endl;

    std::vector<Student> classroom;
    classroom.push_back(s1);

    Student s2;
    s2.name = "Ama";
    s2.age = 19;
    s2.gpa = 3.9;
    classroom.push_back(s2);

    std::cout << "-- classroom --" << std::endl;
    for (Student s : classroom) {
        std::cout << s.name << ": " << s.gpa << std::endl;
    }

    return 0;
}
