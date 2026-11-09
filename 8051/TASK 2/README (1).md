# Bare-Metal LED Control using 8051 (AT89S52)

## Objective  

To compile a minimal **bare-metal C program**, program the device, and control an LED by directly accessing the microcontroller’s **memory-mapped GPIO registers**, without using any high-level libraries.

---

## Constraints  
- No Arduino APIs  
- No HAL libraries  
- No RTOS services  
- Only direct register-level programming  

---

## Hardware Requirements  
- AT89S52 Microcontroller Development Board  
- LED  
- Resistor (1 kΩ)  
- Breadboard  
- Jumper wires  
- Power supply  

---

## Software Requirements  
- Keil C51 Compiler  
- Programmer/Debugger (for flashing code)  

---

## Hardware Bring-Up  
- Identified the microcontroller: **AT89S52 (8051 family)**  
- Verified board power supply using a multimeter  
- Identified LED GPIO pin from schematic  
- Established communication between host PC and MCU  

---

## GPIO Configuration  
The LED is connected to a GPIO pin of **Port 1**.  
The pin is configured as an output by writing directly to the port register.

---

## Working Principle  
- GPIO pins in 8051 are **memory-mapped registers**  
- Writing `1` or `0` to a pin controls the voltage level  
- LED turns ON/OFF based on the output state  

---

## Delay Implementation  
A simple **software delay loop** is used instead of hardware timers to create a visible blinking effect.

---

## Program Logic  
1. Initialize LED pin  
2. Continuously toggle LED state  
3. Introduce delay between toggles  
4. Repeat indefinitely  

---END---
