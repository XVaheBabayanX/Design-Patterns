#include <iostream>
#include <string>

class MediaPlayer {
public:
    virtual void play(const std::string& audioType, const std::string& fileName) = 0;
    virtual ~MediaPlayer() {}
};

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
        }
        else if (audioType == "mp4") {
            advancedPlayer->playMp4(fileName);
        }
        else {
            std::cout << "Unsupported format: " << audioType << std::endl;
        }
    }

    ~MediaAdapter() {
        delete advancedPlayer;
    }
};

class AudioPlayer : public MediaPlayer {
private:
    MediaAdapter* mediaAdapter;

public:
    void play(const std::string& audioType, const std::string& fileName) override {
        if (audioType == "mp3") {
            std::cout << "Playing MP3 file: " << fileName << std::endl;
        }
        else if (audioType == "vlc" || audioType == "mp4") {
            mediaAdapter = new MediaAdapter(audioType);
            mediaAdapter->play(audioType, fileName);
            delete mediaAdapter;
        }
        else {
            std::cout << "Unsupported audio type: " << audioType << std::endl;
        }
    }
};

int main() {
    AudioPlayer player;

    player.play("mp3", "song.mp3");
    player.play("vlc", "movie.vlc");
    player.play("mp4", "video.mp4");
    player.play("avi", "clip.avi");

    return 0;
}