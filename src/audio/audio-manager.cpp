#include "audio-manager.h"
#include "../core/global.h"

int Audio::totalOptions = 3;

// List of background music files
const char* Audio::backgroundMusicTracks[] = {
    "assets/audio/background_music.mp3",
    "assets/audio/background_music[1].wav",
    "assets/audio/background_music[2].mp3"
};

Audio::Audio() {
    currentMusicIndex = 0; 

    InitAudioDevice();

    clearSound = LoadSound("assets/audio/clear.mp3");
    rotateSound = LoadSound("assets/audio/rotate.mp3");
    backgroundMusic = LoadMusicStream(backgroundMusicTracks[currentMusicIndex]);
    gameLostMusic = LoadMusicStream("assets/audio/game_lost.wav");

    PlayMusicStream(backgroundMusic);
    SetMusicVolume(backgroundMusic, 1.0f);
}

Music Audio::getBackgroundMusic() const { return backgroundMusic; }

Music Audio::getGameLostMusic() const { return gameLostMusic; }

Sound Audio::getClearSound() const { return clearSound; }

Sound Audio::getRotateSound() const { return rotateSound; }

void Audio::setNextBackgroundMusic() { 
        StopMusicStream(backgroundMusic);
        backgroundMusic = LoadMusicStream(backgroundMusicTracks[++currentMusicIndex % totalOptions]); 
        PlayMusicStream(backgroundMusic);
        SetMusicVolume(backgroundMusic, musicVolume);
}

void Audio::setPreviousBackgroundMusic() { 
    StopMusicStream(backgroundMusic);

    currentMusicIndex--;
    if(currentMusicIndex < 0) 
        currentMusicIndex = totalOptions - 1;
        
    backgroundMusic = LoadMusicStream(backgroundMusicTracks[currentMusicIndex % totalOptions]); 
    PlayMusicStream(backgroundMusic);
    SetMusicVolume(backgroundMusic, musicVolume);
}

Audio::~Audio() {
    StopMusicStream(backgroundMusic);

    UnloadSound(clearSound);
    UnloadSound(rotateSound);
    UnloadMusicStream(gameLostMusic);
    UnloadMusicStream(backgroundMusic);
    CloseAudioDevice();
}