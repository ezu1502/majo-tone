#include <fstream>
#include <vector>
#include <iostream>
#include "audio_loader.hpp"
#include "effects.hpp"
#include "analytics.hpp"

#define L 0
#define R 1


SampleArray process_samples(SampleArray og_samples){
    SampleArray alter(2);

    int32_t previous_l = static_cast<int32_t>(og_samples[L][0]);
    int32_t previous_r = static_cast<int32_t>(og_samples[R][0]);

    for (size_t i = 0; i < og_samples[0].size(); i++){
        if (i == (og_samples[0].size() / 2)) {
            std::cout << "50%\n";
        }
        if (i == (3 * og_samples[0].size() / 4)) {
            std::cout << "75%\n";
        }
        

        int32_t l = static_cast<int32_t>(og_samples[L][i]);
        int32_t r = static_cast<int32_t>(og_samples[R][i]);

        // soft_drive(l, r, 7.0f);
        
        low_pass(l, r, previous_l, previous_r, 0.2f);

        alter[L].push_back(l);
        alter[R].push_back(r);

        previous_l = l;
        previous_r = r;
    }

    return alter;
}


int main(){
    std::ifstream audio_file = load_audio_file("songs/Aitakute.wav");
    std::vector<char> header = get_header(audio_file);
    SampleArray samples = load_samples(audio_file);
    
    SampleArray processed = process_samples(samples);

    save_audio(header, processed, "output.wav");

    compare_samples(samples, processed);

}