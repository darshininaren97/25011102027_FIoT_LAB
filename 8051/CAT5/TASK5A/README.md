# Task 5A – Timer Interrupt-Based LED Control

## Objective
Design an LED control system using the 8051 microcontroller in which a hardware timer periodically generates interrupts to toggle an LED without using software delay loops.

## Hardware Connections
- **LED:** P1.0
- Connect the LED through a suitable current-limiting resistor.

## Working Principle
1. Timer 0 is configured in Mode 1 (16-bit timer mode).
2. The timer is loaded with `0xFC66` to generate an approximately 1 ms interval (depending on the oscillator frequency).
3. Timer 0 interrupts are enabled using `ET0`, and global interrupts are enabled using `EA`.
4. The timer is started using `TR0`.
5. Whenever Timer 0 overflows, the interrupt service routine reloads the timer and increments the counter.
6. After 1000 interrupts, the LED connected to P1.0 is toggled and the counter is reset.

The main program remains in an infinite loop while the timer interrupt independently handles LED toggling.

## Program Details
- **Microcontroller:** 8051
- **Timer:** Timer 0
- **Timer Mode:** Mode 1 (16-bit)
- **Interrupt:** Timer 0 overflow interrupt
- **Output:** LED on P1.0
- **Programming Language:** Embedded C
-**IDE:** Keil µVision
  
## Circuit Diagram

