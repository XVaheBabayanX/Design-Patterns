#include <iostream>
#include <memory>
#include <string>

class Image {
public:
    virtual void display() const = 0;
    virtual ~Image() {}
};

class RealImage : public Image {
private:
    std::string filename;

    void loadFromDisk() const {
        std::cout << "Loading image from disk: " << filename << std::endl;
    }

public:
    explicit RealImage(const std::string& file) : filename(file) {
        loadFromDisk();
    }

    void display() const override {
        std::cout << "Displaying image: " << filename << std::endl;
    }
};

class ProxyImage : public Image {
private:
    std::string filename;
    mutable std::shared_ptr<RealImage> realImage;

public:
    explicit ProxyImage(const std::string& file) : filename(file), realImage(nullptr) {}

    void display() const override {
        if (!realImage) {
            realImage = std::make_shared<RealImage>(filename); 
        }
        realImage->display();
    }
};

int main() {
    std::shared_ptr<Image> image = std::make_shared<ProxyImage>("example.jpg");
    std::cout << "Image created, but not loaded yet.\n";
    image->display();
    image->display();

    return 0;
}