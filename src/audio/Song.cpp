#include "Song.h"

Song::Song(const char* path, float loopPoint){
    if(loopPoint < 0 || loopPoint > 1){
        std::cout << "Song::Song: " << path << " >> loopPoint must be between 0 and 1" << std::endl;
        return;
    }   

    //loads song from wav file
    auto song = Wav(path);

    //loop point specified, ID sections to set as loop points
    if(loopPoint != 0){
        hasIntro = true;

        alGenBuffers(1, (ALuint*)&introBuffer);
        alBufferData(introBuffer, AL_FORMAT_STEREO16, song.getData(), song.getSize() * loopPoint, song.getFreq());

        //determines the start of the loop
        auto start = (int)(((float)song.getSize() / 4) * loopPoint) * 4;

        alGenBuffers(1, (ALuint*)&loopBuffer);
        alBufferData(loopBuffer, AL_FORMAT_STEREO16, song.getData(), song.getSize(), song.getFreq());

        auto error = alGetError();

        if(error != AL_NO_ERROR){
            printf("OpenAL error: %i from Song.cpp\n", error);
        }
    }
}