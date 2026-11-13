
#include <reg51.h>

#define PORT P3

sbit RS = P3^2;
sbit E  = P3^3;

// Delay function
void delay()
{
    int i, j;

    for(i = 0; i < 2; i++)
    {
        for(j = 0; j < 1275; j++)
        {
        }
    }
}

// Send 4 bits to LCD
void lcd_send_nibble(unsigned char nibble)
{
    PORT = (PORT & 0x0F) | (nibble & 0xF0);

    E = 1;
    delay();

    E = 0;
    delay();
}

// Send command to LCD
void lcd_cmd(unsigned char cmd)
{
    RS = 0;

    lcd_send_nibble(cmd);
    lcd_send_nibble(cmd << 4);

    delay();
}

// Send character/data to LCD
void lcd_data(unsigned char d)
{
    RS = 1;

    lcd_send_nibble(d);
    lcd_send_nibble(d << 4);

    delay();
}

// Initialize LCD
void lcd_init()
{
    delay();

    lcd_send_nibble(0x20);  // 4-bit mode

    lcd_cmd(0x28);          // 4-bit, 2 lines, 5x8 font
    lcd_cmd(0x0C);          // Display ON, cursor OFF
    lcd_cmd(0x06);          // Increment cursor
    lcd_cmd(0x01);          // Clear display

    delay();
    delay();
}

// Display string
void lcd_puts(char *str)
{
    int i = 0;

    while(str[i] != '\0')
    {
        lcd_data(str[i]);
        i++;
    }
}

// Main program
void main()
{
    lcd_init();

    // Display individual character
    lcd_data('A');

    // Display text on first row
    lcd_cmd(0x80);
    lcd_puts("HELLO WORLD");

    // Display text on second row
    lcd_cmd(0xC0);
    lcd_puts("8051 LCD");

    while(1)
    {
    }
}
