#include <stdio.h> 
#include "pico/stdlib.h" 
#include "pico/time.h" 
#include "hardware/irq.h" 
#include "hardware/pwm.h" 

#define LED_PIN 12 
#define SERVO_PIN 22 

// Parâmetros do PWM para o motor
const float PWM_FREQ = 50.0f;     
const uint16_t WRAP_VALUE = 19999;
const float CLK_DIV = 125.0f;   

// Protótipos de função
void set_servo_angle(uint pulse_us);
void pwm_led_handler();

//Função para ajustar ângulos
void set_servo_angle(uint pulse_us) {
    pwm_set_gpio_level(SERVO_PIN, pulse_us);
}

//Função de config do PWM
void pwm_setup() {
    gpio_set_function(SERVO_PIN, GPIO_FUNC_PWM);
    uint slice = pwm_gpio_to_slice_num(SERVO_PIN);
    
    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, CLK_DIV);
    pwm_config_set_wrap(&config, WRAP_VALUE);
    pwm_init(slice, &config, true);
}

//Configuração suave dos LEDs
void pwm_led_handler() {
        static int fade = 0;
        static bool rise = true;

        pwm_clear_irq(pwm_gpio_to_slice_num(LED_PIN));

        if(rise) {
            fade = (fade < 255) ? fade + 1 : 255;
            rise = (fade < 255);
        } else {
            fade = (fade > 0) ? fade - 1 : 0;
            rise = (fade == 0);
        }
        
        pwm_set_gpio_level(LED_PIN, fade * fade);
}

int main(){

    stdio_init_all();
    pwm_setup();

    //Conifg do LED
    gpio_set_function(LED_PIN, GPIO_FUNC_PWM);
    uint slice = pwm_gpio_to_slice_num(LED_PIN);
    
    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, 4.f);
    pwm_config_set_wrap(&config, 255);
    pwm_init(slice, &config, true);
    
    pwm_set_irq_enabled(slice, true);
    irq_set_exclusive_handler(PWM_IRQ_WRAP, pwm_led_handler);
    irq_set_enabled(PWM_IRQ_WRAP, true);

    //Config dos ângulos
    set_servo_angle(2400); // 180°
    sleep_ms(5000);
    
    set_servo_angle(1470);  // 90°
    sleep_ms(5000);
    
    set_servo_angle(500); // 0°
    sleep_ms(5000);

    //Config suave do braço
    while(true) {
        for(int us = 500; us <= 2400; us += 5) {
            set_servo_angle(us);
            sleep_ms(10);
        }
        for(int us = 2400; us >= 500; us -= 5) {
            set_servo_angle(us);
            sleep_ms(10);
        }
    }

}

