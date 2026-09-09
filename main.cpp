#include <fstream>
#include <vector>
#include "audio_loader.hpp"

#define L 0
#define R 1

void clip_samples(int32_t *l, int32_t *r){
    if (*l > 32767){
        *l = 32767;
    }
    else if (*l < -32768){
        *l = -32768;
    }
    
    if (*r > 32767){
        *r = 32767;
    }
    else if (*r < -32768){
        *r = -32768;
    }
}

SampleArray processed_samples(SampleArray og_samples){
    SampleArray alter(2);

    for (size_t i = 0; i < og_samples[0].size(); i++){
        int32_t l = static_cast<int32_t>(og_samples[L][i]);
        int32_t r = static_cast<int32_t>(og_samples[R][i]);

        l *= 10;
        r *= 10;

        clip_samples(&l, &r);
        
        alter[L].push_back(l);
        alter[R].push_back(r);
    }

    return alter;
}


int main(){
    std::ifstream audio_file = load_audio_file("songs/Aitakute.wav");
    std::vector<char> header = get_header(audio_file);
    SampleArray samples = load_samples(audio_file);
    
    SampleArray processed = processed_samples(samples);

    save_audio(header, processed, "output.wav");

}