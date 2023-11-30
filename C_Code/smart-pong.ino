#include <simpleRPC.h>
#include "Adafruit_VL53L0X.h"

Adafruit_VL53L0X sensor1 = Adafruit_VL53L0X();
Adafruit_VL53L0X sensor2 = Adafruit_VL53L0X();

static int button = 0;
static bool button_state = true;

void setup()
{
    Serial.begin(115200);
    Serial1.begin(230400); // Initialize Serial1

    pinMode(13, OUTPUT);
    pinMode(12, INPUT_PULLUP);

    digitalWrite(13, LOW);

    Serial.println("Initialising the first sensor...");
    if (!sensor1.begin(0x30))
    {
        Serial.println(F("Failed to boot sensor 1"));
        while (1)
            ;
    }
    Serial.println("Initialising the first sensor is done.");

    Serial.println("Initialising the second sensor...");

    digitalWrite(13, HIGH);
    delay(5000);
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
    return (digitalRead(12) ? true : false);
}
