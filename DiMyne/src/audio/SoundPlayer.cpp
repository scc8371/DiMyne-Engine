#include "SoundPlayer.h"

SoundPlayer::SoundPlayer(){}

void SoundPlayer::initialize(){
    //audio system init
    device = alcOpenDevice(NULL);

    if(device == NULL){
        std::cout << "[OpenAL] OpenAL refused to get default device" << std::endl;
        return;
    }

    audioContext = alcCreateContext(device, NULL);
    alcMakeContextCurrent(audioContext);

    if(audioContext == NULL){
        std::cout << "[OpenAL] OpenAL refused to make current context" << std::endl;
    }

    //generates source for song
    alGenSources(1, &musicSource);

    //generates source for sounds
    alGenSources(SOURCES, &soundSources[0]);   
}

void SoundPlayer::updateAudio(){
    ALint state;

    //checks if the music is currently playing
    alGetSourcei(musicSource, AL_SOURCE_STATE, &state);
    
    //checks if the audio stopped
    //and if a loop has been queued
    if(state != AL_PLAYING && loopBuffer != 0){
        //changes current state to play the loop
        alSourcei(musicSource, AL_BUFFER, loopBuffer);
        alSourcei(musicSource, AL_LOOPING, 1);

        //plays the music
        alSourcePlay(musicSource);
    }        

    auto error = alGetError();

    if(error != AL_NO_ERROR){
        printf("OpenAL error: %i\n", error);
    }
}

void SoundPlayer::play(Song song){
    //prevents the song from infinitely repeating.
    if(song.getLoopBuffer() == loopBuffer) return;


    //sets the pitch of the song
    alSourcef(musicSource, AL_PITCH, song.pitch);
    
    //checks if the song has an intro segment
    if(song.getHasIntro()){
        //stops current track and plays the intro
        alSourceStop(musicSource);

        alSourcei(musicSource, AL_BUFFER, song.getIntroBuffer());

        alSourcei(musicSource, AL_LOOPING, 0);
        alSourcef(musicSource, AL_GAIN, song.volume);
        alSourcePlay(musicSource);
    }
    else{
        //does not play intro and immediately starts the loop
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

