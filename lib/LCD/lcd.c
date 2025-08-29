#include "lcd.h"
#include "stm32f103xb.h"
#include "delay.h"
int pines[10]={0,1,2,3,4,5,6,7,8,9};//0 al 7 pines de datos. RS=8. RW=9
int i=0;
void lcd_init(){
    RCC -> APB2ENR |= RCC_APB2ENR_IOPAEN;
    RCC -> APB2ENR |= RCC_APB2ENR_IOPBEN;
    for(i=0; i<10; i++){
        if(i<8){
            GPIOA->CRL&=~(0xF<<(pines[i]*4));
            GPIOA->CRL|=(0x1<<(pines[i]*4));
        }else{
            GPIOA -> CRH &=~ (0xF<<((pines[i]%8)*4));
            GPIOA -> CRH |= (0x1<<((pines[i]%8)*4));
        }
    }
}
void lcd_clear(){
    for(i=0; i<10; i++){
        GPIOA->BSRR |=(1<<pines[i]+16);
    }
    GPIOA->BSRR |=(1<<pines[0]);
}
void lcd_setCursor(int col,int row){
    
}
void lcd_print(){
    for(i=0; i<10; i++){
        GPIOA->BSRR |=(1<<pines[i]+16);
    }
    GPIOA->BSRR |=(1<<pines[8]);
}
void lcd_scrollDisplayLeft(){
    for(i=0; i<10; i++){
        GPIOA->BSRR |=(1<<pines[i]+16);
    }
    GPIOA -> BSRR |= (1<<(pines[4]));
    GPIOA->BSRR |=(1<<pines[3]);
}
void lcd_scrollDisplayRight(){
    for(i=0; i<10; i++){
        GPIOA->BSRR |=(1<<pines[i]+16);
    }
    GPIOA -> BSRR |= (1<<(pines[4]));
    GPIOA->BSRR |=(1<<pines[3]);
    GPIOA -> BSRR |= (1<<(pines[2]));
}
void lcd_backlight(){
     for(i=0; i<10; i++){
        GPIOA->BSRR |=(1<<pines[i]+16);
    }
    GPIOA -> BSRR |= (1<<(pines[2]));
    GPIOA->BSRR |=(1<<pines[3]);
}
void lcd_noBacklight(){
     for(i=0; i<10; i++){
        GPIOA->BSRR |=(1<<pines[i]+16);
    }
    GPIOA->BSRR |=(1<<pines[3]);
}
void lcd_createChar (int num,int datos){

}