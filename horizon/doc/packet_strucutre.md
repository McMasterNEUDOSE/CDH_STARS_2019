# Packet Structure

## Telemetry Packets

### SCI Telemetry
The science module sends telemetry packets to the on-board computer module. The telemetry packet includes the following:

| Start # |             Data             |  Unit   | Type  | Size (Bytes) |
| :-----: | :--------------------------: | :-----: | :---: | :----------: |
|    0    |      Acceleration in X       |  m/s^2  | float |      4       |
|    4    |      Acceleration in Y       |  m/s^2  | float |      4       |
|    8    |      Acceleration in Z       |  m/s^2  | float |      4       |
|   12    |           Humidity           | percent | float |      4       |
|   16    | Magnetic Field Strength in X | mGauss  | float |      4       |
|   20    | Magnetic Field Strength in Y | mGauss  | float |      4       |
|   24    | Magnetic Field Strength in Z | mGauss  | float |      4       |
|   28    |           Pressure           |   hPA   | float |      4       |
|   32    |         Temperature          | Celsius | float |      4       |
