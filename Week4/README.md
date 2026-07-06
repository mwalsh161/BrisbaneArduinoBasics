# Week 4 — Make It Smart / Extension Day

**Goal:** Add polish and personalization.

**Takeaway:** Small changes in software can create much richer behavior.

---

## Recap

We have a working night light. This week we make it feel finished — and explore where you can take it next.

---

## Timing Without Blocking

So far we've used `delay()` to wait. The problem: while the Arduino is waiting, it can't do anything else — read a button, update another output, respond to a sensor.

**`millis()`** returns the number of milliseconds since the Arduino started. Use it to check if enough time has passed without stopping the program.

Sketch: [non_blocking/non_blocking.ino](non_blocking/non_blocking.ino)

This pattern is called **non-blocking timing** and is fundamental to any project that needs to do more than one thing at once.

---

## Fade On / Off

Use `millis()` and `analogWrite()` to smoothly fade an LED in and out.

Sketch: [fade/fade.ino](fade/fade.ino)

---

## Stay On After Activation

A useful night light behaviour: stay lit for a set time after someone presses the button, then fade off.

Sketch: [hold_on/hold_on.ino](hold_on/hold_on.ino)

Press the button and the light stays on for 5 seconds. Press again before it expires and the timer resets.

---

## Modes and Behavior

Combine ideas from this week into a multi-mode night light:

| Mode | Behavior |
|------|----------|
| Auto | Light sensor controls LED |
| Hold | On at full brightness for a timed period |
| Fade | Slowly pulses on and off |

Use a button to cycle through modes. Store the current mode in a variable.

```cpp
int mode     = 0;          // 0 = auto, 1 = hold, 2 = fade.
bool lastBtn = HIGH;

void loop() {
  bool btn = digitalRead(BUTTON_PIN);

  if (lastBtn == HIGH && btn == LOW) {
    mode = (mode + 1) % 3;  // Cycle 0 → 1 → 2 → 0.
  }
  lastBtn = btn;

  if (mode == 0) { /* auto logic */ }
  if (mode == 1) { /* hold logic */ }
  if (mode == 2) { /* fade logic */ }
}
```

This is a simple **state machine** — the program's behaviour depends on which state it's in, and events (button presses, timers) trigger transitions between states.

---

## Advanced Extensions

These activities go further — pick what interests you.

### Transistor — Voltage-Controlled Switch

A transistor lets a small voltage on one terminal control a larger current through the other two. Wire one up with an LED to see the concept before any code is involved.

**NPN transistor (e.g. 2N2222 or BC547):**

![NPN transistor with LED: 5V → 220Ω → LED → collector; emitter → GND; base → 1kΩ → control wire](wiring-transistor-led.png)

| Terminal | Role |
|----------|------|
| Base | Control input — apply voltage here to switch it on |
| Collector | Current flows in from the load |
| Emitter | Current flows out to GND |

Wire an LED and 220Ω resistor from 5V to the collector, emitter to GND. Leave the base disconnected — the LED is off. Now touch a wire from 5V to the base through a 1kΩ resistor. The LED turns on.

The key difference from Week 1: in Week 1, the wire you plugged and unplugged was in series with the LED and carrying its full current. Here, the wire to the base carries almost none — you're providing a voltage signal, not powering the LED. The LED current flows through the collector–emitter path; the base just opens or closes the gate.

Replace that wire with a digital pin and the Arduino can switch any load regardless of how much current it draws.

Now swap the static 5V wire for pin 9 and run the fade sketch — the LED dims and brightens through the transistor. The code is identical to driving the LED directly; the transistor is invisible to the Arduino.

Sketch: [fade/fade.ino](fade/fade.ino)

### Servo as a brightness gauge

A servo motor turns to a position set by your program. Map the light sensor reading to a servo angle to create a visual meter.

Sketch: [servo_gauge/servo_gauge.ino](servo_gauge/servo_gauge.ino)

One sensor signal driving two different outputs (LED and servo) — that's a core engineering pattern.

The servo draws its power from the 5V pin, not the signal pin — it needs more current than a digital output can supply. For DC motors or other high-current loads, a transistor or motor driver fills that same role: the Arduino sends a small signal, the external component does the heavy lifting.

### Multiple LEDs

Add a second or third LED on different PWM pins. Use them to show different things simultaneously — one for auto/manual mode, one for the actual light output.

### Buzzer notifications

A passive buzzer on a digital pin can play tones.

```cpp
tone(8, 440, 200);  // Pin 8, 440 Hz (A4), for 200 ms.
```

Use it to beep when the mode changes, or when the light level crosses a threshold.

### Servo mode indicator

Move the servo to a different angle for each mode rather than tracking light level — a physical mode display with no screen required.

---

## Night-light connection

> Today we turned a simple device into a product.

---

## What's next?

You now have the foundation to build almost anything with an Arduino:

- **More sensors:** temperature, ultrasound distance, infrared, humidity.
- **Displays:** LCD screens, OLED panels, 7-segment digits.
- **Communication:** send data over WiFi or Bluetooth (with boards like the Arduino Nano 33 IoT).
- **Motors:** control speed and direction with motor driver shields.

The best next step: buy a starter kit and pick a small project that solves a real problem for you.

---

## Key terms

| Term | Meaning |
|------|---------|
| `millis()` | Returns ms elapsed since the board started; used for non-blocking timing |
| Non-blocking timing | Checking elapsed time without halting the program |
| State machine | Code structure where behaviour depends on the current state |
| `tone()` | Play a frequency on a pin (buzzer) |
| Servo | Motor that turns to a commanded angle (0–180°) |
| Duty cycle | Fraction of time a PWM signal is HIGH |
