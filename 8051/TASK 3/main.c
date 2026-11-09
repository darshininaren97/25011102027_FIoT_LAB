/*The following program is made to design and implement a bare-metal Embedded C and direct memory-mapped register access, develop a four-state LED control system. 
Each valid button press advances the system to the next operating mode: running LED pattern, binary counter, alternating pattern, and all-LED flashing */

#include <reg51.h>
#include <stdio.h>

//LED definitions
sbit LED1 = P1^0;
sbit LED2 = P1^2;
sbit LED3 = P1^3;
sbit LED4 = P1^4;

//Button pins definitions
sbit ROW = P2^3;   // Output
sbit COL = P2^7;   // Input

//defining a variable to track the mode 
unsigned char mode = 0;

//Variables to track the state of each mode
unsigned char m1_index = 0;					//This tracks the current led position 0 1 2 3
unsigned char m2_count = 0;					//This tracks the binary number at which it is in 0-15
unsigned char m3_index = 0;					//This tracks which alternate it is in
bit m4_toggle = 0;									//This tracks if it is on or off

//Delay
void delay(){
  unsigned int i, j;
	for(i = 0; i < 100; i++)
		for(j = 0; j < 500; j++);
}

//assign the bits of the port to each LED
void setLEDs(unsigned char val){
	LED1 = val & 0x01;
  LED2 = (val >> 1) & 0x01;
  LED3 = (val >> 2) & 0x01;
  LED4 = (val >> 3) & 0x01;
}

//Debouncing
void checkButton(){
	ROW = 0;  
  COL = 1;   
  if (COL == 0){
		delay();          
    if (COL == 0){
			while (COL == 0){}; //Waiting for release
			mode++;
      if (mode>3) mode = 0;
    }
  }
}

//Mode 1 - running leds
void mode1(){
	setLEDs(1 << m1_index);
  m1_index = (m1_index + 1) % 4;
}

//Mode 2 - binary counter
void mode2(){
	setLEDs(m2_count);
  m2_count = (m2_count + 1) % 16;
}

//Mode 3 - alternating mode
void mode3(){
  unsigned char pattern[2] = {0x0A, 0x05}; // 1010, 0101
  setLEDs(pattern[m3_index]);
	m3_index = (m3_index + 1) % 2;
}

//Mode 4 - full flash
void mode4(){
  if (m4_toggle)
		setLEDs(0x0F);
  else
    setLEDs(0x00);

	m4_toggle = !m4_toggle;
}

//Main 
void main(){
	// initially setting everything as off
  setLEDs(0x00);

  while(1){
		checkButton();   // ALWAYS check first

    switch(mode){
			case 0: mode1(); break;
      case 1: mode2(); break;
			case 2: mode3(); break;
			case 3: mode4(); break;
    }

    delay();   // Controls speed (non-blocking step delay)
  }
}
