# 4-independent-buttons

Mbed OS 6 example + small reusable button driver for **4 independent buttons** (active-low with pull-ups).

## What’s included
- `Button` class (debounce + edge detection)
- `ButtonManager` helper for handling 4 buttons
- Test app in `main.cpp` that shows button events on an SSD1306 OLED (I2C)

## Wiring assumptions
- Buttons are **active-low** (pressed = `0`) and use **internal pull-ups**.
- OLED is SSD1306 over I2C.

> Pins are intentionally left as placeholders — fill in the correct pins for your board/wiring.

## Build
This is intended to be compiled with **Mbed OS 6**.

If you are using `mbed-tools`:
1. Add this repo as your Mbed program.
2. Ensure Mbed OS is present.
3. Fill in the pin defines in `main.cpp`.
4. Build and flash.
