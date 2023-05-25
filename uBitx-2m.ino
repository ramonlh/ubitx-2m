// actua como cliente I2C de sBitx32.ino

#include "DRA818V.h"
#include <Wire.h>
#include "WireSlave.h"
#include <driver/i2c.h>

#define WIRE_CLOCK 100000     // default = 100000
#define SDA 19
#define SCL 18
#define VHFMODULE_ADDRESS 0x33   // I2C address of VHFModule

DRA818V trx;

typedef struct {    // datos I2C vhf-module
      uint8_t comtype;
      long freqrx;       // frequency RX
      long freqtx;       // frequency TX
      uint8_t volume;    // volume
      uint8_t sqlevel;   // squelch level
      uint16_t ctcsstx;  // ctcss tx
      uint16_t ctcssrx;  // ctcss rx
      uint8_t preemph;   // preemph 0/1
      uint8_t highpass;  // High pass filter 0/1
      uint8_t lowpass;   // Low pass filter 0/1
} datavhftype;
      datavhftype datavhf;
      uint8_t *buffvhf = (uint8_t *) &datavhf; // acceder a datavhftype como bytes


void initI2C()
{
  
    bool success = WireSlave.begin(SDA, SCL, VHFMODULE_ADDRESS);
    if (success) 
      {
        Wire.setClock(WIRE_CLOCK);
        Serial.print("I2C address: "); Serial.print(VHFMODULE_ADDRESS);
        Serial.print("  I2C slave init OK");
        Serial.print("  SDA pin:"); Serial.print(SDA);
        Serial.print("  SLC pin:"); Serial.println(SCL);
      }
    else
      {
        Serial.println("I2C slave init failed");
        while(1) delay(3000);
      }
}

void tone(byte pin, unsigned int freq) 
{ 
  ledcWriteTone(pin, freq); 
} 
  
void noTone(byte pin) 
{ 
  ledcWriteTone(pin,0); 
}     

void doTone(int freq, int duration) 
{
  tone(analogOut,600); 
  delay(duration); 
  noTone(analogOut);
}

void setup() {
  Serial.begin(115200);
  initI2C();          
//  trx.begin(435.000,435.000);   // frecuencias
//  trx.begin(144.5,144.5);   // frecuencias

  }

#define I2C_BUFFER_LENGTH 128

void loop() 
  { 
    uint8_t inputBuffer[I2C_BUFFER_LENGTH] = {0};
    int16_t inputLen = 0;
    inputLen = i2c_slave_read_buffer(i2c_port_t(0 & 1), buffvhf, I2C_BUFFER_LENGTH, 1);
    if (inputLen>0)
      {
      Serial.print("received:"); Serial.println(inputLen);
      Serial.print("comtype:"); Serial.println(datavhf.comtype);
      Serial.print("freqrx:"); Serial.println(datavhf.freqrx);
      Serial.print("freqtx:"); Serial.println(datavhf.freqtx);
      Serial.print("volume:"); Serial.println(datavhf.volume);
      Serial.print("sqlevel:"); Serial.println(datavhf.sqlevel);
      Serial.print("ctcsstx:"); Serial.println(datavhf.ctcsstx);
      Serial.print("ctcssrx:"); Serial.println(datavhf.ctcssrx);
      Serial.print("highpass:"); Serial.println(datavhf.highpass);
      Serial.print("lowpass:"); Serial.println(datavhf.lowpass);
      Serial.println("===================================");
    uint8_t comtype;
    double freqrx;    // frequency RX
    double freqtx;    // frequency TX
    uint8_t volume;    // volume
    uint8_t sqlevel;   // squelch level
    uint8_t ctcsstx;      // ctcss tx
    uint8_t ctcssrx;      // ctcss rx
    uint8_t highpass;   // High pass filter 0/1
    uint8_t lowpass;   // Low pass filter 0/1
      }
    delay(1);

  
  
  //trx.getSquelch(); 
  
  /****
  trx.setPTT(true,false);
  doTone(600,5000);    //  // freq, duración en ms
  trx.setPTT(false);
  delay(5000);
  ***/
  }
