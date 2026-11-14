# Variable Duty Cycle PWM Generation – 8051

This program generates a PWM signal on **P1.0** using Timer 1 interrupts. The duty cycle gradually increases from 0% to 100% and then decreases back to 0%, producing an LED fading effect.

## Implementation

- Timer 1 is configured in **Mode 1 (16-bit timer mode)** using `TMOD = 0x10`.
- Timer 1 interrupts are enabled using `ET1 = 1`.
- Global interrupts are enabled using `EA = 1`.
- The timer is started using `TR1 = 1`.
- Timer 1 is reloaded with `TH1 = 0xFF` and `TL1 = 0xF7` on every interrupt.

## PWM Generation

Software PWM is implemented using two variables:

- `pwm_count`: Tracks the current position within a PWM cycle (0–99).
- `duty`: Determines how many counts the LED remains HIGH during each cycle.

The LED output is controlled by comparing `pwm_count` with `duty`:

- If `pwm_count < duty`, P1.0 is set HIGH.
- Otherwise, P1.0 is set LOW.

Each PWM cycle consists of 100 timer interrupts, giving a duty-cycle resolution of 1%.

## Duty Cycle Variation

The duty cycle is updated using `fade_count` and `direction`.

- `fade_count` counts completed PWM cycles.
- The duty cycle changes after every 10 PWM cycles.
- When `direction = 1`, the duty cycle increases until it reaches 100%.
- When `direction = 0`, the duty cycle decreases until it reaches 0%.
- The direction reverses at both limits, creating a continuous fading effect.

## Output

The LED connected to P1.0 gradually brightens as the duty cycle increases and gradually dims as it decreases. The process repeats continuously.
