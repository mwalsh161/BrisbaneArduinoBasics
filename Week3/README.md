# Week 3 — Build the Night Light

**Goal:** Assemble a complete useful device.

**Takeaway:** Inputs and outputs can be combined into a useful system.

---

## Recap

- Week 1: `digitalWrite()` — digital output.
- Week 2: `digitalRead()` / `analogRead()` — reading the world.

This week we combine both into a device that actually does something useful.

---

## PWM — Controlling Brightness

*(Instructor-led demo — students observe)*

Last week the auto-on night light could only switch the LED fully on or off. To make brightness track the light level smoothly we need a different technique: **Pulse Width Modulation (PWM)**.

### Step 1 — The pulsing loop

A fast on/off loop — the same as Blink from Week 1, just much faster:

Sketch: [pwm_flicker/pwm_flicker.ino](pwm_flicker/pwm_flicker.ino)

At 50 Hz the LED flickers noticeably. Halve the delays — the flicker fades. Halve again — almost gone. The LED is pulsing the whole time; it only looks steady when the pulses are too fast to see.

> **Demo:** Record in slow-motion (120 fps+) to see the individual on/off pulses clearly.

### Step 2 — Duty cycle

Keep the total period fixed. Change the on/off ratio — the **duty cycle**:

Sketch: [pwm_duty_cycle/pwm_duty_cycle.ino](pwm_duty_cycle/pwm_duty_cycle.ino)

`ON_MS + OFF_MS` stays at 20 ms throughout. Try:
- `ON_MS = 2, OFF_MS = 18` — very dim (10%)
- `ON_MS = 10, OFF_MS = 10` — half brightness (50%)
- `ON_MS = 18, OFF_MS = 2` — near full (90%)

```
100% duty cycle:  ████████████  (always on, full brightness)
 50% duty cycle:  ██░░██░░██░░  (half brightness)
 25% duty cycle:  █░░░█░░░█░░░  (quarter brightness)
```

### Step 3 — Full software fade

Now vary the duty cycle continuously to fade in and out:

Sketch: [pwm_soft_fade/pwm_soft_fade.ino](pwm_soft_fade/pwm_soft_fade.ino)

It works — but the MCU is doing nothing but toggle a pin. It can't read a sensor or respond to a button while this runs.

### Step 4 — Hardware PWM

Six pins (marked `~` on the board: 3, 5, 6, 9, 10, 11) have dedicated hardware timers. Set the duty cycle once; the hardware handles the pulsing. The MCU is free.

```cpp
analogWrite(9, 128);  // 0 = off, 255 = full brightness, 128 = ~50%.
```

Sketch: [pwm_analog_write/pwm_analog_write.ino](pwm_analog_write/pwm_analog_write.ino)

Same fade as the software version — in a handful of lines.

> **Note:** Despite the name, `analogWrite()` does not produce a true analog voltage. It's still a digital signal, pulsing at ~490 Hz. The hardware just does the toggling so you don't have to.

---

## Light Sensor

Wire a photoresistor (LDR) and 10kΩ resistor as a voltage divider on A0 (same as Week 2).

Read the light level and print it to the Serial Monitor to understand the range in your environment:

Sketch: [light_sensor_read/light_sensor_read.ino](light_sensor_read/light_sensor_read.ino)

Note the readings in bright light and when you cover the sensor with your hand. These will be your calibration reference.

---

## Auto-on in Darkness

Combine the light reading with PWM output:

Sketch: [auto_on/auto_on.ino](auto_on/auto_on.ino)

**Try it:** Cover the sensor with your hand — the LED turns on. Uncover it — the LED turns off.

---

## Manual Override Button

A useful night light needs a way to override the automatic mode. Wire a button to pin 2 with `INPUT_PULLUP`.

Logic:
- If the button is held → LED on regardless of light level.
- Otherwise → automatic mode (light sensor controls LED).

Sketch: [manual_override/manual_override.ino](manual_override/manual_override.ino)

---

## Activity — Auto brightness

Rather than a simple on/off, map the light level directly to LED brightness so the LED gets brighter as the room gets darker.

Sketch: [auto_brightness/auto_brightness.ino](auto_brightness/auto_brightness.ino)

`constrain(value, min, max)` clamps a value so it never goes outside the allowed range — a useful safety net after `map()`.

---

## Auto / Manual modes

Give the button a more deliberate role: toggle between automatic and always-on modes.

Sketch: [night_light/night_light.ino](night_light/night_light.ino)

This introduces **edge detection** — responding to a change in state rather than a held state. A key technique in interactive hardware.

> **If your mode toggle misfires:** that's button bounce (see Week 2). The `delay(50)` in the sketch already helps — increase it to 50–100 if needed.

---

## Night-light connection

> Today we built a functioning smart night light.

---

## Key terms

| Term | Meaning |
|------|---------|
| PWM | Pulse Width Modulation — simulates analog output by pulsing a digital pin |
| Duty cycle | Fraction of time a PWM signal spends HIGH |
| `analogWrite()` | Set PWM duty cycle (0–255) on a PWM-capable pin |
| `constrain()` | Clamp a value to a min/max range |
| Edge detection | Responding to a transition (LOW→HIGH or HIGH→LOW) rather than a held state |
| Auto / manual mode | Two operating behaviors selectable at runtime |
