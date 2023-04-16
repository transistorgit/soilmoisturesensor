# soilmoisturesensor
arduino nano with 8 moisture sensors and a ESP01 to send the data to a MQTT broker

## connections

connect Nano Tx pin to ESP01 RX pin (use resistors as level shifters)

Sensors: https://www.amazon.de/Hailege-Capacitive-Moisture-Voltage-3-3-5-5V/dp/B07XK772MN/ref=sr_1_1_sspa?

## config
ad a file "nano2mqtt/src/secrets.h" with your paswords, like

```
#pragma once

const char* SSID = "myssid";
const char* PASSWORD = "mywifipasswd";
const char* OTAPASSWORD = "xxx";
```



