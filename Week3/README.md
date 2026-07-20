# Week 3 — Build the Night Light

**Goal:** Assemble a complete useful device.

**Takeaway:** Inputs and outputs can be combined into a useful system.

---

## Recap

- Week 1: `digitalWrite()` — digital output.
- Week 2: `digitalRead()` / `analogRead()` — reading the world.

This week we combine both into a device that actually does something useful.

---

## Light Sensor

Your board is pre-wired — LDR on A5, button on pin 13, LED on pin 11, pot on A1.

![Button on pin 13, LED on pin 11, pot on A1, LDR on A5](../Week2/assets/button_pot_LDR.png)

Open the Serial Plotter (Tools → Serial Plotter) and move your hand over the sensor — you can see your range visually as the line rises and falls. Note the value when you fully cover the sensor and the value in normal room light. These are your **LO** and **HI** values; write them down — you will plug them into sketches later.

Try writing the sketch yourself, then check your work:
Reference: [light_sensor_read/light_sensor_read.ino](light_sensor_read/light_sensor_read.ino)

---

## Auto-on in Darkness

Use a threshold to make a decision: turn the LED on when it gets dark.

**Try it:** Cover the sensor with your hand — the LED turns on. Uncover it — the LED turns off.

**Challenge:** Adjust `THRESHOLD` so the LED only turns on when it gets very dark.

Try writing the sketch yourself, then check your work:
Reference: [auto_on/auto_on.ino](auto_on/auto_on.ino)

---

## Auto Brightness

Rather than fully on or fully off, make the LED get brighter as the room gets darker.

To control brightness we use `analogWrite()` — this is what was demonstrated at the start of class. It works on PWM-capable pins, marked `~` on the board (3, 5, 6, 9, 10, 11):

```cpp
analogWrite(pin, brightness);  // 0 = off, 255 = full brightness
```

> Curious how it works? See [PWM.md](PWM.md).

Update `LO` and `HI` in the sketch with the values you noted from the Serial Plotter.

Try writing the sketch yourself, then check your work:
Reference: [auto_brightness/auto_brightness.ino](auto_brightness/auto_brightness.ino)

`constrain(value, min, max)` clamps a value so it never goes outside the allowed range — a useful safety net after `map()`.

---

## Manual Override

A useful night light needs a way to override automatic mode. The button is on pin 13.

Logic:
- If the button is held → LED full brightness, regardless of light level.
- Otherwise → automatic mode (smooth brightness from the light sensor).

Try writing the sketch yourself, then check your work:
Reference: [manual_override/manual_override.ino](manual_override/manual_override.ino)

---

## Auto / Manual Modes

Give the button a more deliberate role: toggle between automatic and always-on modes.

This introduces **edge detection** — responding to a change in state rather than a held state. A key technique in electronics.

> Two variables (`manualMode` and `lastButton`) are declared outside `loop()` — they need to keep their value between each run of the loop.

> **If your mode toggle misfires:** that's button bounce (see Week 2). The `delay(50)` in the sketch already helps — increase it to 100–150 if needed.

Try writing the sketch yourself, then check your work:
Reference: [night_light/night_light.ino](night_light/night_light.ino)

---

## Night-light connection

> Today we built a functioning smart night light.

---

## Challenge — Night Light v2

If you have finished early and want a harder problem, build a more capable version from scratch. There are no sketches for this one — use what you have learned and figure out the rest.

**Requirements:**

1. The built-in LED (pin 13) is always on whenever the board is powered.
2. A button cycles through four modes: **OFF**, **ALWAYS ON**, **THRESHOLD**, and **AUTO**.
3. In ALWAYS ON mode the pot controls brightness.
4. In THRESHOLD mode the LED turns on when the room gets dark enough, and off when it gets bright — no dimming.
5. In AUTO mode brightness tracks darkness smoothly via the light sensor.
6. A different colored LED lights up to show which mode is currently active.

**Stretch goal:** Accept a command typed into the Serial Monitor — `off`, `on`, `threshold`, or `auto` — to switch modes without pressing the button. Use a newline character as the end of each command.

> **Hint for the stretch goal:** There are two ways to read serial input: `Serial.readStringUntil('\n')` and `Serial.available()`. One of them will cause your button to stop working. Figure out which one and why.

---

## Key terms

| Term | Meaning |
|------|---------|
| PWM | Pulse Width Modulation — pulses a digital pin on and off very fast; LEDs and motors respond to the average power, so varying the pulse width gives real control over brightness and speed |
| Duty cycle | Fraction of time a PWM signal spends HIGH |
| `analogWrite()` | Set PWM duty cycle (0–255) on a PWM-capable pin |
| `constrain()` | Clamp a value to a min/max range |
| Edge detection | Responding to a transition (LOW→HIGH or HIGH→LOW) rather than a held state |
| Auto / manual mode | Two operating behaviors selectable at runtime |
