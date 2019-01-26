#include <M5Stack.h>
#include "BluetoothSerial.h"
#include <driver/adc.h>

BluetoothSerial SerialBT;

int sensorValue = 0;
float gsr_average = 0;
long sum = 0;
int w = 0;

int userResistence = 0;

void setup()
{
  Serial.begin(115200);

  adc1_config_width(ADC_WIDTH_BIT_12);                       
  // adc1_config_channel_atten(ADC1_CHANNEL_0, ADC_ATTEN_DB_11); //ADC_ATTEN_DB_11 = 0-3,6V
  SerialBT.begin("ESP32Emotion"); //Bluetooth device name
}

void loop()
{
  sum = 0;

  for (int i = 0; i < 10; i++) //Average the 10 measurements to remove the glitch
  {
    sensorValue = adc1_get_raw(ADC1_CHANNEL_0);
    //sensorValue = analogRead(36);
    sum += sensorValue;
    delay(5);
  }
  gsr_average = sum / 10;
  /*
  Human Resistance = ((1024+2*Serial_Port_Reading)*10000)/(512-Serial_Port_Reading), 
  unit is ohm, Serial_Port_Reading is the value display on Serial Port(between 0~1023)
  */

  float voltage = (gsr_average * 3.3) / 4096;

  // Print results

  SerialBT.print(gsr_average);
  SerialBT.print(" , ");
  SerialBT.println(voltage);

}