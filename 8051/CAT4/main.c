

#include<stdio.h>
#include<reg51.h>

// Function Prototypes
void delay();
void setLEDs(unsigned char val,int mode);
void running_led(int mode);
void binary_counter(int mode);
void alternate_led(int mode);
void blink_all(int mode);
void led_control(int key);
void display_digit(int digit);
void keypad_scan();

// LED definitions
sbit LED1 = P1^0;
sbit LED2 = P1^1;
sbit LED3 = P1^2;
sbit LED4 = P1^3;

// Seven Segment Display
sbit a  = P0^0;
sbit b  = P0^1;
sbit c  = P0^2;
sbit d  = P0^3;
sbit e  = P0^4;
sbit f  = P0^5;
sbit g  = P0^6;

// Row pins (Output)
sbit ROW1 = P2^7;
sbit ROW2 = P2^6;
sbit ROW3 = P2^5;
sbit ROW4 = P2^4;

// Column pins (Input)
sbit COL1 = P2^3;
sbit COL2 = P2^2;
sbit COL3 = P2^1;

// Pattern variables
unsigned char mode = 0;
unsigned char run_index = 0;
unsigned char binary_count = 0;
unsigned char alt_index = 0;
bit blink_toggle = 0;

// Delay Function
void delay()
{
    unsigned int i,j;
    for(i=0;i<100;i++)
        for(j=0;j<500;j++);
}

void setLEDs(unsigned char val,int mode)
{ 
	display_digit(mode);
    LED1 = val & 0x01;
    LED2 = (val>>1) & 0x01;
    LED3 = (val>>2) & 0x01;
    LED4 = (val>>3) & 0x01;
}

void running_led(int mode)
{
	display_digit(mode);
    setLEDs(1<<run_index,mode);
    run_index=(run_index+1)%4;
}

void binary_counter(int mode)
{
	display_digit(mode);
    setLEDs(binary_count,mode);
    binary_count=(binary_count+1)%16;
}

void alternate_led(int mode)
{
    unsigned char pattern[2]={0x0A,0x05};

    setLEDs(pattern[alt_index],mode);

    alt_index=(alt_index+1)%2;
}

void blink_all(int mode)
{
    if(blink_toggle)
        setLEDs(0x0F,mode);
    else
        setLEDs(0x00,mode);

    blink_toggle=!blink_toggle;
}

// LED Control Function
void led_control(int key)
{
    // Turn OFF all LEDs first
    LED1=0;
    LED2=0;
    LED3=0;
    LED4=0;

    switch(key)
    {
        case 1:
            mode = 1;
						display_digit(1);
            break;

        case 2:
            mode = 2;
						display_digit(2);
            break;

        case 3:
            mode = 3;
						display_digit(3);
            break;

        case 4:
            mode = 4;
						display_digit(4);
            break;

        case 5:
            mode = 5;
						display_digit(5);
            break;

        case 6:
            mode = 6;
						display_digit(6);
            break;

        case 7:
            mode = 7;
						display_digit(7);
            break;

        case 8:
            mode = 8;
						display_digit(8);
            break;

        case 9:
            mode = 9;
						display_digit(9);
            break;

        case 0:
            mode = 0;
						display_digit(0);
            break;
    }
}

// Seven Segment Display Function
void display_digit(int digit)
{
    // Turn OFF all segments first
    a=0;
    b=0;
    c=0;
    d=0;
    e=0;
    f=0;
    g=0;

    switch(digit)
    {
        case 0:
            a=1; b=1; c=1; d=1; e=1; f=1;
            break;

        case 1:
            b=1; c=1;
            break;

        case 2:
            a=1; b=1; d=1; e=1; g=1;
            break;

        case 3:
            a=1; b=1; c=1; d=1; g=1;
            break;

        case 4:
            b=1; c=1; f=1; g=1;
            break;

        case 5:
            a=1; c=1; d=1; f=1; g=1;
            break;

        case 6:
            a=1; c=1; d=1; e=1; f=1; g=1;
            break;

        case 7:
            a=1; b=1; c=1;
            break;

        case 8:
            a=1; b=1; c=1; d=1; e=1; f=1; g=1;
            break;

        case 9:
            a=1; b=1; c=1; d=1; f=1; g=1;
            break;
    }
}

// Keypad Scan Function
void keypad_scan()
{
    int i;

    // Initialize Seven Segment
    a=0;
    b=0;
    c=0;
    d=0;
    e=0;
    f=0;
    g=0;
    //dp=0;

    // Make all rows HIGH
    ROW1=1;
    ROW2=1;
    ROW3=1;
    ROW4=1;

    for(i=1;i<=4;i++)
    {
        switch(i)
        {
        case 1:
        {
            ROW1=0;

            if(COL1==0)
            {
                delay();
                if(COL1==0)
                {
                    //b=1;
                    //c=1;
                    //LED1=1;
                    led_control(1);
                    
                    while(COL1==0);
                }
            }

            if(COL2==0)
            {
                delay();
                if(COL2==0)
                {
                    led_control(2);
                    
                    while(COL2==0);
                }
            }

            if(COL3==0)
            {
                delay();
                if(COL3==0)
                {
                    led_control(3);
                    
                    while(COL3==0);
                }
            }

            ROW1=1;
            break;
        }

        case 2:
        {
            ROW2=0;

            if(COL1==0)
            {
                delay();
                if(COL1==0)
                {
                    led_control(4);
                    
                    while(COL1==0);
                }
            }

            if(COL2==0)
            {
                delay();
                if(COL2==0)
                {
                    led_control(5);
                    
                    while(COL2==0);
                }
            }

            if(COL3==0)
            {
                delay();
                if(COL3==0)
                {
                    led_control(6);
                    
                    while(COL3==0);
                }
            }

            ROW2=1;
            break;
        }

        case 3:
        {
            ROW3=0;

            if(COL1==0)
            {
                delay();
                if(COL1==0)
                {
                    led_control(7);
                    
                    while(COL1==0);
                }
            }

            if(COL2==0)
            {
                delay();
                if(COL2==0)
                {
                    led_control(8);
                    
                    while(COL2==0);
                }
            }

            if(COL3==0)
            {
                delay();
                if(COL3==0)
                {
                    led_control(9);
                    
                    while(COL3==0);
                }
            }

            ROW3=1;
            break;
        }

        case 4:
        {
            ROW4=0;

            if(COL2==0)
            {
                delay();
                if(COL2==0)
                {
                    led_control(0);
                   
                    while(COL2==0);
                }
            }

            ROW4=1;
            break;
        }

        }
    }
}

// Main Function
void main()
{
    mode = 0;

    LED1=0;
    LED2=0;
    LED3=0;
    LED4=0;

    a=0;
    b=0;
    c=0;
    d=0;
    e=0;
    f=0;
    g=0;
    //dp=0;

    while(1)
    {
        keypad_scan();

        switch(mode)
        {
            case 1:
                setLEDs(0x01,mode);
						
                break;

            case 2:
                setLEDs(0x02,mode);
                break;

            case 3:
                setLEDs(0x04,mode);
                break;

            case 4:
                setLEDs(0x08,mode);
                break;

            case 5:
                running_led(mode);
                break;

            case 6:
                alternate_led(mode);
                break;

            case 7:
                binary_counter(mode);
                break;

            case 8:
                blink_all(mode);
                break;

            case 9:
                setLEDs(0x00,mode);
                break;

            case 0:
                setLEDs(0x00,mode);
                run_index = 0;
                binary_count = 0;
                alt_index = 0;
                blink_toggle = 0;
                break;
        }

        delay();
    }
}
