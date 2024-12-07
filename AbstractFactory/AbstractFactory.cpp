#include <iostream>
#include <memory>
#include <string>

class Chair {
public:
    virtual void sitOn() const = 0; 
    virtual ~Chair() = default;
};

class Table {
public:
    virtual void use() const = 0; 
    virtual ~Table() = default;
};

class ModernChair : public Chair {
public:
    void sitOn() const override {
        std::cout << "Sitting on a modern chair." << std::endl;
    }
};

class ModernTable : public Table {
public:
    void use() const override {
        std::cout << "Using a modern table." << std::endl;
    }
};

class ClassicChair : public Chair {
public:
    void sitOn() const override {
        std::cout << "Sitting on a classic chair." << std::endl;
    }
};

class ClassicTable : public Table {
public:
    void use() const override {
        std::cout << "Using a classic table." << std::endl;
    }
};

class FurnitureFactory {
public:
    virtual std::unique_ptr<Chair> createChair() const = 0; 
    virtual std::unique_ptr<Table> createTable() const = 0; 
    virtual ~FurnitureFactory() = default;
};

class ModernFurnitureFactory : public FurnitureFactory {
public:
    std::unique_ptr<Chair> createChair() const override {
        return std::make_unique<ModernChair>();
    }

    std::unique_ptr<Table> createTable() const override {
        return std::make_unique<ModernTable>();
    }
};

class ClassicFurnitureFactory : public FurnitureFactory {
public:
    std::unique_ptr<Chair> createChair() const override {
        return std::make_unique<ClassicChair>();
    }

    std::unique_ptr<Table> createTable() const override {
        return std::make_unique<ClassicTable>();
    }
};

class Room {
private:
    std::unique_ptr<Chair> chair;
    std::unique_ptr<Table> table;

public:
    Room(const FurnitureFactory& factory) {
        chair = factory.createChair();
        table = factory.createTable();
    }

    void furnish() const {
        chair->sitOn();
        table->use();
    }
};

int main() {
    std::cout << "Modern Room:" << std::endl;
    ModernFurnitureFactory modernFactory;
    Room modernRoom(modernFactory);
    modernRoom.furnish();

    std::cout << "\nClassic Room:" << std::endl;
    ClassicFurnitureFactory classicFactory;
    Room classicRoom(classicFactory);
    classicRoom.furnish();

    return 0;
}