#ifndef SONG_H
#define SONG_H
#include <AL/al.h>
#include <iostream>
#include "Wav.h"

class Song{
public:
    Song(const char* path, float loopPoint = 0);
    
    ALint getIntroBuffer() { return introBuffer; };
    ALint getLoopBuffer() { return loopBuffer;};
    bool getHasIntro() { return hasIntro; };
    float volume = 1.0f;
    float pitch = 1.0f;
    
private:
    ALint introBuffer = 0, loopBuffer = 0;
    bool hasIntro = false;
    
};


#endif //SONG_H