# RPI-UART-Demo
Communicating over the UART_ with the Raspberry Pi
## Getting Started

In this tutorial I will be creating a demo for using the UART_ on the Raspberry pi 4 using the header pigpio, I'm going to be using the RPI 4B model, but any model should be fine as well. </br>

[The pigpio package](https://abyz.me.uk/rpi/pigpio/) is a package used to control the GPIO pins on the PI, and more.

### Step one - Activating the serial communication

1. Open up your PI terminal.
2. Enter the command *sudo raspi-config*.
3. Use your arrow keys to navigate to *Advanced options*, and press enter.
4. Navigate to the *Serial* option.

At this point, the terminal will ask if you want a login shell activated, in case you do, press yes.
Another prompt will pop up asking if you want the Serial Port activated, to that you should select **yes**, and then **reboot**.

#### More about the RPI and it's UARTS

On the 4B model, there are 6 UARTS

| UART  | GPIO |
| ------------- | ------------- |
| 0  | 14/15  |
| 1  | 14/15  |
| 2  | 0/1  |
| 3  | 4/5  |
| 4  | 8/9  |
| 5  | 12/13  |

In this tutorial i will be using UART 4 on pins 8 and 9.
