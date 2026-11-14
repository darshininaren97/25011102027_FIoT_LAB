# Timer 1 Interrupt-Driven Output Generation

## Overview
A simple 8051-based implementation that uses Timer 1 in Mode 1 (16-bit timer mode) to generate a periodic digital output signal on pin P1.1.

The output is controlled entirely through timer interrupts rather than software delay loops. Each interrupt reloads the timer, updates the output state, and advances a counter to produce a repeating sequence.

## Implementation Details
- **Microcontroller:** 8051 / AT89S52
- **Timer:** Timer 1
- **Timer Mode:** Mode 1 (16-bit)
- **Output Pin:** P1.1
- **Interrupt:** Timer 1 Overflow Interrupt
- **Timer Reload Value:** `0xFC66`
- **Output Sequence:** HIGH for one interrupt interval, LOW for the next seven intervals.

## Working
1. Timer 1 is configured in 16-bit mode.
2. The timer is loaded with `0xFC66` and started.
3. On every timer overflow, the interrupt service routine reloads the timer.
4. The counter determines the output state:
   - `count == 0`: Output HIGH.
   - Otherwise: Output LOW.
5. The counter increments on every interrupt and resets after reaching 8, repeating the sequence.

## Key Concepts
- 16-bit timer configuration
- Timer overflow interrupts
- Interrupt service routines (ISR)
- Register-level peripheral configuration
- Periodic digital signal generation
- Counter-based output control

## Design Notes
The main loop remains empty because all output operations are handled by the Timer 1 interrupt service routine. This avoids software-based delay loops and keeps the timing mechanism interrupt-driven.

The actual output frequency and timing depend on the microcontroller clock frequency and timer configuration.
