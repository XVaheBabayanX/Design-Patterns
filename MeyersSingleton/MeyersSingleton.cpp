#include <iostream>

class MeyersSingleton {
public:
    static MeyersSingleton& getInstance() {
        static MeyersSingleton instance;
        return instance;
    }

    void showMessage() {
        std::cout << "Hello from Vahe's MeyersSingleton!" << std::endl;
    }

private:
    MeyersSingleton() {
        std::cout << "MeyersSingleton is created!" << std::endl;
    }

    MeyersSingleton(const MeyersSingleton&) = delete;
    MeyersSingleton& operator=(const MeyersSingleton&) = delete;
};

int main() {
    MeyersSingleton& s1 = MeyersSingleton::getInstance();
    s1.showMessage();

    MeyersSingleton& s2 = MeyersSingleton::getInstance();
    s2.showMessage();

    if (&s1 == &s2) {
        std::cout << "Both pointers point to the same instance!" << std::endl;
    }

    return 0;
}