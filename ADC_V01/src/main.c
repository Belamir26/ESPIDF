#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/adc.h"


#define A14 ADC2_CHANNEL_4
#define samples 64

void setup(void);


void app_main() 
{
    int val_pot_raw=0;
    int smooth_val=0;
    
    while(1)
    {
        for(int k=0;k<samples;k++){
            adc2_get_raw(A14,12,&val_pot_raw);
            smooth_val += val_pot_raw;
        }
        smooth_val /= samples;
        if(smooth_val > 4095){smooth_val=4095;}
        adc2_get_raw(A14,12,&val_pot_raw);
        
        printf("Valor RAW: %d\n",val_pot_raw);
        printf("Valor: %d",smooth_val);
        vTaskDelay(300/portTICK_PERIOD_MS);

    }
}

void setup(void){
    adc2_config_channel_atten(A14,ADC_ATTEN_DB_11);
}
