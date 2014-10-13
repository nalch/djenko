djenko
======

![djenko Pony](http:// "The djenko pony")

## Installation

* on windows: install [pySerial](http://pythonhosted.org//pyserial/#)
* start djenko_serialproxy.py with the jenkinsjob's name
    ```
    python djenko_serialproxy.py mytask
    ```
    
## Configuration
The configuration is handled through commandline parameters. See the help message for further information.

Available parameters are:
|        Parameter         |                                            Description                                                   |
|--------------------------|----------------------------------------------------------------------------------------------------------|
asoernideo
|        Parameter         |                                            Description                                                   |
|--------------------------|----------------------------------------------------------------------------------------------------------|
| `--verbose`, `-v`        | prints debug messages to the console                                                                     |
| `--jenkins_url`, `-u`    | the Jenkins server url                                                                                   |
| `--fetch_interval`, `-i` | interval to fetch the job's status in seconds (the old status will be assumed till a new one is fetched) |
| `--serial_port`, `-p`    | the hardware device's serial port                                                                        |

An exhaustive example with all available parameters and their default values:
```   
python djenko_serialproxy.py -v -u http://localhost:8080 -i 30 -p /dev/ttyUSB0 mytask
```
 
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

#### Djenko Pony
The Djenko Pony is the basic status indicator. Just connect the provided cables to the peripheral interface and you're good to go.
