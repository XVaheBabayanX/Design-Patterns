# Builder
---
**Creational Design Pattern** 
---

### **Объяснение кода**

1. **Класс `Car`:**
   - Содержит поля, представляющие свойства автомобиля (бренд, модель, год, цвет и мощность).
   - Конструктор приватный, что позволяет создавать объект только через `Builder`.
   - Вложенный класс `Builder` объявлен как friend, чтобы он имел доступ к приватному конструктору.

2. **Класс `Builder`:**
   - Упрощает создание объектов `Car`, предоставляя методы для настройки каждого параметра.
   - Методы `setBrand`, `setModel` и т.д. возвращают ссылку на самого себя (`*this`), что позволяет использовать цепочку вызовов (method chaining).
   - Метод `build()` проверяет обязательные параметры (`brand` и `model`) и создаёт объект `Car`.

3. **Клиентский код:**
   - Использует `Car::Builder` для настройки объекта. Параметры можно задавать в любом порядке, что делает код более читаемым.
   - Значения по умолчанию используются для необязательных параметров, если их явно не задать.

---

### **Результаты выполнения**

```
Car Details:
Brand: Toyota
Model: Camry
Year: 2021
Color: White
Horsepower: 200 HP

Car Details:
Brand: Tesla
Model: Model 3
Year: 2023
Color: Black
Horsepower: 150 HP
```

---

### **Преимущества паттерна Builder**

1. **Управляемая сложность:**
   - Полезен, если объект имеет множество параметров, включая опциональные.
   - Позволяет избежать создания большого количества перегруженных конструкторов.

2. **Читаемость:**
   - Легче понять, какие параметры задаются, благодаря именованным методам.

3. **Гибкость:**
   - Параметры можно задавать в любом порядке, что делает код более выразительным.

4. **Безопасность:**
   - Позволяет добавить проверки обязательных параметров перед созданием объекта.