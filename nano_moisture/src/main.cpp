#include <Arduino.h>

// see sensorvergleich.xlsx
float scale[8] = {0.274725275, 0.280112045, 0.284900285, 0.280898876, 1.470588235, 0.273224044, 1.333333333, 1.19047619};
float offset[8] = {-72.25274725, -74.50980392, -78.91737892, -76.96629213, -836.7647059, -72.13114754, -750.6666667, -655.952381};

void setup() {
  Serial.begin(9600);
}

int clip(int value, int min = 0, int max = 100)
{
  if (value < min)
  {
    return min;
  }
  if (value > max)
  {
    return max;
  }
  return value;
}

void loop() {
  char str[7];

  int val = analogRead(A0);
  snprintf(str, 7, "S0:%d", 100 - clip(val * scale[0] + offset[0]));
  Serial.print(str);

  val = analogRead(A1);
  snprintf(str, 7, "S1:%d", 100 - clip(val * scale[1] + offset[1]));
  Serial.print(str);

  val = analogRead(A2);
  snprintf(str, 7, "S2:%d", 100 - clip(val * scale[2] + offset[2]));
  Serial.print(str);

  val = analogRead(A3);
  snprintf(str, 7, "S3:%d", 100 - clip(val * scale[3] + offset[3]));
  Serial.print(str);

  val = analogRead(A4);
  snprintf(str, 7, "S4:%d", 100 - clip(val * scale[4] + offset[4]));
  Serial.print(str);

  val = analogRead(A5);
  snprintf(str, 7, "S5:%d", 100 - clip(val * scale[5] + offset[5]));
  Serial.print(str);

  val = analogRead(A6);
  snprintf(str, 7, "S6:%d", 100 - clip(val * scale[6] + offset[6]));
  Serial.print(str);

  val = analogRead(A7);
  snprintf(str, 7, "S7:%d", 100 - clip(val * scale[7] + offset[7]));
  Serial.print(str);      
    
  delay(5000);                     
}