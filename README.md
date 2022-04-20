# lcd-notifications

[![Arduino](https://img.shields.io/badge/-Arduino-00979D?style=flat&logo=Arduino&logoColor=white)](https://www.arduino.cc/)

## Endpoints

| Endpoint | Função |
|---|---|
| `"/"` | Teste de health check |
| `"/post"` | Recebe um `POST` contendo a notificação via arg (`?notification=foo`) |

## Pinagem

| I2C LCD | ESP32 |
|---|---|
| GND | GND |
| VCC | VIN |
| SDA | GPIO21 |
| SCL | GPIO22 |
