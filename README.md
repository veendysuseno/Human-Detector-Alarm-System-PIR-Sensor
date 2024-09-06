# Human Detector Alarm System

This project implements a human detection alarm system using an Arduino. The system can detect human presence and sound an alarm if motion is detected. It also features a mode button to turn the detector on or off and an indicator LED to show when the alarm is active.

## Components Used

- Arduino Uno
- Human Detector Sensor
- Push Button
- Alarm (Buzzer)
- Indicator LED
- Resistors
- Jumper Wires
- Breadboard

## Pin Configuration

- **PIN_HUMAN_DETECTOR**: connected to the human detector sensor (Pin 2)
- **PIN_DETECTOR_MODE**: controls the detector mode (Pin 3)
- **PIN_BUTTON_MODE**: connected to the mode button (Pin 4)
- **PIN_ALARM**: connected to the alarm buzzer (Pin 6)
- **PIN_INDICATOR_LED**: connected to the indicator LED (Pin 7)

## Code

```cpp
const int PIN_HUMAN_DETECTOR = 2;
const int PIN_DETECTOR_MODE = 3;
const int PIN_BUTTON_MODE = 4;
const int PIN_ALARM = 6;
const int PIN_INDICATOR_LED = 7;

const int ALARM_DURATION = 500;
const int ALARM_DELAY = 100;

bool detector_on = true;
bool button_ready = true;

void setup() {
    pinMode(PIN_HUMAN_DETECTOR, INPUT);
    pinMode(PIN_DETECTOR_MODE, OUTPUT);
    digitalWrite(PIN_DETECTOR_MODE, HIGH);
    pinMode(PIN_INDICATOR_LED, OUTPUT);
    pinMode(PIN_BUTTON_MODE, INPUT_PULLUP);
    pinMode(PIN_ALARM, OUTPUT);
}

void loop() {
    if (digitalRead(PIN_HUMAN_DETECTOR) == HIGH && detector_on) {
        alarm();
    }

    if (button_ready && digitalRead(PIN_BUTTON_MODE) == LOW) {
        detector_on = !detector_on;
        button_ready = false;
        delay(10);
    } else if (!button_ready && digitalRead(PIN_BUTTON_MODE) == HIGH) {
        button_ready = true;
        delay(10);
    }

    if (detector_on) {
        digitalWrite(PIN_DETECTOR_MODE, HIGH);
    } else {
        digitalWrite(PIN_DETECTOR_MODE, LOW);
        digitalWrite(PIN_ALARM, LOW);
        digitalWrite(PIN_INDICATOR_LED, LOW);
    }
}

void alarm() {
    int alarm_duration = ALARM_DURATION;
    int alarm_delay = ALARM_DELAY;

    digitalWrite(PIN_ALARM, HIGH);
    digitalWrite(PIN_INDICATOR_LED, HIGH);
    while (alarm_duration > 0) {
        if (button_ready && digitalRead(PIN_BUTTON_MODE) == LOW) {
            detector_on = false;
            button_ready = false;
            return;
        }
        alarm_duration -= 10;
        delay(10);
    }

    digitalWrite(PIN_ALARM, LOW);
    digitalWrite(PIN_INDICATOR_LED, LOW);
    while (alarm_delay > 0) {
        if (button_ready && digitalRead(PIN_BUTTON_MODE) == LOW) {
            detector_on = false;
            button_ready = false;
            return;
        }
        alarm_delay -= 10;
        delay(10);
    }
}
```

## How to Use

1. Connect the components to the Arduino according to the pin configuration.
2. Upload the code to your Arduino.
3. Press the mode button to toggle the detector on or off.
4. If the human detector sensor detects motion and the detector is on, the alarm will sound and the indicator LED will light up.
5. The alarm can be stopped by pressing the mode button while the alarm is sounding.

## Notes

- The system uses a polling method to check the button state during alarm duration. For a more responsive system, an interrupt-based approach could be implemented.
- Ensure all connections are secure to avoid false alarms or missed detections.
