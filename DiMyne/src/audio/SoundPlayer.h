#ifndef SOUNDPLAYER_H
#define SOUNDPLAYER_H

#include <AL/al.h>
#include <AL/alext.h>
#include <opengl/opengl.h>
#include <iostream>
#include "Song.h"
#include "Sound.h"
//pre alloc, higher = more RAM usage. 
const int SOURCES = 60;

class SoundPlayer{
public:
    SoundPlayer();
    void updateAudio();
    void initialize();
    void play(Song song);
    void play(Sound sound);


private:
    ALCdevice* device;
    ALCcontext* audioContext;

    //sources
    ALuint musicSource = 0;
    ALuint soundSources[SOURCES];

    int nextSoundSource = 0;
    ALuint loopBuffer = 0;
};


#endif //SOUNDPLAYER_H