# Packet Structure

## Telemetry Packets

### SCI Telemetry
The science module sends telemetry packets to the on-board computer module. The telemetry packet includes the following:

| Start # |             Data             | Type  | Size (Bytes) |
| :-----: | :--------------------------: | :---: | :----------: |
|    0    |      Acceleration in X       | float |      4       |
|    4    |      Acceleration in Y       | float |      4       |
|    8    |      Acceleration in Z       | float |      4       |
|   12    |           Humidity           | float |      4       |
|   16    | Magnetic Field Strength in X | float |      4       |
|   20    | Magnetic Field Strength in Y | float |      4       |
|   24    | Magnetic Field Strength in Z | float |      4       |
|   28    |           Pressure           | float |      4       |
|   32    |         Temperature          | float |      4       |
