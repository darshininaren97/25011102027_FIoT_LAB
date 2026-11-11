
/*The following program is written to compile a minimal bare-metal C program, program the device, and control an LED by directly accessing 
the microcontroller's memory-mapped GPIO registers*/

#include<stdio.h>
#include<reg51.h>


sbit ledpin=P1^0;

//Defining and declaring the delay function
void delay(){
	int i,j;
	for(i=0;i<500;i++){
		for(j=0;j<500;j++){
		}
	}
}

//Main function
void main(){
  while(1){
    ledpin=1;
    delay();
    ledpin=0;
    delay();
  }
}
