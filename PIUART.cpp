#include "PIUART.hpp"
#include "pigpio.h"
#include <cstring>
#include <fcntl.h>  //Used for UART
#include <iostream>
//#include <termios.h>  //Used for UART
#include <asm/termbits.h>
#include <sys/ioctl.h>
#include <unistd.h>  //Used for UART

void PIUART::printErr(char* msg = nullptr) noexcept
{
    // todo : decide where errors should go
    if (msg)
        cerr << msg << endl;
    cerr << strerror(errno) << endl;
}

int PIUART::serial_init() noexcept
{
    /* Init the pigpio library */
    if(gpioInitialise() < 0)
    {
        printErr();
        return -1;
    }
    /* Initialize the RTS PIN */
    if(RTS_PIN_ >= 0)
    {
        gpioSetMode(RTS_PIN_, PI_OUTPUT);
    }
    int uart_filestream = -1;

    //OPEN THE UART
    //The flags (defined in fcntl.h):
    //	Access modes (use 1 of these):
    //		O_RDONLY - Open for reading only.
    //		O_RDWR - Open for reading and writing.
    //		O_WRONLY - Open for writing only.
    //
    //	O_NDELAY / O_NONBLOCK (same function) - Enables nonblocking mode. When set read requests on the file can return immediately with a failure status
    //											if there is no input immediately available (instead of blocking). Likewise, write requests can also return
    //											immediately with a failure status if the output can't be written immediately.
    //
    //	O_NOCTTY - When set and path identifies a terminal device, open() shall not cause the terminal device to become the controlling terminal for the process.
    uart_filestream = open(UART_, O_RDWR | O_NOCTTY);		//Open in non-blocking read/write mode
    if (uart_filestream == -1)
    {
        //ERROR - CAN'T OPEN SERIAL PORT
        printErr();
        return -1;
    }
    //CONFIGURE THE UART
    //The flags (defined in /usr/include/termios.h - see http://pubs.opengroup.org/onlinepubs/007908799/xsh/termios.h.html):
    //	Baud rate:- B1200, B2400, B4800, B9600, B19200, B38400, B57600, B115200, B230400, B460800, B500000, B576000, B921600, B1000000, B1152000, B1500000, B2000000, B2500000, B3000000, B3500000, B4000000
    //	CSIZE (character size in bits) :- CS5, CS6, CS7, CS8
    //	CLOCAL - Ignore modem status lines
    //	CREAD - Enable receiver
    //	IGNPAR = Ignore characters with parity errors
    //	ICRNL - Map CR to NL on input (Use for ASCII comms where you want to auto correct end of line characters - don't use for bianry comms!)
    //	PARENB - Parity enable
    //	PARODD - Odd parity (else even)
    struct termios options;

//    tcgetattr(uart_filestream, &options);
//    options.c_cflag = B115200 | CS8 | CLOCAL | CREAD;		//<Set baud rate
//    options.c_iflag = IGNPAR;
//    options.c_oflag = 0;
//    options.c_lflag = 0;
//    cfsetispeed(&options, 115200);
//    cfsetospeed(&options, 115200);
//    tcflush(uart_filestream, TCIFLUSH);
//    tcsetattr(uart_filestream, TCSANOW, &options);

    struct termios2 tio;

    ioctl(uart_filestream, TCGETS2, &tio);
    tio.c_iflag = IGNPAR;
    tio.c_oflag = 0;
    tio.c_lflag = 0;
    tio.c_cflag &= ~CBAUD;
    tio.c_cflag |= CBAUDEX;
    tio.c_cflag |= BOTHER;
    tio.c_ispeed = BAUD_RATE_;
    tio.c_ospeed = BAUD_RATE_;
    ioctl(uart_filestream, TCSETS2, &tio);

    handle_ = uart_filestream;
    is_initialized_ = true;
    return 0;
}

int PIUART::write(std::byte* buff, uint8_t size) noexcept
{
    if (!is_initialized_)
    {
        printErr();
        return -1;
    }

        rw_mutex.lock();
        int byte_count = 0;
        raiseToSpeak();
        byte_count = ::write(handle_, buff, size);
        if (byte_count < 0) // an error has occured
        {
            printErr();
            return -1;
        }
        if (byte_count < size)
        {
            printErr(PARTIAL_WRITE_ERR);
            return -1;
        }
        raiseToSpeak();
        rw_mutex.unlock();
        return byte_count;
}

int PIUART::read(std::byte* buff, uint8_t size) noexcept
{
    if (is_initialized_)
    {
        rw_mutex.lock();
        int rx_length = ::read(handle_, (void*)buff, size);
        if (rx_length < 0)
        {
            //An error occured (will occur if there are no bytes)
//            printErr(GENERAL_ERR);
            cout << strerror(errno) << endl;
        }
        if (rx_length == 0)
        {
            //No data waiting
        }
        rw_mutex.unlock();
        return rx_length;
    }
    printErr();
    return -1;
}

byte PIUART::read() noexcept
{
    byte inChar;
    if (read(&inChar, 1))
        return inChar;
    return byte(0);
}

void PIUART::serial_terminate() const noexcept
{
    if (handle_ >= 0)
        close(handle_);
    else
        printErr();
}

void PIUART::raiseToSpeak() const noexcept
{
    if (RTS_PIN_ >= 0) // if RTS is initialized
        gpioWrite(RTS_PIN_, !gpioRead(RTS_PIN_));
}
