# PWM — Controlling Brightness

*(Instructor-led demo)*

Last week the auto-on night light could only switch the LED fully on or off. To make brightness track the light level smoothly we need a different technique: **Pulse Width Modulation (PWM)**.

---

## Step 1 — The pulsing loop

A fast on/off loop — the same as Blink from Week 1, just much faster:

Sketch: [pwm_flicker/pwm_flicker.ino](pwm_flicker/pwm_flicker.ino)

At 50 Hz the LED flickers noticeably. Halve the delays — the flicker fades. Halve again — almost gone. The LED is pulsing the whole time; it only looks steady when the pulses are too fast to see.

> **Demo:** Record in slow-motion (120 fps+) to see the individual on/off pulses clearly.

---

## Step 2 — Duty cycle

Two pots let you control frequency and duty cycle live:

| Pot | Pin | Controls |
|-----|-----|----------|
| Left | A0 | Period: 5 ms (200 Hz, smooth) to 300 ms (3 Hz, clearly blinking) |
| Right | A1 | Duty cycle: 0% (always off) to 100% (always on) |

Sketch: [pwm_duty_cycle/pwm_duty_cycle.ino](pwm_duty_cycle/pwm_duty_cycle.ino)

**Demo flow:**
1. Turn the frequency pot to max (slow — ~3 Hz). The LED blinks visibly.
2. Turn the duty cycle pot and watch the on/off fraction change in real time.
3. Try 25%, 50%, 75% — notice the brightness changes even though the LED is still switching fully on and off.
4. Slowly crank the frequency pot back toward min. The flicker fades; at ~200 Hz it looks like smooth brightness control.

```
100% duty cycle:  ████████████  (always on, full brightness)
 50% duty cycle:  ██░░██░░██░░  (half brightness)
 25% duty cycle:  █░░░█░░░█░░░  (quarter brightness)
```

The key insight: the LED never changes how bright it gets — it only changes *how long* it stays on each cycle. Persistence of vision does the rest.

---

## Step 3 — Full software fade

Now vary the duty cycle continuously to fade in and out:

Sketch: [pwm_soft_fade/pwm_soft_fade.ino](pwm_soft_fade/pwm_soft_fade.ino)

It works — but the MCU is doing nothing but toggle a pin. It can't read a sensor or respond to a button while this runs.

---

## Step 4 — Hardware PWM

Six pins (marked `~` on the board: 3, 5, 6, 9, 10, 11) have dedicated hardware timers. Set the duty cycle once; the hardware handles the pulsing. The MCU is free.

```cpp
analogWrite(9, 128);  // 0 = off, 255 = full brightness, 128 = ~50%
```

Sketch: [pwm_analog_write/pwm_analog_write.ino](pwm_analog_write/pwm_analog_write.ino)

Same fade as the software version — in a handful of lines.

> **Note:** Despite the name, `analogWrite()` is still pulsing the pin on and off at ~490 Hz. But LEDs and motors only care about average power, so the result is real brightness and real speed control. The hardware just does the toggling so you don't have to.
