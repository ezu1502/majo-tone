#include <fstream>
#include <iostream>
#include <stdexcept>
#include <cstdint>
#include <vector>
#include <string>

#define L 0
#define R 1

using SampleArray = std::vector<std::vector<int16_t>>;

std::ifstream load_audio_file(std::string file_name){
    std::ifstream file(file_name, std::ios::binary);
    if (!file){
        throw std::runtime_error("Couldn't open audio file");
    }

    std::cout << "File open successfully.\n";
    return file;
}

std::vector<char> get_header(std::ifstream& audio_file){
    std::vector<char> header;

    char byte;

    std::string finder = "";

    while (audio_file.get(byte)){
        header.push_back(byte);
        finder += byte;

        if (finder.size() > 4){
            finder.erase(0, 1);
        }

        if (finder == "data"){
            // std::cout << "Achamo\n";

            for(int i = 0; i < 4; i++){
                audio_file.get(byte);
                header.push_back(byte);
                // std::cout << (int)byte << " ";
            }

            break;
        }
    }    
    return header;
}

SampleArray load_samples(std::ifstream& audio_file){
    SampleArray samples(2);

    char l1, l2;
    char r1, r2;

    int16_t l, r;

    while(audio_file.get(l1) && audio_file.get(l2) && audio_file.get(r1) && audio_file.get(r2)){
        l = static_cast<unsigned char>(l1) + (static_cast<unsigned char>(l2) << 8);
        r = static_cast<unsigned char>(r1) + (static_cast<unsigned char>(r2) << 8);
        
        samples[0].push_back(l);
        samples[1].push_back(r);
    }

    if (samples[0].size() != samples[1].size()){
        throw std::runtime_error("sample sizes should be equal!");
    }
    return samples;
}

void save_audio(const std::vector<char>& header, const SampleArray& samples, std::string output_name){
    std::ofstream output(output_name, std::ios::binary);
    if (!output){
        throw std::runtime_error("Couldn't create output file");
    }

    for (char byte : header){
        output.put(byte);
    }

    for (size_t i = 0; i < samples[0].size(); i++){
        uint16_t l = static_cast<uint16_t>(samples[L][i]);
        uint16_t r = static_cast<uint16_t>(samples[R][i]);

        uint8_t l1 = l & 0xFF;
        uint8_t l2 = l >> 8;

        uint8_t r1 = r & 0xFF;
        uint8_t r2 = r >> 8;

        output.put(l1);
        output.put(l2);
        output.put(r1);
        output.put(r2);
    }
    
}

