#include "stm32f103xb.h"
#include "lcd.h"
#include "delay.h"
int ixtal_simbolo[8] = {
    0b00100, 
    0b01110, 
    0b10101, 
    0b01110, 
    0b00100, 
    0b00100, 
    0b00100, 
    0b00000,
};

int main(){
    lcd_init();
    lcd_createChar(0,ixtal_simbolo);
    while(1){
        lcd_clear();
        lcd_sendChar(0);
        lcd_backlight();
        delay_ms(1000);
    }
    return 0;
}