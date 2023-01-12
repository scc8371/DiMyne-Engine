#ifndef SOUND_H
#define SOUND_H
#include <AL/al.h>
#include <iostream>
#include "Wav.h"

class Sound{
public:
    Sound(const char* path);

    ALint getBuffer() { return buffer; };
    float getVolume() { return volume; };
    float getPitch() { return pitch; };
    void setPitch(float pitch) { this->pitch = pitch; }
    void setVolume(float volume) {this->volume = volume; }
    

private:
    float volume = 1.0f;
    float pitch = 1.0f;
    ALint buffer = 0;
};

#endif //SOUND_H