# Keypad-Controlled Stepper Motor Using 8051 Timer Interrupts

## Overview
An 8051-based implementation of a stepper motor control system with adjustable stepping speed through a 4×4 matrix keypad.

Timer 0 is used in Mode 1 (16-bit timer mode) to generate periodic interrupts. The interrupt service routine controls the motor stepping sequence, while keypad input allows the stepping interval to be changed during operation.

## Implementation Details
- **Microcontroller:** 8051
- **Timer:** Timer 0
- **Timer Mode:** Mode 1 (16-bit)
- **Timer Reload Value:** `0xDC00`
- **Stepper Motor Output:** Port 1
- **Keypad Interface:** 4×4 matrix keypad connected to Port 2
- **Interrupt:** Timer 0 Overflow Interrupt

## Keypad-Based Speed Control

Three keypad inputs are used to select the stepping interval:

| Key | Step Interval |
|---|---|
| 1 | 1 timer interrupt |
| 2 | 5 timer interrupts |
| 3 | 10 timer interrupts |

A smaller interval results in faster motor stepping, while a larger interval slows down the motor.

## Motor Stepping Sequence

The motor is driven using a repeating four-state coil sequence:

`0x08 → 0x04 → 0x02 → 0x01 → Repeat`

Each timer-controlled step updates Port 1 to activate the corresponding coil output.

## Working
1. Timer 0 is initialized in 16-bit Mode 1 and started with interrupts enabled.
2. The timer interrupt periodically reloads the timer and increments `timer_count`.
3. When `timer_count` reaches the selected `step_interval`, the counter resets and the motor advances by one step.
4. The main loop continuously scans the matrix keypad.
5. Pressing keys 1, 2, or 3 updates the stepping interval without stopping the timer.
6. The motor continues operating using the newly selected interval.

## Key Concepts
- 8051 timer configuration and interrupts
- Matrix keypad scanning
- GPIO input and output control
- Stepper motor coil sequencing
- Interrupt-driven motor control
- Runtime speed adjustment
- Non-blocking peripheral operation

## Design Notes
The implementation separates keypad scanning from motor control. The main loop handles user input, while the Timer 0 ISR handles periodic motor stepping.

This allows the motor to operate continuously while accepting speed adjustments through the keypad, without relying on software delay loops.
