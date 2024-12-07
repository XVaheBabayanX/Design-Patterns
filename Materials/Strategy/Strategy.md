# Strategy
---
**Behavioral Design Pattern** 
---

### Объяснение кода

#### 1. **Strategy (Интерфейс стратегии):**
```cpp
class PaymentStrategy {
public:
    virtual void pay(int amount) = 0;
    virtual ~PaymentStrategy() {}
};
```
- Определяет общий интерфейс `pay` для всех стратегий оплаты.
- Класс-клиент (`ShoppingCart`) взаимодействует с этим интерфейсом, а не с конкретными реализациями.

---

#### 2. **Concrete Strategies (Реализации стратегий):**

##### **CreditCardPayment:**
```cpp
class CreditCardPayment : public PaymentStrategy {
private:
    std::string cardNumber;
    std::string cardHolderName;

public:
    CreditCardPayment(const std::string& number, const std::string& name)
        : cardNumber(number), cardHolderName(name) {}

    void pay(int amount) override {
        std::cout << "Paid $" << amount << " using Credit Card ("
                  << "Card Holder: " << cardHolderName << ", Card Number: " << cardNumber << ")." << std::endl;
    }
};
```
- Реализует метод `pay` для оплаты кредитной картой.
- Содержит данные о карте: номер и имя владельца.

##### **PayPalPayment:**
```cpp
class PayPalPayment : public PaymentStrategy {
private:
    std::string email;

public:
    PayPalPayment(const std::string& emailAddress) : email(emailAddress) {}

    void pay(int amount) override {
        std::cout << "Paid $" << amount << " using PayPal (Email: " << email << ")." << std::endl;
    }
};
```
- Реализует метод `pay` для оплаты через PayPal.
- Хранит электронную почту для входа в PayPal.

---

#### 3. **Context (Контекст):**
```cpp
class ShoppingCart {
private:
    std::unique_ptr<PaymentStrategy> paymentStrategy;

public:
    void setPaymentStrategy(std::unique_ptr<PaymentStrategy> strategy) {
        paymentStrategy = std::move(strategy);
    }

    void checkout(int amount) {
        if (!paymentStrategy) {
            std::cout << "No payment method selected!" << std::endl;
            return;
        }
        paymentStrategy->pay(amount);
    }
};
```
- Контекст, управляющий объектами стратегий:
  - Метод `setPaymentStrategy` позволяет задавать текущую стратегию оплаты.
  - Метод `checkout` вызывает метод `pay` выбранной стратегии для выполнения платежа.
- Использование `std::unique_ptr` обеспечивает автоматическое управление памятью.

---

#### 4. **Client Code (Клиентский код):**
```cpp
int main() {
    ShoppingCart cart;

    // Use Credit Card Payment
    cart.setPaymentStrategy(std::make_unique<CreditCardPayment>("1234-5678-9012-3456", "Vahe"));
    cart.checkout(250);

    // Use PayPal Payment
    cart.setPaymentStrategy(std::make_unique<PayPalPayment>("vahe@example.com"));
    cart.checkout(150);

    return 0;
}
```
- В клиентском коде создаются разные стратегии (`CreditCardPayment` и `PayPalPayment`) и задаются в корзину (`ShoppingCart`) перед выполнением платежа.
- Это позволяет гибко менять способ оплаты без изменения логики корзины.

---

### Вывод программы:
```
Paid $250 using Credit Card (Card Holder: Vahe, Card Number: 1234-5678-9012-3456).
Paid $150 using PayPal (Email: vahe@example.com).
```

---

### Преимущества паттерна **Strategy**

1. **Инкапсуляция алгоритмов:** Каждая стратегия реализует свой способ выполнения задачи.
2. **Простая смена алгоритма:** Вы можете менять стратегии во время выполнения программы.
3. **Открытость для расширения:** Добавление новой стратегии не требует изменения существующего кода.

### Когда использовать:
- Когда у вас есть несколько вариантов выполнения одной задачи.
- Когда нужно избегать множества `if-else` или `switch-case` для выбора поведения.