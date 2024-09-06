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
    pinMode( PIN_HUMAN_DETECTOR, INPUT );
    pinMode( PIN_DETECTOR_MODE, OUTPUT );
    digitalWrite( PIN_DETECTOR_MODE, HIGH );
    pinMode( PIN_INDICATOR_LED, OUTPUT );
    pinMode( PIN_BUTTON_MODE, INPUT_PULLUP );
    pinMode( PIN_ALARM, OUTPUT );
}

void loop() {
    
    if( digitalRead(PIN_HUMAN_DETECTOR) == HIGH && detector_on ) {
        alarm();
    }

    if( button_ready && digitalRead(PIN_BUTTON_MODE) == LOW ) {
        detector_on = !detector_on;
        button_ready = false;
        delay( 10 );
    } else if( !button_ready && digitalRead(PIN_BUTTON_MODE) == HIGH ) {
        button_ready = true;
        delay( 10 );
    }
        
    if( detector_on ) {
        digitalWrite( PIN_DETECTOR_MODE, HIGH );
    } else {
        digitalWrite( PIN_DETECTOR_MODE, LOW );
        digitalWrite( PIN_ALARM, LOW );
        digitalWrite( PIN_INDICATOR_LED, LOW );
    }

}

void alarm() {

    /*
     * Multiprogramming technique, alarm bunyi (500ms), delay (100ms)
     * bila tombol detector mode ditekan, matikan alarm secara langsung. Solusi
     * yang lebih bagus adalah interrupt, namun tidak dilakukan demi kemudahan
     * membaca kode :)
     */

    int alarm_duration = ALARM_DURATION;
    int alarm_delay = ALARM_DELAY;

    digitalWrite( PIN_ALARM, HIGH );
    digitalWrite( PIN_INDICATOR_LED, HIGH );
    while( alarm_duration > 0 ) {
        if( button_ready && digitalRead(PIN_BUTTON_MODE) == LOW ) {
            detector_on = false;
            button_ready = false;
            return;
        }
        alarm_duration -= 10;
        delay( 10 );
    }

    digitalWrite( PIN_ALARM, LOW );
    digitalWrite( PIN_INDICATOR_LED, LOW );
    while( alarm_delay > 0 ) {
        if( button_ready && digitalRead(PIN_BUTTON_MODE) == LOW ) {
            detector_on = false;
            button_ready = false;
            return;
        }
        alarm_delay -= 10;
        delay( 10 );
    }
}
