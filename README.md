djenko
======

![djenko Pony](https://github.com/nalch/djenko/blob/master/images/IMG_20141013_145952.jpg "The djenko pony")

## Installation

### Windows-only
* install [pySerial](http://pythonhosted.org//pyserial/#)
* if the virtual com port driver is not present, download it from [FTDI Chip](http://www.ftdichip.com/Drivers/VCP.htm) 

### Common
* plug in the serial forwarder hardware device to the computer's usb port
* start djenko_serialproxy.py with the jenkinsjob's name and optional parameters (see _Configuration_)
    ```
    python djenko_serialproxy.py mytask
    ```
or
    ```   
    python djenko_serialproxy.py -v -u http://localhost:8080 -i 30 -p /dev/ttyUSB0 mytask
    ```

## Configuration
The configuration is handled through commandline parameters. See the help message for further information.

Available parameters are:

|        Parameter         |                                            Description                                                   |       Default         |
|--------------------------|----------------------------------------------------------------------------------------------------------|-----------------------|
| `--verbose`, `-v`        | prints debug messages to the console                                                                     | False                 |
| `--jenkins_url`, `-u`    | the Jenkins server url                                                                                   | http://localhost:8080 |
| `--fetch_interval`, `-i` | interval to fetch the job's status in seconds (the old status will be assumed till a new one is fetched) | 30                    |
| `--serial_port`, `-p`    | the hardware device's serial port                                                                        | /dev/ttyUSB0          |

## Signals

### General information
|  Event  |                     Occurences                        |                              Signal                                 |
|---------|-------------------------------------------------------|---------------------------------------------------------------------|
| Startup | serialport connection/disconnect, power on the device | all three leds blink three times                                    |
| Error   | f.e. jenkins status could not be fetched              | an alternating blinking between the red and the yellow/green led    |
 
### Job status
|    Status      |         Signal        |
|----------------|-----------------------|
| Building       | all three leds blink  |
| Successful     | the green led is lit  |
| Unstable       | the yellow led is lit |
| Aborted/Failed | the red led is lit    |

## Hardware devices
The main hardware device is the serial forwarder, which receives signals from a serial connection over the USB-Interface.
![Serial forwarder](https://github.com/nalch/djenko/blob/master/images/IMG_20141013_150458.jpg "Serial forwarder")
It provides a 5 Volt-four pin interface to connect arbitrary peripheral devices to display the jobstatus. The upper pins don't serve any function.

```
 --------
|o X o X|
|o o o o|
 --------
 | | | |
 G R Y G
 R E E R
 O D L E
 U   L E
 N   O N
 D   W  
```

### Peripherals
You can connect any type of status indicator to the serial forwarder as long as it supports the four 5-Volt output pins. Pretty standard solutions are traffic lights. Please consider a big, red signal horn or the bugsiren.

#### Djenko Pony
The Djenko Pony is the basic status indicator. Just connect the provided cables to the peripheral interface and you're good to go.
![Djenko Pony](https://github.com/nalch/djenko/blob/master/images/IMG_20141013_150231.jpg "Pony connector")![Pony Connector](https://github.com/nalch/djenko/blob/master/images/IMG_20141013_150021.jpg "Djenko Pony")