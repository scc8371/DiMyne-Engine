#include "Song.h"

Song::Song(const char* path, float loopPoint){
    //loop point cannot be before the start or after the end of the song
    if(loopPoint < 0 || loopPoint > 1){
        std::cout << "Invalid loop point. Please specify a value between 0 and 1.";
        return;
    }

    //loads the song from the wav file
    auto song = Wav(path);
    
    //loop point is specified... so we need to identify the sections of the song to loop and to not loop.
    if(loopPoint != 0){
        hasIntro = true;
        alGenBuffers(1, (ALuint*)&introBuffer); 
        alBufferData(introBuffer, AL_FORMAT_STEREO16, song.getData(), song.getSize(), song.getFreq());
        
        //determines where the loop of the song starts (ex. intro plays, will not play again due to loop)
        auto start = (int)(((float)song.getSize() / 4) * loopPoint) * 4;
        
        alGenBuffers(1, (ALuint*)&loopBuffer);
        alBufferData(loopBuffer, AL_FORMAT_STEREO16, (void*)((size_t)song.getData() + start),
             ((ALsizei)(song.getSize() - start)), song.getFreq());
        
    }
    //no loop point, just play the whole song.
    else{
        alGenBuffers(1, (ALuint*)&loopBuffer);
        alBufferData(loopBuffer, AL_FORMAT_STEREO16, song.getData(), song.getSize(), song.getFreq());
    }

    //checks for any OpenAL errors (should be none)d
    auto error = alGetError();

    //prints any errors to the console.
    if(error != AL_NO_ERROR){
        printf("OpenAL error: %i\n", error);
    }
    else{
        std::cout << "Song loaded successfully." << std::endl;
    }
}