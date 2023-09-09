#include "Sound.h"

Sound::Sound(const char* path){
    auto sound = Wav(path);

    alGenBuffers(1, (ALuint*)(&buffer));

    alBufferData(buffer, AL_FORMAT_STEREO16, sound.getData(), sound.getSize(), sound.getFreq());
}