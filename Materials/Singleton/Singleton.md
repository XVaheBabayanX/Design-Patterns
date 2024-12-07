# Singleton
---
**Creational Design Pattern** 
---
### **1. Eager Singleton**

#### Код:
```cpp
class EagerSingleton {
private:
    static EagerSingleton instance; // Объект создаётся сразу при запуске программы.

    EagerSingleton() {
        std::cout << "EagerSingleton is created!" << std::endl;
    }

    EagerSingleton(const EagerSingleton&) = delete;
    EagerSingleton& operator=(const EagerSingleton&) = delete;

public:
    static EagerSingleton& getInstance() {
        return instance;
    }

    void showMessage() {
        std::cout << "Hello from Vahe's EagerSingleton!" << std::endl;
    }
};

EagerSingleton EagerSingleton::instance; // Инициализация объекта.
```

#### Принцип работы:
- Объект **создаётся сразу при загрузке программы**, ещё до первого запроса к `getInstance()`.

#### Преимущества:
1. Простота реализации.
2. Объект гарантированно создан до любого обращения.

#### Недостатки:
1. Даже если объект никогда не используется, он всё равно будет создан, что может расходовать память и ресурсы.
2. Не подходит для случаев, где создание объекта зависит от контекста (например, конфигурации).

#### Когда использовать:
- Если объект **должен быть всегда доступен** и его создание занимает мало времени.
- Когда важно, чтобы объект был инициализирован заранее, до выполнения основного кода.

---

### **2. Lazy Singleton**

#### Код:
```cpp
class LazySingleton {
private:
    static LazySingleton* instance; // Указатель на объект.
    static std::mutex mtx;          // Мьютекс для потокобезопасности.

    LazySingleton() {
        std::cout << "LazySingleton is created!" << std::endl;
    }

    LazySingleton(const LazySingleton&) = delete;
    LazySingleton& operator=(const LazySingleton&) = delete;

public:
    static LazySingleton* getInstance() {
        if (instance == nullptr) {
            std::lock_guard<std::mutex> lock(mtx); // Потокобезопасность.
            if (instance == nullptr) {
                instance = new LazySingleton(); // Создание объекта при первом обращении.
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
```

#### Принцип работы:
- Объект создаётся **только при первом вызове** метода `getInstance()`.
- Используется двойная проверка `if (instance == nullptr)` для повышения производительности.

#### Преимущества:
1. Экономия ресурсов: объект создаётся только при необходимости.
2. Потокобезопасность (за счёт мьютекса).

#### Недостатки:
1. Более сложная реализация из-за необходимости обеспечить потокобезопасность.
2. Небольшая задержка при первом создании объекта.

#### Когда использовать:
- Когда объект может **никогда не понадобиться**, а его создание ресурсоёмко.
- Когда важно, чтобы объект создавался **только в определённых ситуациях**.

---

### **3. Meyers Singleton**

#### Код:
```cpp
class MeyersSingleton {
public:
    static MeyersSingleton& getInstance() {
        static MeyersSingleton instance; // Локальная статическая переменная, потокобезопасная.
        return instance;
    }

    void showMessage() {
        std::cout << "Hello from Vahe's MeyersSingleton!" << std::endl;
    }

private:
    MeyersSingleton() {
        std::cout << "MeyersSingleton is created!" << std::endl;
    }

    MeyersSingleton(const MeyersSingleton&) = delete;
    MeyersSingleton& operator=(const MeyersSingleton&) = delete;
};
```

#### Принцип работы:
- Используется локальная статическая переменная (`static`), которая создаётся при первом вызове `getInstance()` и автоматически освобождается при завершении программы.

#### Преимущества:
1. Очень простая и компактная реализация.
2. Потокобезопасность гарантируется стандартом C++11.
3. Автоматическое управление временем жизни объекта.

#### Недостатки:
- Может быть сложнее контролировать момент создания объекта в более сложных сценариях.

#### Когда использовать:
- Почти всегда, если нужна простая и надёжная реализация Singleton.
- Если проект использует стандарт C++11 или выше.

---

### **Сравнение и выбор Singleton**

| Функция                | **Eager Singleton**           | **Lazy Singleton**               | **Meyers Singleton**            |
|------------------------|------------------------------|----------------------------------|---------------------------------|
| **Создание объекта**    | При загрузке программы       | При первом обращении            | При первом обращении            |
| **Потокобезопасность**  | Автоматическая              | Требуется реализовать вручную    | Гарантирована стандартом C++11  |
| **Простота реализации** | Средняя                     | Сложная (из-за мьютексов)        | Очень простая                   |
| **Ресурсоёмкость**      | Высокая (даже если не используется) | Низкая                          | Низкая                          |
| **Когда использовать**  | Объект всегда нужен         | Объект используется не всегда   | Универсальное решение           |

---

### Итоги:

1. **Используй Eager Singleton**, если объект всегда нужен и должен быть готов заранее. Пример: управление логированием.
2. **Используй Lazy Singleton**, если объект создаётся редко и создание ресурсоёмкое. Пример: доступ к базе данных.
3. **Используй Meyers Singleton** для большинства случаев. Пример: глобальные настройки приложения.