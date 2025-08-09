#include <stdio.h>
#include "pico/stdlib.h"

#include "lib/ssd1306/ssd1306.h"
#include "lib/ssd1306/display.h"
#include "lib/led/led.h"
#include "lib/button/button.h"
#include "lib/matrix_leds/matrix_leds.h"
#include "lib/buzzer/buzzer.h"
#include "lib/aht20/aht20.h"
#include "lib/bmp280/bmp280.h"
#include "lib/sensors/sensors.h"
#include "pico/bootrom.h"

ssd1306_t ssd; // Declaração do display OLED
SensorReadings readings;

volatile bool tx_mode=false;
volatile bool rx_mode=false;

void button_callback(uint gpio, uint32_t events);
void init_peripherals();
void setup_lora_mode();
void tx_operation_mode();
void rx_operation_mode();
void display_startup_message();
void display_data();



int main()
{
    stdio_init_all();

    init_peripherals();

    setup_lora_mode();
    
    if (tx_mode)
    {
        while (true)
        {
            tx_operation_mode();
            sleep_ms(1000);
        }
    
    }else if(rx_mode){
        while (true)
        {
            rx_operation_mode();
            sleep_ms(500);
        }
        
    }
    
}

void init_peripherals(){
    button_init_predefined(true,true,true);
    button_setup_irq(true,true,true,button_callback);
    init_led_matrix(); // Inicializa a matriz de LEDs
    init_display(&ssd); // Inicializa o display OLED
    init_leds();// Inicializa os LEDs

}

void tx_operation_mode(){
    readings=get_sensor_readings();
    display_data();
    //Falta implementar envio via Lora
}

void rx_operation_mode(){
    //Falta implementar recebimento dos dados e armazenamento em struct
    display_data();
}

void setup_lora_mode(){
    
    //Falta inicialização do SPI e Lora
    set_led_yellow();
    display_startup_message();
    
    while (!rx_mode && !tx_mode)
    {
        set_led_yellow();
        sleep_ms(250);
        turn_off_leds();
        sleep_ms(250);
    }

    gpio_set_irq_enabled(BUTTON_A, GPIO_IRQ_EDGE_FALL, false);
    gpio_set_irq_enabled(BUTTON_B, GPIO_IRQ_EDGE_FALL, false);


    if (tx_mode)
    {
        init_i2c_sensor();
        init_bmp280();
        init_aht20();
        desenha_frame(status,0);
        //Falta a configuração do modo TX
        
    }else if(rx_mode){

        desenha_frame(status,1);
        //Falta a configuração do modo RX

    }
    
    set_led_green();
    
}

void display_startup_message(){

    ssd1306_fill(&ssd, false);                     // Limpa o display
    ssd1306_rect(&ssd, 3, 3, 122, 60, true, false); // Desenha um retângulo

    ssd1306_draw_string(&ssd,"Escolha o modo", 10,10);

    ssd1306_draw_string(&ssd,"Botao A:", 10,20);
    ssd1306_draw_string(&ssd,"  Transmissor", 10,30);

    ssd1306_draw_string(&ssd,"Botao B:", 10,40);
    ssd1306_draw_string(&ssd,"  Receptor", 10,50);

    ssd1306_send_data(&ssd);   // Envia os dados para o display
}

void display_data(){

    ssd1306_fill(&ssd, false);                     // Limpa o display
    ssd1306_rect(&ssd, 3, 3, 122, 60, true, false); // Desenha um retângulo
    
    ssd1306_line(&ssd,3,20,125,20,true); //Linha Horizontal
    ssd1306_line(&ssd,64,3,64,45,true);  //Linha Vertical

    ssd1306_draw_string(&ssd, "BMP280", 10, 10);
    char temp_str[10];
    snprintf(temp_str, sizeof(temp_str), "%.1fC", readings.bmp_temp);
    ssd1306_draw_string(&ssd, temp_str, 10, 25);

    char altitude_str[10];
    snprintf(altitude_str, sizeof(altitude_str), "%.1fm", readings.altitude_m);
    ssd1306_draw_string(&ssd, altitude_str, 10, 35);
    
    //AHT20 DADOS
    ssd1306_draw_string(&ssd, "AHT20", 70, 10);

    char temp_aht_str[10];
    snprintf(temp_aht_str, sizeof(temp_aht_str), "%.1fC", readings.aht_temp);
    ssd1306_draw_string(&ssd, temp_aht_str, 70, 25);

    char humidity_str[10];
    snprintf(humidity_str, sizeof(humidity_str), "%.1f%%", readings.humidity);
    ssd1306_draw_string(&ssd, humidity_str, 70, 35);

    ssd1306_line(&ssd,3,45,125,45,true); //Linha Horizontal

    ssd1306_draw_string(&ssd,tx_mode ? "Transmissor" : "Receptor", 10,50);
    
    ssd1306_send_data(&ssd);   // Envia os dados para o display
}

void button_callback(uint gpio, uint32_t events){
    uint32_t current_time = to_ms_since_boot(get_absolute_time());

    if(current_time - last_debounce_time > debounce_delay){
        printf("Interrupção chamada\n");
        if(gpio == BUTTON_A){
            tx_mode=true;
        }
        else if(gpio == BUTTON_B){
            rx_mode=true;
        }
        else if(gpio == BUTTON_SW){
            reset_usb_boot(0, 0);
        }

        last_debounce_time = current_time;
    }
}
