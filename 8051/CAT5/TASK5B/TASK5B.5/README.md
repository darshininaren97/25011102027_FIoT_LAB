# Timer 1 Interrupt-Driven Burst Signal Generation

## Overview
An 8051-based implementation that generates a burst-type digital signal using Timer 1 interrupts. The output is controlled through a repeating sequence of three phases: an initial toggling period, a forced LOW period, and a final toggling period.

The entire signal generation is handled by the timer interrupt service routine without using software delay loops.

## Implementation Details
- **Microcontroller:** 8051 / AT89S52
- **Timer:** Timer 1
- **Timer Mode:** Mode 1 (16-bit timer)
- **Output Pin:** P1.1
- **Interrupt:** Timer 1 Overflow Interrupt
- **Timer Reload Value:** `0xFC66`
- **Sequence Length:** 30 timer interrupts

## Signal Sequence

The output follows three phases in each repeating cycle:

| Counter Range | Output Behaviour |
|---|---|
| 0–9 | Output toggles on every interrupt |
| 10–19 | Output is held LOW |
| 20–29 | Output toggles on every interrupt |

After 30 interrupts, the counter resets to zero and the sequence repeats.

## Working
1. Timer 1 is configured in 16-bit Mode 1.
2. The timer is periodically reloaded with `0xFC66`.
3. Each overflow triggers the Timer 1 interrupt service routine.
4. The counter determines which phase of the burst sequence is active.
5. The output is toggled or forced LOW depending on the current counter value.
6. Once the counter reaches 30, it resets and begins a new cycle.

## Key Concepts
- 8051 timer configuration
- Timer overflow interrupts
- Interrupt-driven signal generation
- Digital output toggling
- Burst and pulse sequence generation
- Counter-based timing control

## Design Notes
The main loop remains empty, with all signal generation performed inside the Timer 1 ISR. This provides a periodic, interrupt-driven approach to generating a repeating burst pattern without blocking software delays.

The actual timing and output frequency depend on the oscillator frequency and timer configuration.
