# lcd-notifications

[![Arduino](https://img.shields.io/badge/-Arduino-00979D?style=flat&logo=Arduino&logoColor=white)](https://www.arduino.cc/)

<img src="images/photo.jpg" height="700"/>

## Endpoints

| Endpoint | Função |
|---|---|
| `"/"` | Health check |
| `"/post"` | Recebe um `POST` contendo a notificação via arg (`?notification=foo`) |

## Pinagem

| I2C LCD | ESP32 |
|---|---|
| GND | GND |
| VCC | VIN |
| SDA | GPIO21 |
| SCL | GPIO22 |

![schematic](images/schematic.jpg)
