#pragma once
#include "Button.h"

/** 4-button helper: UP / DOWN / OK / BACK */
class Buttons4 {
public:
    Buttons4(PinName up, PinName down, PinName ok, PinName back,
             chrono::milliseconds debounce = 30ms)
        : up(up, Button::Config{debounce, true})
        , down(down, Button::Config{debounce, true})
        , ok(ok, Button::Config{debounce, true})
        , back(back, Button::Config{debounce, true})
    {}

    void update()
    {
        up.update();
        down.update();
        ok.update();
        back.update();
    }

    Button up, down, ok, back;
};