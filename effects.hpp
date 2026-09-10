#include <cstdint>

void hard_clipping(int32_t& l, int32_t& r);

void soft_clipping(int32_t& l, int32_t& r);

void gain(int32_t& l, int32_t& r, float amount);

void hard_drive(int32_t& l, int32_t& r, float amount);

void soft_drive(int32_t& l, int32_t& r, float amount);

