#include <iostream>
#include <memory>
#include <string>

class Transport {
public:
    virtual void deliver() const = 0;
    virtual ~Transport() = default;
};

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

class Logistics {
public:
    virtual std::unique_ptr<Transport> createTransport() const = 0;
    virtual ~Logistics() = default;

    void planDelivery() const {
        auto transport = createTransport();
        transport->deliver();
    }
};

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

int main() {
    std::cout << "Road Logistics:" << std::endl;
    std::unique_ptr<Logistics> roadLogistics = std::make_unique<RoadLogistics>();
    roadLogistics->planDelivery();

    std::cout << "\nSea Logistics:" << std::endl;
    std::unique_ptr<Logistics> seaLogistics = std::make_unique<SeaLogistics>();
    seaLogistics->planDelivery();

    return 0;
}