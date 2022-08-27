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

At this point, the terminal will ask if you want a login shell activated, press ***no*** (otherwise the serial will be used to access the PI's terminal
and not serial communication). </br></br>
Another prompt will pop up asking if you want the Serial Port activated, to that you should select **yes**, and then **reboot**.

### Step two - Editing the *config.txt* file

In the PI's terminal, access the */boot/config.txt* file for editing via the command *sudo nano /boot/config.txt*.

Once there, scroll to the end of the file and add the following lines :

*dtoverlay=uart4
dtoverlay-disable-bt
dtoverlay=miniuart-bt
enable_uart=1*

Now pay attention that the last command only enables the uart (1=yes), and not enables the first UART on the PI 
the first command is the one that decides for which UART to be enabled (uart1,uart2,uart3,uart4...) 
the rest of the commands make sure to enable the main UART on the PI (ttyAMA0), instead of the default limited miniUART

## More about the RPI and it's UARTS

On the 4B model, there are 6 UARTS

| UART  | GPIO |
| ------------- | ------------- |
| 0  | 14/15  |
| 1  | 14/15  |
| 2  | 0/1  |
| 3  | 4/5  |
| 4  | 8/9  |
| 5  | 12/13  |

In this tutorial I will be using UART 4 on pins 8 and 9.
