#include "SoundPlayer.h"

SoundPlayer::SoundPlayer(){}

void SoundPlayer::initialize(){
    device = alcOpenDevice(NULL);

    if(device == NULL){
        std::cout << "OpenAL refused to get the default device" << std::endl;
    }

    audioContext = alcCreateContext(device, NULL);
    alcMakeContextCurrent(audioContext);

    if(audioContext == NULL){
        std::cout << "OpenAL refused to get the default context" << std::endl;
    }

    //generate sources for songs
    alGenSources(1, &musicSource);

    //generate sources for sounds
    alGenSources(SOURCES, &soundSources[0]);
}

void SoundPlayer::updateAudio(){
    ALint state;

    //checks if the source is already playing
    alGetSourcei(musicSource, AL_SOURCE_STATE, &state);

    //checks if audio stopped, and if a loop buffer is set
    if(state == AL_STOPPED && loopBuffer != 0){
        //sets the buffer to the loop buffer
        alSourcei(musicSource, AL_BUFFER, loopBuffer);
        alSourcei(musicSource, AL_LOOPING, AL_TRUE);

        //plays the source
        alSourcePlay(musicSource);
    }

    auto error = alGetError();

    if(error != AL_NO_ERROR){
        printf("OpenAL error: %i\n", error);
    }
}

void SoundPlayer::play(Song song){
    if(song.getLoopBuffer() == loopBuffer) return;

    //sets the pitch of the song
    alSourcef(musicSource, AL_PITCH, song.getPitch());

    if(song.getHasIntro()){
        alSourceStop(musicSource);

        alSourcei(musicSource, AL_BUFFER, song.getIntroBuffer());

        alSourcei(musicSource, AL_LOOPING, 0);
        alSourcef(musicSource, AL_GAIN, song.getVolume());
        alSourcePlay(musicSource);
    }
    else{
        alSourceStop(musicSource);
    }

    loopBuffer = song.getLoopBuffer();
}

void SoundPlayer::play(Sound sound){

    //checks if the source is already playing
    alSourcef(soundSources[nextSoundSource], AL_PITCH, sound.getPitch());
    alSourcei(soundSources[nextSoundSource], AL_BUFFER, sound.getBuffer());
    alSourcef(soundSources[nextSoundSource], AL_GAIN, sound.getVolume());

    alSourcePlay(soundSources[nextSoundSource]);

    nextSoundSource++;

    if(nextSoundSource >= SOURCES){
        nextSoundSource = 0;
    }
}

