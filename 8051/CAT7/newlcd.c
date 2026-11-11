#include <reg51.h>
#define PORT P3
sbit RS = P3^2;
sbit E  = P3^3;

sbit UP_ROW    = P2^3;
sbit DOWN_ROW  = P2^2;
sbit LEFT_ROW  = P2^1;
sbit RIGHT_ROW = P2^0;
sbit COL = P2^7;

/*
sbit LCD_D4 = P3^4;
sbit LCD_D5 = P3^5;
sbit LCD_D6 = P3^6;
sbit LCD_D7 = P3^7;
*/
void delay(){
	int i,j;
	for(i=0;i<2;i++){
		for(j=0;j<1275;j++){}}}
			
void delay_button(){
	int i,j;
	for(i=0;i<5;i++){
		for(j=0;j<5;j++){}}}
			
void lcd_send_nibble(unsigned char nibble){
	
	PORT=(PORT &0x0F)|(nibble & 0xF0);
	E=1;
	delay();
	E=0;
	delay();
}
void lcd_cmd(unsigned char cmd){
	RS=0;
	lcd_send_nibble(cmd);
	lcd_send_nibble(cmd<<4);
	delay();
	
}
void lcd_data(unsigned char d){
	RS=1;
	lcd_send_nibble(d);
	
	lcd_send_nibble(d<<4);
	delay();
}
void lcd_init(){
	delay();
	lcd_send_nibble(0x20);
	lcd_cmd(0x28);
	//lcd_cmd(0x02);//return home
	lcd_cmd(0x0E); //display ON, cursor ON
	lcd_cmd(0x06);//increment cursor direction, does not accompany display shift
	lcd_cmd(0x01);//clear display
	delay();
	delay();
	
}
void lcd_puts(char *str)
{
    int i = 0;

    while(str[i] != '\0')
    {
        lcd_data(str[i]);
        i++;
    }
}
void lcd_goto(unsigned char row, unsigned char col){
	if(row==1){
			lcd_cmd(0x80+0x00+(col-1));}
	if(row==2){
			lcd_cmd(0x80+0x40+(col-1));}
}

unsigned char check_button()
{
      // UP
    UP_ROW = 0;
    DOWN_ROW = 1;
    LEFT_ROW = 1;
    RIGHT_ROW = 1;

    COL = 1;

    if(COL == 0)
    {
        delay_button();

        if(COL == 0)
        {
            while(COL == 0);

            return 1;
        }
    }

       //DOWN
    UP_ROW = 1;
    DOWN_ROW = 0;
    LEFT_ROW = 1;
    RIGHT_ROW = 1;

    COL = 1;

    if(COL == 0)
    {
        delay_button();

        if(COL == 0)
        {
            while(COL == 0);

            return 2;
        }
    }
       //LEFT
    UP_ROW = 1;
    DOWN_ROW = 1;
    LEFT_ROW = 0;
    RIGHT_ROW = 1;

    COL = 1;

    if(COL == 0)
    {
        delay_button();

        if(COL == 0)
        {
            while(COL == 0);

            return 3;
        }
    }
    //RIGHT
    UP_ROW = 1;
    DOWN_ROW = 1;
    LEFT_ROW = 1;
    RIGHT_ROW = 0;

    COL = 1;

    if(COL == 0)
    {
        delay_button();

        if(COL == 0)
        {
            while(COL == 0);

            return 4;
        }
    }


    return 0;
}

int main(){
	unsigned char save='A';
		unsigned char button;
    unsigned char row = 1;
    unsigned char col = 1;
    UP_ROW = 1;
    DOWN_ROW = 1;
    LEFT_ROW = 1;
    RIGHT_ROW = 1;
		COL = 1;
	lcd_init();
	lcd_data(save);
	//lcd_cmd(0xC0);
	lcd_goto(2,1);
	lcd_puts("HELLO");

    lcd_goto(row, col);
    while(1)
    {
        button = check_button();
        //Up
        if(button == 1)
        {
            if(row > 1)
            {	lcd_goto(row, col);
							
								lcd_data(' ');
                row--;
                lcd_goto(row, col);
								lcd_data(save);
            }
        }
        //DOWN
        else if(button == 2)
        {
            if(row < 2)
            {lcd_goto(row, col);
							
								lcd_data(' ');
                row++;

                lcd_goto(row, col);
								lcd_data(save);

            }
        }
        //LEFT
        else if(button == 3)
        {
            if(col > 1)
            {lcd_goto(row, col);
								lcd_data(' ');
                col--;

                lcd_goto(row, col);
								lcd_data(save);

            }
        }
        //RIGHT
        else if(button == 4)
        {
            if(col < 16)
            {lcd_goto(row, col);
								lcd_data(' ');
                col++;
                lcd_goto(row, col);
							lcd_data(save);
            }
        }
    }
}