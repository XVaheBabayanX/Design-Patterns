#include <iostream>
#include <string>
#include <vector>
#include <memory>

class Observer {
public:
    virtual void update(const std::string& message) = 0;
    virtual ~Observer() {}
};

class Subject {
public:
    virtual void attach(std::shared_ptr<Observer> observer) = 0;
    virtual void detach(std::shared_ptr<Observer> observer) = 0;
    virtual void notify() = 0;
    virtual ~Subject() {}
};

class NewsPublisher : public Subject {
private:
    std::vector<std::shared_ptr<Observer>> observers;
    std::string latestNews;

public:
    void attach(std::shared_ptr<Observer> observer) override {
        observers.push_back(observer);
    }

    void detach(std::shared_ptr<Observer> observer) override {
        observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
    }

    void notify() override {
        for (const auto& observer : observers) {
            observer->update(latestNews);
        }
    }

    void setNews(const std::string& news) {
        latestNews = news;
        notify();
    }
};

class EmailSubscriber : public Observer {
private:
    std::string email;

public:
    explicit EmailSubscriber(const std::string& emailAddress) : email(emailAddress) {}

    void update(const std::string& message) override {
        std::cout << "Email sent to " << email << ": " << message << std::endl;
    }
};

class SMSSubscriber : public Observer {
private:
    std::string phoneNumber;

public:
    explicit SMSSubscriber(const std::string& phone) : phoneNumber(phone) {}

    void update(const std::string& message) override {
        std::cout << "SMS sent to " << phoneNumber << ": " << message << std::endl;
    }
};

int main() {
    auto newsPublisher = std::make_shared<NewsPublisher>();

    auto emailSubscriber = std::make_shared<EmailSubscriber>("vahe@example.com");
    auto smsSubscriber = std::make_shared<SMSSubscriber>("+123456789");

    newsPublisher->attach(emailSubscriber);
    newsPublisher->attach(smsSubscriber);

    newsPublisher->setNews("Breaking News: Observer Pattern in Action!");

    newsPublisher->detach(smsSubscriber);
    newsPublisher->setNews("Update: Only email subscribers receive this.");

    return 0;
}