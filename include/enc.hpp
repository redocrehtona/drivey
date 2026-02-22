#ifndef ENC_HPP
#define ENC_HPP
#include <cstdint>  // For inetegers of specific sizes
#include "pico/stdlib.h"
#include "hardware/pio.h"

typedef struct substep_state_t {
    // configuration data:
    uint calibration_data[4]; // relative phase sizes
    uint clocks_per_us;       // save the clk_sys frequency in clocks per us
    uint idle_stop_samples;   // after these samples without transitions, assume the encoder is stopped
    PIO pio;
    uint sm;

    // internal fields to keep track of the previous state:
    uint prev_trans_pos, prev_trans_us;
    uint prev_step_us;
    uint prev_low, prev_high;
    uint idle_stop_sample_count;
    int speed_2_20;
    int stopped;

    // output of the encoder update function:
    int speed;     // estimated speed in substeps per second
    uint position; // estimated position in substeps

    uint raw_step; // raw step count
} substep_state_t;

class ENC {
    private:
        uint32_t _last_position;
        int32_t _last_speed;
        uint32_t _last_raw_step;
    public:
        substep_state_t _state;
        ENC(uint8_t pin_a);
        void update();
};

#endif