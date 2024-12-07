# Adapter
---
**Structural Design Pattern** 
---

### Объяснение паттерна **Adapter** с кодом

Паттерн **Adapter** используется для объединения интерфейсов, которые не совместимы друг с другом. Он «адаптирует» один интерфейс к другому, что позволяет клиенту использовать неподходящий класс без его модификации.

---

### Разбор кода

#### 1. **Target (Целевой интерфейс):**
```cpp
class MediaPlayer {
public:
    virtual void play(const std::string& audioType, const std::string& fileName) = 0;
    virtual ~MediaPlayer() {}
};
```
- Интерфейс `MediaPlayer` определяет метод `play`, ожидаемый клиентом.
- Клиент (`AudioPlayer`) использует этот интерфейс для воспроизведения различных аудиофайлов.

---

#### 2. **Adaptee (Адаптируемый класс):**
```cpp
class AdvancedMediaPlayer {
public:
    virtual void playVlc(const std::string& fileName) {
        std::cout << "Playing VLC file: " << fileName << std::endl;
    }
    virtual void playMp4(const std::string& fileName) {
        std::cout << "Playing MP4 file: " << fileName << std::endl;
    }
    virtual ~AdvancedMediaPlayer() {}
};
```
- Класс `AdvancedMediaPlayer` предоставляет методы `playVlc` и `playMp4`, несовместимые с интерфейсом `MediaPlayer`.
- Это наш «старый» или «несовместимый» класс.

---

#### 3. **Adapter (Адаптер):**
```cpp
class MediaAdapter : public MediaPlayer {
private:
    AdvancedMediaPlayer* advancedPlayer;

public:
    MediaAdapter(const std::string& audioType) {
        advancedPlayer = new AdvancedMediaPlayer();
    }

    void play(const std::string& audioType, const std::string& fileName) override {
        if (audioType == "vlc") {
            advancedPlayer->playVlc(fileName);
        } else if (audioType == "mp4") {
            advancedPlayer->playMp4(fileName);
        } else {
            std::cout << "Unsupported format: " << audioType << std::endl;
        }
    }

    ~MediaAdapter() {
        delete advancedPlayer;
    }
};
```
- `MediaAdapter` реализует интерфейс `MediaPlayer`, чтобы быть совместимым с клиентом.
- Он «оборачивает» `AdvancedMediaPlayer`, перенаправляя вызовы на соответствующие методы (`playVlc` или `playMp4`).
- Это основная часть паттерна: адаптер позволяет клиенту использовать `AdvancedMediaPlayer` через интерфейс `MediaPlayer`.

---

#### 4. **Client (Клиентский код):**
```cpp
class AudioPlayer : public MediaPlayer {
private:
    MediaAdapter* mediaAdapter;

public:
    void play(const std::string& audioType, const std::string& fileName) override {
        if (audioType == "mp3") {
            std::cout << "Playing MP3 file: " << fileName << std::endl;
        } else if (audioType == "vlc" || audioType == "mp4") {
            mediaAdapter = new MediaAdapter(audioType);
            mediaAdapter->play(audioType, fileName);
            delete mediaAdapter;
        } else {
            std::cout << "Unsupported audio type: " << audioType << std::endl;
        }
    }
};
```
- `AudioPlayer` использует интерфейс `MediaPlayer` для воспроизведения аудиофайлов.
- Для форматов, которые `AudioPlayer` не поддерживает напрямую (например, `vlc` или `mp4`), создаётся экземпляр адаптера `MediaAdapter`.

---

#### 5. **Client Code (Использование):**
```cpp
int main() {
    AudioPlayer player;

    player.play("mp3", "song.mp3");
    player.play("vlc", "movie.vlc");
    player.play("mp4", "video.mp4");
    player.play("avi", "clip.avi");

    return 0;
}
```
- Вызывается метод `play` для воспроизведения разных форматов файлов:
  - MP3 файлы обрабатываются напрямую.
  - VLC и MP4 файлы перенаправляются на `MediaAdapter`.
  - AVI формат не поддерживается, и клиент получает сообщение об ошибке.

---

### Вывод программы:
```
Playing MP3 file: song.mp3
Playing VLC file: movie.vlc
Playing MP4 file: video.mp4
Unsupported audio type: avi
```

---

### Преимущества и применение

1. **Преимущества:**
   - Позволяет интегрировать старый или несовместимый код без изменения его реализации.
   - Разделяет клиентский код и адаптируемый класс, улучшая читаемость и поддерживаемость.
   - Обеспечивает гибкость: легко адаптировать новый функционал.

2. **Когда использовать:**
   - Когда нужно использовать существующий класс, но его интерфейс не соответствует требованиям.
   - При интеграции старых систем с новыми.