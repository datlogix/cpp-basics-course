// Multiple inheritance: a Smartphone IS-A Camera and IS-A Phone.
// Bases are constructed in the order LISTED, and destroyed in reverse.
// A name found in both bases is ambiguous until you say which one.
#include <iostream>
#include <string>

class Camera {
protected:
    int photosTaken = 0;

public:
    Camera() { std::cout << "  [+] Camera part" << std::endl; }
    virtual ~Camera() { std::cout << "  [-] Camera part" << std::endl; }
    void takePhoto() { photosTaken++; std::cout << "  click! (" << photosTaken << " photos)" << std::endl; }
    std::string status() const { return std::to_string(photosTaken) + " photos"; }
};

class Phone {
protected:
    int callsMade = 0;

public:
    Phone() { std::cout << "  [+] Phone part" << std::endl; }
    virtual ~Phone() { std::cout << "  [-] Phone part" << std::endl; }
    void call(std::string number) { callsMade++; std::cout << "  calling " << number << std::endl; }
    std::string status() const { return std::to_string(callsMade) + " calls"; }
};

class Smartphone : public Camera, public Phone {
public:
    Smartphone() { std::cout << "  [+] Smartphone" << std::endl; }
    ~Smartphone() override { std::cout << "  [-] Smartphone" << std::endl; }

    void sharePhoto(std::string number) {
        takePhoto(); // from Camera
        call(number); // from Phone
    }

    // Resolve the ambiguity properly: decide what status() means for a Smartphone.
    std::string status() const { return Camera::status() + ", " + Phone::status(); }
};

void usePhone(Phone& p) { p.call("0302 000 111"); }
void useCamera(Camera& c) { c.takePhoto(); }

int main() {
    std::cout << "Construction:" << std::endl;
    {
        Smartphone s;
        s.sharePhoto("0244 123 456");
        usePhone(s);  // a Smartphone can be used as a Phone...
        useCamera(s); // ...and as a Camera

        std::cout << "  Camera::status(): " << s.Camera::status() << std::endl; // qualified call
        std::cout << "  Smartphone::status(): " << s.status() << std::endl;
        std::cout << "Destruction:" << std::endl;
    }
    return 0;
}
