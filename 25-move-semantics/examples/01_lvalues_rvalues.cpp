// lvalues (things with names) vs rvalues (temporaries).
// Overloading on const T& and T&& shows which category each argument is:
// the compiler picks the && version ONLY for rvalues.
#include <iostream>
#include <string>

void describe(const std::string& s) {
    std::cout << "  lvalue (has a name):      \"" << s << "\"" << std::endl;
}

void describe(std::string&& s) {
    std::cout << "  rvalue (a temporary):     \"" << s << "\"" << std::endl;
}

std::string makeName() {
    return "Kwame Nkrumah";
}

int main() {
    std::string first = "Yaa";
    std::string last = "Asantewaa";

    describe(first);               // a variable - lvalue
    describe(first + " " + last);  // the result of + is a temporary - rvalue
    describe(makeName());          // a returned value - rvalue
    describe(std::string("Ghana")); // an unnamed object - rvalue

    // An rvalue reference VARIABLE has a name - so using it is an lvalue!
    std::string&& ref = makeName();
    describe(ref);                 // lvalue (surprising, but it has a name)

    return 0;
}
