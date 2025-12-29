#define RPIN 3
#define GPIN 5
#define BPIN 6
#define BUTTON_PIN 7
#define COLORON 0
#define COLOROFF 255

enum ColorMode {
    OFF = 0,
    RED = 1,
    GREEN = 2,
    BLUE = 3,
    YELLOW = 4,
    PURPLE = 5,
    DIFFERENT_BLUE = 6,
    ALL = 7
};

ColorMode mode = BLUE;
bool lastButtonState = HIGH;
int potPin = A3;
int potVal = 0;
int ledPin = 10;
int ledVal = 0;

void setup() {
    Serial.begin(9600);
    pinMode(RPIN, OUTPUT);
    pinMode(GPIN, OUTPUT);
    pinMode(BPIN, OUTPUT);
    pinMode(BUTTON_PIN, INPUT_PULLUP);

    pinMode(ledPin, OUTPUT);
}

void loop() {
    bool buttonState = digitalRead(BUTTON_PIN);
    potVal = analogRead(potPin);

    // potentiometer's range 0-1023
    if (potVal < 341) {
        potVal = ((potVal * 3) / 4)/3; // normalize to lower third 0-84
        ledVal = potVal; // 0-84
    }
    else if (potVal < 682) {
        potVal = (((potVal-341) * 3) / 4)/3; // normalize to middle third 85-170
        ledVal = potVal+85; // 85-170
    }
    else {
        potVal = (((potVal-683) * 3) / 4)/3; // normalize to upper third 171-255
        ledVal = potVal+170; // 171-255
    }

    if (lastButtonState == HIGH && buttonState == LOW) {
        mode = (ColorMode)((mode + 1) % 8);  // cycle 0 -> 7
        delay(200);
    }
    lastButtonState = buttonState;

    switch(mode) {
        case OFF:
            light_led_colors(COLOROFF, COLOROFF, COLOROFF);
            break;

        case RED:
            light_led_colors(ledVal, COLOROFF, COLOROFF);
            break;

        case GREEN:
            light_led_colors(COLOROFF, ledVal, COLOROFF);
            break;

        case BLUE:
            light_led_colors(COLOROFF, COLOROFF, ledVal);
            break;

        case YELLOW:
            light_led_colors(ledVal, ledVal, COLOROFF);
            break; 

        case PURPLE:
            light_led_colors(ledVal, COLOROFF, ledVal);
            break; 

        case DIFFERENT_BLUE:
            light_led_colors(COLOROFF, ledVal, ledVal);
            break; 

        case ALL: 
            light_led_colors(ledVal, ledVal, ledVal);
            break; 

        default: // BLUE
            light_led_colors(COLOROFF, COLOROFF, ledVal);
            break;
    }
}

void light_led_colors(int red, int green, int blue) {
    analogWrite(RPIN, red);
    analogWrite(GPIN, green);
    analogWrite(BPIN, blue);
}
