#include <iostream>
#include <string>
#include <optional>

class Car {
private:
    std::string brand;
    std::string model;
    int year;
    std::string color;
    int horsepower;

    Car(const std::string& brand, const std::string& model, int year, const std::string& color, int horsepower)
        : brand(brand), model(model), year(year), color(color), horsepower(horsepower) {
    }

public:
    class Builder;

    void showDetails() const {
        std::cout << "Car Details:\n"
            << "Brand: " << brand << "\n"
            << "Model: " << model << "\n"
            << "Year: " << year << "\n"
            << "Color: " << color << "\n"
            << "Horsepower: " << horsepower << " HP\n";
    }
};

class Car::Builder {
private:
    std::string brand;
    std::string model;
    int year = 2023;              
    std::string color = "Black"; 
    int horsepower = 150;        

public:
    Builder& setBrand(const std::string& carBrand) {
        brand = carBrand;
        return *this;
    }

    Builder& setModel(const std::string& carModel) {
        model = carModel;
        return *this;
    }

    Builder& setYear(int carYear) {
        year = carYear;
        return *this;
    }

    Builder& setColor(const std::string& carColor) {
        color = carColor;
        return *this;
    }

    Builder& setHorsepower(int carHorsepower) {
        horsepower = carHorsepower;
        return *this;
    }

    Car build() {
        if (brand.empty() || model.empty()) {
            throw std::runtime_error("Brand and Model are mandatory fields!");
        }
        return Car(brand, model, year, color, horsepower);
    }
};

int main() {
    try {
        Car car = Car::Builder()
            .setBrand("Toyota")
            .setModel("Camry")
            .setYear(2021)
            .setColor("White")
            .setHorsepower(200)
            .build();

        car.showDetails();

        Car defaultCar = Car::Builder()
            .setBrand("Tesla")
            .setModel("Model 3")
            .build();

        defaultCar.showDetails();
    }
    catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
    }

    return 0;
}