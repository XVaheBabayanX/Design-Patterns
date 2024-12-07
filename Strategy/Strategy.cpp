#include <iostream>
#include <memory>
#include <string>

class PaymentStrategy {
public:
    virtual void pay(int amount) = 0;
    virtual ~PaymentStrategy() {}
};

class CreditCardPayment : public PaymentStrategy {
private:
    std::string cardNumber;
    std::string cardHolderName;

public:
    CreditCardPayment(const std::string& number, const std::string& name)
        : cardNumber(number), cardHolderName(name) {
    }

    void pay(int amount) override {
        std::cout << "Paid $" << amount << " using Credit Card ("
            << "Card Holder: " << cardHolderName << ", Card Number: " << cardNumber << ")." << std::endl;
    }
};

class PayPalPayment : public PaymentStrategy {
private:
    std::string email;

public:
    PayPalPayment(const std::string& emailAddress) : email(emailAddress) {}

    void pay(int amount) override {
        std::cout << "Paid $" << amount << " using PayPal (Email: " << email << ")." << std::endl;
    }
};

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

int main() {
    ShoppingCart cart;

    cart.setPaymentStrategy(std::make_unique<CreditCardPayment>("1234-5678-9012-3456", "Vahe"));
    cart.checkout(250);

    cart.setPaymentStrategy(std::make_unique<PayPalPayment>("vahe@example.com"));
    cart.checkout(150);

    return 0;
}