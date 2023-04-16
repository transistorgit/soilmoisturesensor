#include <Arduino.h>

void setup() {
  Serial.begin(9600);
}

void loop() {
  char str[6];

  int val = analogRead(A0);
  snprintf(str, 6, "S0:%d", val/10);
  Serial.print(str);      

  val = analogRead(A1);
  snprintf(str, 6, "S1:%d", val/10);
  Serial.print(str);   

  val = analogRead(A2);   
  snprintf(str, 6, "S2:%d", val/10);
  Serial.print(str);   

  val = analogRead(A3);   
  snprintf(str, 6, "S3:%d", val/10);
  Serial.print(str);      
    
  val = analogRead(A4);   
  snprintf(str, 6, "S4:%d", val/10);
  Serial.print(str);      
    
  val = analogRead(A5);   
  snprintf(str, 6, "S5:%d", val/10);
  Serial.print(str);      
    
  val = analogRead(A6);   
  snprintf(str, 6, "S6:%d", val/10);
  Serial.print(str);      
    
  val = analogRead(A7);   
  snprintf(str, 6, "S7:%d", val/10);
  Serial.print(str);      
    
  delay(5000);                     
}