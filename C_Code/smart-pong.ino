#include <simpleRPC.h>
#include "Adafruit_VL53L0X.h"

Adafruit_VL53L0X sensor1 = Adafruit_VL53L0X();
Adafruit_VL53L0X sensor2 = Adafruit_VL53L0X();

// constants won't change. They're used here to set pin numbers:
const int buttonPin = 12; // the number of the pushbutton pin
const int ledPin = 13;    // the number of the LED pin

// Variables will change:
int button_state = HIGH;       // the current state of the output pin
int buttonState;           // the current reading from the input pin
int lastButtonState = LOW; // the previous reading from the input pin

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0; // the last time the output pin was toggled
unsigned long debounceDelay = 50;   // the debounce time; increase if the output flickers

void setup()
{
    Serial.begin(115200);
    Serial1.begin(230400); // Initialize Serial1

    pinMode(2, OUTPUT);
    pinMode(13, OUTPUT);
    pinMode(buttonPin, INPUT_PULLUP);

    digitalWrite(2, LOW);
    digitalWrite(13, LOW);

    delay(1000);

    Serial.println("Initialising the first sensor...");
    if (!sensor1.begin(0x30))
    {
        Serial.println(F("Failed to boot sensor 1"));
        while (1)
            ;
    }
    Serial.println("Initialising the first sensor is done.");

    Serial.println("Initialising the second sensor...");

    delay(1000);
    digitalWrite(2, HIGH);
    digitalWrite(13, HIGH);
    delay(1000);
    Serial.println("VL53L0X 2");
    if (!sensor2.begin(0x29))
    {
        Serial.println(F("Failed to boot sensor 2"));
        while (1)
            ;
    }
    Serial.println("Initialising the second sensor is done.");
    digitalWrite(13, LOW);

    // start continuous ranging
    sensor1.startRangeContinuous();
    sensor2.startRangeContinuous();
}

void loop()
{
    interface(
        Serial1,
        get_sensor1, "get_sensor1:",
        get_sensor2, "get_sensor2:",
        get_button, "get_button:");

    poll_button();
    
    // if (sensor1.isRangeComplete())
    // {
    //     int range = sensor1.readRange() / 10.0;
    //     Serial.println(range);
    // }
}

bool get_sensor1(void)
{
    bool res = false;

    if (sensor1.isRangeComplete())
    {
        int range = sensor1.readRange() / 10.0;
        if (range <= 6)
            res = true;
    }
    return res;
}

bool get_sensor2(void)
{
    bool res = false;

    if (sensor2.isRangeComplete())
    {
        int range = sensor2.readRange() / 10.0;
        if (range <= 6)
            res = true;
    }
    return res;
}

bool get_button(void)
{
    // return (digitalRead(12) ? true : false);
    return lastButtonState;
}

void poll_button(void)
{
    // read the state of the switch into a local variable:
    int reading = !digitalRead(buttonPin);

    // check to see if you just pressed the button
    // (i.e. the input went from LOW to HIGH), and you've waited long enough
    // since the last press to ignore any noise:

    // If the switch changed, due to noise or pressing:
    if (reading != lastButtonState)
    {
        // reset the debouncing timer
        lastDebounceTime = millis();
    }

    if ((millis() - lastDebounceTime) > debounceDelay)
    {
        // whatever the reading is at, it's been there for longer than the debounce
        // delay, so take it as the actual current state:

        // if the button state has changed:
        if (reading != buttonState)
        {
            buttonState = reading;

            // only toggle the LED if the new button state is HIGH
            if (buttonState == HIGH)
            {
                button_state = !button_state;
            }
        }
    }

    // save the reading. Next time through the loop, it'll be the lastButtonState:
    lastButtonState = reading;
}