#include <fstream>
#include <vector>
#include "audio_loader.hpp"
#include "effects.hpp"
#include "analytics.hpp"

#define L 0
#define R 1


SampleArray process_samples(SampleArray og_samples){
    SampleArray alter(2);

    for (size_t i = 0; i < og_samples[0].size(); i++){
        int32_t l = static_cast<int32_t>(og_samples[L][i]);
        int32_t r = static_cast<int32_t>(og_samples[R][i]);

        soft_drive(l, r, 40.0f);
        
        alter[L].push_back(l);
        alter[R].push_back(r);
    }

    return alter;
}


int main(){
    std::ifstream audio_file = load_audio_file("songs/test.wav");
    std::vector<char> header = get_header(audio_file);
    SampleArray samples = load_samples(audio_file);
    
    SampleArray processed = process_samples(samples);

    save_audio(header, processed, "output.wav");

    compare_samples(samples, processed);

}