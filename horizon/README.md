# Horizon

## Horizon consists of two targets OBC and SCI :

- ### OBC
    The onboard computer module, responsible for collecting telemetry data from the science module as well as some housekeeping. The data is then transmitted to ground. The board used for OBC node is the _NUCLEO-L476RG_ with a _STM32L476RG_

- ### SCI
    The science module, responsible for gathering scientific data. The data is then transmitted to the obc module. The board used for SCI node is _B-L475E-IOT01A_ with a _STM32L475VG_.
---
## Building
There are two binaries (images) that can be built, the _OBC_ binary and the _SCI_ binary. Make sure your current directory is _horizon_.

- ### OBC
```sh
TARGET=OBC make
```

- ### SCI
```sh
TARGET=SCI make
```
---
## Flashing

- ### OBC
```sh
TARGET=OBC make flash
```

- ### SCI
```sh
TARGET=SCI make flash
```