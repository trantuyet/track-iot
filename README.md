## track-iot
Junction Ha Noi 2023 - Track IoT: design an IoT system consting of a device and an application that provides a solution for monitoring and alerting of LTE network signal loss with optional configuration according to user needs.

### Devices:
Censor provider: Module **SIM7090**
Hardware provider: MCU **Arduino Uno R3**
### AT commands:
|Command        |Description                                  |Expected result
------------    ---------------                               --------------------------------------
|`AT`           |  check module                               |  OK </br>
|`AT+CSQ?`      |  check channel sign quality                 |   OK (rssi 31 - 52 dBm for the best quality) </br>
|`AT+CMGR?`     |  check Software Release version             |   OK </br>
|`AT+CGREG?`    |  check network registration status          |   OK <n>,<stat>[,<lac>,<ci>,<netact>[,[<Active-Time>],[<Periodic-RAU>],[<GPRS-READY-timer>]]]
|``
