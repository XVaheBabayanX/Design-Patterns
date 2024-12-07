# Factory Method
---
**Creational Design Pattern** 
---

#### **1. Базовый продукт (`Transport`)**
```cpp
class Transport {
public:
    virtual void deliver() const = 0; // Чисто виртуальный метод, реализуемый в подклассах
    virtual ~Transport() = default;
};
```
- Абстрактный класс, представляющий общий интерфейс для всех видов транспорта.
- Определяет метод `deliver()`, который должны реализовать конкретные продукты.

---

#### **2. Конкретные продукты**
```cpp
class Truck : public Transport {
public:
    void deliver() const override {
        std::cout << "Delivering goods by land in a truck." << std::endl;
    }
};

class Ship : public Transport {
public:
    void deliver() const override {
        std::cout << "Delivering goods by sea in a ship." << std::endl;
    }
};
```
- `Truck` и `Ship` реализуют метод `deliver()`, каждый по-своему.

---

#### **3. Создатель (Фабрика)**
```cpp
class Logistics {
public:
    virtual std::unique_ptr<Transport> createTransport() const = 0; // Чисто виртуальный фабричный метод
    virtual ~Logistics() = default;

    void planDelivery() const {
        auto transport = createTransport(); // Создание продукта через фабричный метод
        transport->deliver();               // Использование продукта
    }
};
```
- Абстрактный класс, который определяет интерфейс для фабричного метода `createTransport()`.
- Метод `planDelivery()` демонстрирует использование создаваемого объекта.

---

#### **4. Конкретные создатели**
```cpp
class RoadLogistics : public Logistics {
public:
    std::unique_ptr<Transport> createTransport() const override {
        return std::make_unique<Truck>();
    }
};

class SeaLogistics : public Logistics {
public:
    std::unique_ptr<Transport> createTransport() const override {
        return std::make_unique<Ship>();
    }
};
```
- `RoadLogistics` и `SeaLogistics` реализуют фабричный метод `createTransport()` для создания соответствующих продуктов.

---

#### **5. Использование в `main()`**
```cpp
int main() {
    std::cout << "Road Logistics:" << std::endl;
    std::unique_ptr<Logistics> roadLogistics = std::make_unique<RoadLogistics>();
    roadLogistics->planDelivery();

    std::cout << "\nSea Logistics:" << std::endl;
    std::unique_ptr<Logistics> seaLogistics = std::make_unique<SeaLogistics>();
    seaLogistics->planDelivery();

    return 0;
}
```
- Мы создаём экземпляры `RoadLogistics` и `SeaLogistics`.
- Вызываем `planDelivery()`, чтобы увидеть, как создаются и используются разные виды транспорта.

---

### **Результат выполнения**
```
Road Logistics:
Delivering goods by land in a truck.

Sea Logistics:
Delivering goods by sea in a ship.
```

---

### **Преимущества Factory Method**
1. **Расширяемость**: Легко добавить новые продукты и создателей без изменения существующего кода.
2. **Разделение обязанностей**: Создание и использование объектов разделены.
3. **Гибкость**: Позволяет создавать разные продукты, используя один и тот же интерфейс.

---