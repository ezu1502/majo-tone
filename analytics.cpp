#include <cstdint>
#include <vector>
#include <cmath>

#include <cstdio>
#include "audio_loader.hpp"
#include "effects.hpp"

void compare_samples(const SampleArray& normal, const SampleArray& processed){
    SampleArray arrays[2] = {normal, processed};

    for (const SampleArray& array : arrays){
        int64_t sum = 0;

        for (const std::vector<int16_t>& side : array){
            for (const int16_t& sample : side){
                sum += (int64_t)sample * sample;
            }
        }

        double rms = std::sqrt((double)sum / (array[0].size() * 2));
        printf("RMS: %.2f\n", rms);
    }
}