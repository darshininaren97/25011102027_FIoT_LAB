
#include <reg51.h>

#define PORT P3

sbit RS = P3^2;
sbit E  = P3^3;

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

void lcd_send_nibble(unsigned char nibble)
{
    PORT = (PORT & 0x0F) | (nibble & 0xF0);

    E = 1;
    delay();

    E = 0;
    delay();
}

void lcd_cmd(unsigned char cmd)
{
    RS = 0;

    lcd_send_nibble(cmd);
    lcd_send_nibble(cmd << 4);

    delay();
}

void lcd_data(unsigned char d)
{
    RS = 1;

    lcd_send_nibble(d);
    lcd_send_nibble(d << 4);

    delay();
}

void lcd_init()
{
    delay();

    lcd_send_nibble(0x20);

    lcd_cmd(0x28);
    lcd_cmd(0x0C);
    lcd_cmd(0x06);
    lcd_cmd(0x01);

    delay();
    delay();
}

// Position cursor
void lcd_goto(unsigned char row, unsigned char col)
{
    if(row == 1)
    {
        lcd_cmd(0x80 + (col - 1));
    }

    if(row == 2)
    {
        lcd_cmd(0xC0 + (col - 1));
    }
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

// Display integer
void lcd_print_number(unsigned int value)
{
    unsigned char digit;
    unsigned char arr[5];
    int i = 0;

    if(value == 0)
    {
        lcd_data('0');
        return;
    }

    while(value > 0)
    {
        digit = value % 10;
        arr[i] = digit + '0';

        value = value / 10;
        i++;
    }

    while(i > 0)
    {
        i--;
        lcd_data(arr[i]);
    }
}

void main()
{
    unsigned int count = 1234;

    lcd_init();

    lcd_goto(1, 1);
    lcd_puts("VALUE:");

    lcd_goto(2, 1);
    lcd_print_number(count);

    while(1)
    {
        // Dynamic value can be updated here
    }
}

