#pragma once
#include "mbed.h"

/**
 * Debounced active-low button (pressed == 0).
 * Call update() periodically (e.g. every 5ms).
 *
 * Events:
 *  - fell(): stable transition to PRESSED
 *  - rose(): stable transition to RELEASED
 */
class Button {
public:
    struct Config {
        chrono::milliseconds debounce = 30ms;
        bool active_low = true;
    };

    Button(PinName pin, const Config& cfg = Config())
        : _in(pin), _cfg(cfg)
    {
        // active-low typical: enable pull-up
        _in.mode(PullUp);

        _raw_prev = raw_read();
        _stable = _raw_prev;
        _last_change = Kernel::Clock::now();
    }

    void update()
    {
        const bool raw = raw_read();
        const auto now = Kernel::Clock::now();

        if (raw != _raw_prev) {
            _raw_prev = raw;
            _last_change = now;
        }

        if ((_stable != raw) && (now - _last_change >= _cfg.debounce)) {
            const bool prev = _stable;
            _stable = raw;

            if (!prev && _stable) _rose = true;      // released
            else if (prev && !_stable) _fell = true; // pressed
        }
    }

    bool pressed() const { return _stable; }

    bool fell() { bool v = _fell; _fell = false; return v; }
    bool rose() { bool v = _rose; _rose = false; return v; }

private:
    bool raw_read()
    {
        const int v = _in.read();      // 0/1
        const bool active = (v == 0);  // active-low
        return _cfg.active_low ? active : !active;
    }

private:
    DigitalIn _in;
    Config _cfg;

    bool _raw_prev = false;
    bool _stable = false;

    bool _fell = false;
    bool _rose = false;

    Kernel::Clock::time_point _last_change{};
};