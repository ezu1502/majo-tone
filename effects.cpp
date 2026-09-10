#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <stdexcept>


void hard_clipping(int32_t& l, int32_t& r){
    if (l > 32767){
        l = 32767;
    }
    else if (l < -32768){
        l = -32768;
    }
    
    if (r > 32767){
        r = 32767;
    }
    else if (r < -32768){
        r = -32768;
    }
}

void soft_clipping(int32_t& l, int32_t& r){

    if (l != 0){
        double l_module = (double) abs(l) / 32768;
        int sign = l / std::abs(l);

        if (l_module >= 0.6){
            double x = l_module - 0.6;
            double percentage = 0.6 + (0.4*x / (x + 0.404));

            l = 32767 * percentage * sign;
        }
    }
    if (r != 0){
        double r_module = (double) abs(r) / 32768;
        int sign_r = r / std::abs(r);

        if (r_module >= 0.6){
            double xr = r_module - 0.6;
            double percentage = 0.6 + (0.4*xr / (xr + 0.404));

            r = 32767 * percentage * sign_r;
        }
    }
}

void gain(int32_t& l, int32_t& r, float amount){
    if (amount < 0){
        throw std::runtime_error("Can't make a gain lesser than 0");
    }

    if (amount == 0){
        return;
    }

    l = std::round(l * amount);
    r = std::round(r * amount);
    
}

void hard_drive(int32_t& l, int32_t& r, float amount){
    if (amount <= 0){
        return;
    }

    gain(l, r, amount);
    hard_clipping(l, r);
}

void soft_drive(int32_t& l, int32_t& r, float amount){
    if (amount <= 0){
        return;
    }

    gain(l, r, amount);
    soft_clipping(l, r);
}


void low_pass(int32_t& l, int32_t& r, const int32_t& previous_l, const int32_t& previous_r, float alpha){
    int32_t delta_l = l - previous_l;
    int32_t delta_r = r - previous_r;

    l = previous_l + std::round(alpha * delta_l);
    r = previous_r + std::round(alpha * delta_r);
}