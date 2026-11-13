
#include <reg51.h>

#define PORT P3

sbit RS = P3^2;
sbit E  = P3^3;

// Keypad connections
sbit UP_ROW    = P2^3;
sbit DOWN_ROW  = P2^2;
sbit LEFT_ROW  = P2^1;
sbit RIGHT_ROW = P2^0;

sbit COL = P2^7;

// Delay
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

void delay_button()
{
    int i, j;

    for(i = 0; i < 5; i++)
    {
        for(j = 0; j < 5; j++)
        {
        }
    }
}

// Send nibble
void lcd_send_nibble(unsigned char nibble)
{
    PORT = (PORT & 0x0F) | (nibble & 0xF0);

    E = 1;
    delay();

    E = 0;
    delay();
}

// LCD command
void lcd_cmd(unsigned char cmd)
{
    RS = 0;

    lcd_send_nibble(cmd);
    lcd_send_nibble(cmd << 4);

    delay();
}

// LCD data
void lcd_data(unsigned char d)
{
    RS = 1;

    lcd_send_nibble(d);
    lcd_send_nibble(d << 4);

    delay();
}

// LCD initialization
void lcd_init()
{
    delay();

    lcd_send_nibble(0x20);

    lcd_cmd(0x28);
    lcd_cmd(0x0E);
    lcd_cmd(0x06);
    lcd_cmd(0x01);

    delay();
    delay();
}

// Cursor positioning
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

// Read keypad
// 1 = UP
// 2 = DOWN
// 3 = LEFT
// 4 = RIGHT
// 0 = No key

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

    // DOWN
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

    // LEFT
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

    // RIGHT
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

// Main program
void main()
{
    unsigned char save = 'A';
    unsigned char button;

    unsigned char row = 1;
    unsigned char col = 1;

    // Initialize keypad
    UP_ROW = 1;
    DOWN_ROW = 1;
    LEFT_ROW = 1;
    RIGHT_ROW = 1;

    COL = 1;

    lcd_init();

    lcd_data(save);

    lcd_goto(2, 1);
    lcd_puts("HELLO");

    lcd_goto(row, col);

    while(1)
    {
        button = check_button();

        // UP
        if(button == 1)
        {
            if(row > 1)
            {
                lcd_goto(row, col);
                lcd_data(' ');

                row--;

                lcd_goto(row, col);
                lcd_data(save);
            }
        }

        // DOWN
        else if(button == 2)
        {
            if(row < 2)
            {
                lcd_goto(row, col);
                lcd_data(' ');

                row++;

                lcd_goto(row, col);
                lcd_data(save);
            }
        }

        // LEFT
        else if(button == 3)
        {
            if(col > 1)
            {
                lcd_goto(row, col);
                lcd_data(' ');

                col--;

                lcd_goto(row, col);
                lcd_data(save);
            }
        }

        // RIGHT
        else if(button == 4)
        {
            if(col < 16)
            {
                lcd_goto(row, col);
                lcd_data(' ');

                col++;

                lcd_goto(row, col);
                lcd_data(save);
            }
        }
    }
}
