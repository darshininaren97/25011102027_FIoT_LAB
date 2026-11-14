# Variable Frequency Square Wave Generation – 8051

This program generates a square wave on **P1.1** using Timer 1 interrupts of the 8051 microcontroller. The output frequency is controlled by changing the timer reload values.

## Implementation

- Timer 1 is configured in **Mode 1 (16-bit timer mode)** using `TMOD = 0x10`.
- Timer 1 overflow interrupts are enabled using `ET1 = 1`.
- Global interrupts are enabled using `EA = 1`.
- The timer is started using `TR1 = 1`.
- On every Timer 1 interrupt, the timer is reloaded and P1.1 is toggled.

## Frequency Configuration

The `set_frequency()` function selects different timer reload values based on the requested mode.

| Mode | TH1 | TL1 |
|---|---|---|
| 1 | `0xEE` | `0x00` |
| 2 | `0xFC` | `0x66` |
| 3 | `0xFE` | `0x33` |
| 4 | `0xFF` | `0x1A` |
| 5 | `0xFF` | `0xA4` |

The selected values are stored in `reload_high` and `reload_low`, which are used by the Timer 1 ISR.

## Timer Interrupt

The interrupt service routine:
1. Reloads TH1 and TL1 with the selected values.
2. Toggles the output pin P1.1.

Repeated toggling produces a square wave. Changing the reload values changes the timer overflow interval and consequently the output frequency.

## Notes

- The initial reload values are `0xFE33`.
- The `set_frequency()` function is defined but is not called in the current `main()` function.
- Frequency selection through keypad input is indicated as a possible extension in the code but is not implemented.
