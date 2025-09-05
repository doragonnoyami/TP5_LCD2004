#ifndef LCD_H
#define LCD_H
void lcd_init();
void lcd_clear();
void lcd_setCursor(int col,int row);
void lcd_print();
void lcd_scrollDisplayLeft();
void lcd_scrollDisplayRight();
void lcd_backlight();
void lcd_noBacklight();
void lcd_createChar (int num,int datos[8]);
void lcd_send(char datos, int rs_est);
void lcd_sendCommand(char cmd);
void lcd_sendChar(char c);
#endif