#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include "../../include/raylib/raylib.h"

class Audio {
private:
    Sound clearSound;
    Sound rotateSound;
    Music backgroundMusic;
    Music gameLostMusic;

    static int totalOptions;

    // List of background music files
    static const char* backgroundMusicTracks[];

public:

    int currentMusicIndex;

    Audio();

    Music getBackgroundMusic() const ;
    Music getGameLostMusic() const ;
    Sound getClearSound() const ;
    Sound getRotateSound() const ;

    void setNextBackgroundMusic();
    void setPreviousBackgroundMusic();

    ~Audio();
};

#endif