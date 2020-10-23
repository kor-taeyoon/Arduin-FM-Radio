#include <Wire.h>
unsigned char frequencyH = 0;
unsigned char frequencyL = 0;
unsigned int frequencyB;
double channel = 0;

void setFrequency();

void setup() {
    Wire.begin();
    setFrequency();
    Serial.begin(9600);
}

void loop() {
    channel = analogRead(A0);
    channel = map(channel, 0, 1023, 880, 1080);
    setFrequency();
    Serial.println(channel/10.0);
}

void setFrequency(){
    frequencyB = 4 * (channel/10 * 1000000 + 225000) / 32768;
    frequencyH = frequencyB >> 8;
    frequencyL = frequencyB & 0xFF;
    delay(10);
    Wire.beginTransmission(0x60);
    Wire.write(frequencyH);
    Wire.write(frequencyL);
    Wire.write(0xB0);
    Wire.write(0x10);
    Wire.write((byte)0x00);
    Wire.endTransmission();
    delay(10);
}
