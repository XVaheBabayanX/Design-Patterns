#include <iostream>

class EagerSingleton {
private:
    static EagerSingleton instance;

    EagerSingleton() {
        std::cout << "EagerSingleton is created!" << std::endl;
    }

    EagerSingleton(const EagerSingleton&) = delete;
    EagerSingleton& operator=(const EagerSingleton&) = delete;

public:
    static EagerSingleton& getInstance() {
        return instance;
    }

    void showMessage() {
        std::cout << "Hello from Vahe's EagerSingleton!" << std::endl;
    }
};

EagerSingleton EagerSingleton::instance;

int main() {
    EagerSingleton& s1 = EagerSingleton::getInstance();
    s1.showMessage();

    EagerSingleton& s2 = EagerSingleton::getInstance();
    s2.showMessage();

    if (&s1 == &s2) {
        std::cout << "Both pointers point to the same instance!" << std::endl;
    }

    return 0;
}