#include <fstream>
#include <cstdint>
#include <vector>

#define L 0
#define R 1

using SampleArray = std::vector<std::vector<int16_t>>;

std::ifstream load_audio_file(std::string file_name);

std::vector<char> get_header(std::ifstream& audio_file);

SampleArray load_samples(std::ifstream& audio_file);

void save_audio(const std::vector<char>& header, const SampleArray& samples, std::string output_name);