#include "PIUART.h"
#include "pigpio.h"
#include <iostream>

void printErr(char* errmsg)
{
    cerr << errmsg << endl;
}

int PIUART::SerialInit() noexcept
{
    /* Init the pigpio library */
    if(gpioInitialise() < 0)
    {
        cerr << "Unable to initialize pigio." << endl;
        return -1;
    }

    /* Initialize the RTS PIN */
    if(RTS_PIN_ >= 0)
    {
        gpioSetMode(RTS_PIN_, PI_OUTPUT);
    }
    cout << "init" << endl;
    int file_handle = serOpen(UART_, BAUD_RATE_, 0);
    cout << "init complete" << endl;
    if (file_handle < 0)
    {
        cerr << "Cannot open UART : " << UART_ << endl;
        return -1;
    }
    handle_ = file_handle;
    is_initialized_ = true;
    return 0;
}

int PIUART::Write(char *buff, uint8_t size) const noexcept
{
    if (is_initialized_)
    {
        raiseToSpeak();
//        gpioDelay(500000); // visual check whether the RTS raises
        int res =  serWrite(handle_, buff, size);
        cout << "write res : " << res << endl;
        raiseToSpeak();
        return res;
    }
    cerr << "Uninitialized Serial." << endl;
    return -1;
}

int PIUART::Read(char *buff, uint8_t size) const noexcept
{
    if (is_initialized_)
    {
        return serRead(handle_, buff, size);;
    }
    printErr(BAD_FILE_ERR);
    return -1;
}

void PIUART::SerialTerminate() const noexcept {
    if (handle_ < 0)
    {
        printErr("Uninitialized Serial.");
    }
    serClose(handle_);
}

void PIUART::raiseToSpeak() const noexcept
{
    gpioWrite(RTS_PIN_, !gpioRead(RTS_PIN_));
}
