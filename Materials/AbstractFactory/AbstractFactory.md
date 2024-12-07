# Abstract Factory
---
**Creational Design Pattern** 
---

#### **1. Абстрактные продукты**
```cpp
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
```
- Абстрактные классы, представляющие общий интерфейс для конкретных продуктов (`Chair` и `Table`).
- Задают контракт для действий, которые должны реализовываться в конкретных продуктах.

---

#### **2. Конкретные продукты**
```cpp
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
```
- Реализации для стульев (`Chair`) и столов (`Table`), отличающиеся стилем (современные или классические).

---

#### **3. Абстрактная фабрика**
```cpp
class FurnitureFactory {
public:
    virtual std::unique_ptr<Chair> createChair() const = 0;
    virtual std::unique_ptr<Table> createTable() const = 0;
    virtual ~FurnitureFactory() = default;
};
```
- Интерфейс фабрики, определяющий методы для создания объектов (`Chair` и `Table`).

---

#### **4. Конкретные фабрики**
```cpp
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
```
- `ModernFurnitureFactory` создаёт современные стулья и столы.
- `ClassicFurnitureFactory` создаёт классические стулья и столы.

---

#### **5. Клиентский код**
```cpp
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
```
- Класс `Room` использует фабрику для создания объектов мебели, не завися от конкретного типа мебели.

---

#### **6. Использование в `main()`**
```cpp
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
```
- Создаём две фабрики: `ModernFurnitureFactory` и `ClassicFurnitureFactory`.
- Используем их для обстановки комнат.

---

### **Результат выполнения**
```
Modern Room:
Sitting on a modern chair.
Using a modern table.

Classic Room:
Sitting on a classic chair.
Using a classic table.
```

---

### **Преимущества Abstract Factory**
1. **Разделение кода**: Клиентский код не зависит от конкретных классов.
2. **Единый стиль продуктов**: Все продукты создаются в едином стиле (например, современные или классические).
3. **Гибкость**: Легко добавить новые семейства продуктов.