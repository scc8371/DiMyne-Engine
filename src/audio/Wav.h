#ifndef WAV_H
#define WAV_H

#include <AL/al.h>
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <cstring>

class Wav{
public:
    Wav(const char* path);
    ~Wav();
    
    void* getData(){ return data; }
    uint32_t getSize(){ return size; }
    uint32_t getFreq(){ return freq; }
    uint32_t getChannels(){ return channels; }
    
private:
    void* data;
    uint32_t size, freq, channels;
};

#endif //WAV_H
