# Ground
The ground section of the system demonstrates the use of NASA's [OpenMCT](https://github.com/nasa/openmct) mission control software to read telemetry from a serialport device. It displays 9 plots for the different scientific data collected by the science node.

## Running
You need to have node 10.x to run this. Any newer version of node will not work. I suggest using [nvm](https://github.com/nvm-sh/nvm) to manage your node versions.
Make sure the serial port path is defined correctly within spacecraft.js. 

```sh
npm install
npm start
```