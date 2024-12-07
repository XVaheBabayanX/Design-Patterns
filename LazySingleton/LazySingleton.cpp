#include <iostream>
#include <mutex>

class LazySingleton {
private:
    static LazySingleton* instance;
    static std::mutex mtx;

    LazySingleton() {
        std::cout << "LazySingleton is created!" << std::endl;
    }

    LazySingleton(const LazySingleton&) = delete;
    LazySingleton& operator=(const LazySingleton&) = delete;

public:
    static LazySingleton* getInstance() {
        if (instance == nullptr) {
            std::lock_guard<std::mutex> lock(mtx);
            if (instance == nullptr) {
                instance = new LazySingleton();
            }
        }
        return instance;
    }

    void showMessage() {
        std::cout << "Hello from Vahe's LazySingleton!" << std::endl;
    }
};

LazySingleton* LazySingleton::instance = nullptr;
std::mutex LazySingleton::mtx;

int main() {
    LazySingleton* s1 = LazySingleton::getInstance();
    s1->showMessage();

    LazySingleton* s2 = LazySingleton::getInstance();
    s2->showMessage();

    if (s1 == s2) {
        std::cout << "Both pointers point to the same instance!" << std::endl;
    }

    return 0;
}