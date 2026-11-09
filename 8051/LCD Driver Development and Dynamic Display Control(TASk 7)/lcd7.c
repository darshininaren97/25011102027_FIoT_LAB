/*#include <reg51.h>

#define LCD_PORT P3


/* =========================================================
   LCD CONNECTIONS
   ========================================================= */

sbit RS = P3^2;
sbit E  = P3^3;


/* =========================================================
   BUTTON CONNECTIONS
   ========================================================= */

sbit UP_ROW    = P2^3;
sbit DOWN_ROW  = P2^2;
sbit LEFT_ROW  = P2^1;
sbit RIGHT_ROW = P2^0;

sbit COL = P2^7;


/* =========================================================
   DELAY
   ========================================================= */

void delay_ms()
{
    unsigned int i, j;

    for(i = 0; i < 10; i++)
    {
        for(j = 0; j < 10; j++);
    }
}


/* =========================================================
   LCD ENABLE
   ========================================================= */

void lcd_enable()
{
    E = 1;
    delay_ms();
    E = 0;
    delay_ms();
}


/* =========================================================
   SEND 4-BIT NIBBLE
   ========================================================= */

void lcd_send_nibble(unsigned char nibble)
{
    LCD_PORT = (LCD_PORT & 0x0F) | (nibble & 0xF0);

    lcd_enable();
}


/* =========================================================
   SEND LCD COMMAND
   ========================================================= */

void lcd_cmd(unsigned char cmd)
{
    RS = 0;

    /* Higher nibble */
    lcd_send_nibble(cmd);

    /* Lower nibble */
    lcd_send_nibble(cmd << 4);

    delay_ms();
}


/* =========================================================
   SEND LCD DATA
   ========================================================= */

void lcd_data(unsigned char datas)
{
    RS = 1;

    /* Higher nibble */
    lcd_send_nibble(datas);

    /* Lower nibble */
    lcd_send_nibble(datas << 4);

    delay_ms();
}


/* =========================================================
   LCD INITIALIZATION
   ========================================================= */

void lcd_init()
{
    RS = 0;
    E = 0;

    delay_ms();

    /* 4-bit initialization sequence */

    lcd_send_nibble(0x30);
    delay_ms();

    lcd_send_nibble(0x30);
    delay_ms();

    lcd_send_nibble(0x30);
    delay_ms();

    lcd_send_nibble(0x20);
    delay_ms();


    /* 4-bit, 2-line, 5x8 font */

    lcd_cmd(0x28);


    /* Display ON, Cursor ON, Blink ON */

    lcd_cmd(0x0F);


    /* Cursor moves right */

    lcd_cmd(0x06);


    /* Clear display */

    lcd_cmd(0x01);

    delay_ms();
}


/* =========================================================
   MOVE LCD CURSOR
   ========================================================= */

void lcd_goto(unsigned char row, unsigned char col)
{
    unsigned char address;

    if(row == 1)
    {
        address = col - 1;
    }
    else
    {
        address = 0x40 + (col - 1);
    }

    lcd_cmd(0x80 | address);
}


/* =========================================================
   CHECK BUTTON
   ========================================================= */

unsigned char check_button()
{
    /* =====================================================
       UP
       ===================================================== */

    UP_ROW = 0;
    DOWN_ROW = 1;
    LEFT_ROW = 1;
    RIGHT_ROW = 1;

    COL = 1;

    if(COL == 0)
    {
        delay_ms();

        if(COL == 0)
        {
            while(COL == 0);

            return 1;
        }
    }


    /* =====================================================
       DOWN
       ===================================================== */

    UP_ROW = 1;
    DOWN_ROW = 0;
    LEFT_ROW = 1;
    RIGHT_ROW = 1;

    COL = 1;

    if(COL == 0)
    {
        delay_ms();

        if(COL == 0)
        {
            while(COL == 0);

            return 2;
        }
    }


    /* =====================================================
       LEFT
       ===================================================== */

    UP_ROW = 1;
    DOWN_ROW = 1;
    LEFT_ROW = 0;
    RIGHT_ROW = 1;

    COL = 1;

    if(COL == 0)
    {
        delay_ms();

        if(COL == 0)
        {
            while(COL == 0);

            return 3;
        }
    }


    /* =====================================================
       RIGHT
       ===================================================== */

    UP_ROW = 1;
    DOWN_ROW = 1;
    LEFT_ROW = 1;
    RIGHT_ROW = 0;

    COL = 1;

    if(COL == 0)
    {
        delay_ms();

        if(COL == 0)
        {
            while(COL == 0);

            return 4;
        }
    }


    return 0;
}


/* =========================================================
   MAIN
   ========================================================= */

void main()
{
    unsigned char button;

    unsigned char row = 1;
    unsigned char col = 1;


    /* Initialize buttons */

    UP_ROW = 1;
    DOWN_ROW = 1;
    LEFT_ROW = 1;
    RIGHT_ROW = 1;

    COL = 1;


    /* Initialize LCD */

    lcd_init();


    /* Clear LCD before use */
		
    lcd_cmd(0x01);

    /* Start cursor at row 1, column 1 */

    lcd_goto(row, col);


    while(1)
    {
        button = check_button();


        /* =================================================
           UP
           ================================================= */

        if(button == 1)
        {
            if(row > 1)
            {
                row--;

                lcd_goto(row, col);
            }
        }


        /* =================================================
           DOWN
           ================================================= */

        else if(button == 2)
        {
            if(row < 2)
            {
                row++;

                lcd_goto(row, col);
            }
        }


        /* =================================================
           LEFT
           ================================================= */

        else if(button == 3)
        {
            if(col > 1)
            {
                col--;

                lcd_goto(row, col);
            }
        }


        /* =================================================
           RIGHT
           ================================================= */

        else if(button == 4)
        {
            if(col < 16)
            {
                col++;

                lcd_goto(row, col);
            }
        }
    }
}*/
