#include "lcd.h"
#include "stm32f103xb.h"
#include "delay.h"
#define DB0 0
#define DB1 1
#define DB2 2
#define DB3 3
#define DB4 4
#define DB5 5
#define DB6 6
#define DB7 7
#define RS 8
#define RW 9
int pines[10]={DB0,DB1,DB2,DB3,DB4,DB5,DB6,DB7,RS,RW};
int lcd_row[4]={0x80,0xC0,0x94,0xD4};
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
        GPIOA -> BSRR |= (1<<(pines[i])+16); 
    }
    GPIOA -> BSRR |= (1<<(DB3));
    GPIOA -> BSRR |= (1<<(DB4));
    GPIOA -> BSRR |= (1<<(DB5));
}
void lcd_clear(){
    for(i=0; i<10; i++){
        GPIOA->BSRR |=(1<<pines[i]+16);
    }
    GPIOA->BSRR |=(1<<DB0);
    delay_ms(2);
}
void lcd_setCursor(int col,int row){
    int posicion=lcd_row[row]+col;
    lcd_sendCommand(posicion);
    delay_ms(1);
}
void lcd_print(char *str){
    while(str){
        lcd_sendChar(*str++);
    }
    delay_ms(1);
}
void lcd_scrollDisplayLeft(){
    for(i=0; i<10; i++){
        GPIOA->BSRR |=(1<<pines[i]+16);
    }
    GPIOA -> BSRR |= (1<<(DB3));
    GPIOA->BSRR |=(1<<DB4);
    delay_ms(1);
}
void lcd_scrollDisplayRight(){
    for(i=0; i<10; i++){
        GPIOA->BSRR |=(1<<pines[i]+16);
    }
    GPIOA -> BSRR |= (1<<DB2);
    GPIOA->BSRR |=(1<<DB3);
    GPIOA -> BSRR |= (1<<DB4);
    delay_ms(1);
}
void lcd_backlight(){
     for(i=0; i<10; i++){
        GPIOA->BSRR |=(1<<pines[i]+16);
    }
    GPIOA -> BSRR |= (1<<DB2);
    GPIOA->BSRR |=(1<<DB3);
    delay_ms(1);
}
void lcd_noBacklight(){
     for(i=0; i<10; i++){
        GPIOA->BSRR |=(1<<pines[i]+16);
    }
    GPIOA->BSRR |=(1<<DB3);
    delay_ms(1);
}
void lcd_createChar (int num,int datos[8]){
    lcd_sendCommand(num*8+0x40);
    for(i=0;i<8;i++){
        lcd_sendCommand(datos[i]);
    }
    delay_ms(1);
}
void lcd_send(char datos, int rs_est){
    if(rs_est){
        GPIOA -> BSRR |= (1<<RS);
    }
    else {
        GPIOA -> BSRR |= (1<<(RS+16));
    }
    GPIOA -> BSRR |= (0x7F<<(DB0+16));
    GPIOA -> BSRR |= (datos<<(DB0));
    delay_ms(1);
}
void lcd_sendCommand(char cmd){
    lcd_send(cmd,0);
    delay_ms(1);
}
void lcd_sendChar(char c){
    lcd_send(c,1);
    delay_ms(1);
}