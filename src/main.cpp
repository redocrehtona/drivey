#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "drv.hpp"
#include "enc.hpp"
#include "cfg.hpp"

void core1_main()
{
    ENC enc0(ENC0_PIN1);
    while (true)
    {
        enc0.update();
        multicore_fifo_push_timeout_us(enc0._state.speed / ENC0_RPM_SCALE, 0);
        sleep_ms(5);
    }
}

int main()
{
    stdio_init_all();

    //sleep_ms(10000);
    DRV motor0(MOTOR0_PIN1, MOTOR0_PIN2, MOTOR0_FREQ, MOTOR0_CLKDIV, MOTOR0_EEP, MOTOR0_EEP_STATE);

    multicore_launch_core1(core1_main);

    // Current speed in RPM
    int speedNow = 0;


    while (true) {
        printf("%d\n", motor0.getDuty());
        printf("%d\n", motor0.getDutyPercent());
        printf("%d\n", motor0.setDuty((uint16_t)(0.15 * 0xFFFF)));

        // Drain the FIFO to get the latest speed value from core1
        while(multicore_fifo_rvalid()) {
            multicore_fifo_pop_blocking();
        }

        // Imedietly after draining, use the next value 
        speedNow = multicore_fifo_pop_blocking();

        printf("%d\n", speedNow);
        sleep_ms(1000);
    }
}
