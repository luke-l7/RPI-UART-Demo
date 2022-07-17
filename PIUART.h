#ifndef GREAT_PIUART_H
#define GREAT_PIUART_H
#include <utility>
#include <cstdint>
using namespace std;
#define BAD_FILE_ERR "Cannot Initialize the uart."

// todo : improve the error handling techniques
// todo : check conflicts with the CMakeLists for adding the PIUART library
// todo : check conflicts with SPI
// todo : document
/**
 * Implementation of Serial Communication on the PI
 *
 * Using the header <pigpio>.
 * for more info and documentation refer to the webpage https://abyz.me.uk/rpi/pigpio/
 */
class PIUART
{
private:
    /// the UART_ to use
    char*                UART_;
    /// RTS 'raise to speak' pin
    int               RTS_PIN_;
    /// UART file-handle id
    int                handle_;
    /// Baud Rate
    unsigned int    BAUD_RATE_;
    /// boolean for if the serial has been initialized
    bool is_initialized_;
    /// either raises/lowers the RTS
    void raiseToSpeak() const noexcept;
public:
    PIUART(char* UART_string, unsigned int BAUD_RATE): UART_(UART_string),
        RTS_PIN_(-1), handle_(-1), BAUD_RATE_(BAUD_RATE), is_initialized_(false) {};
    PIUART(char* UART_string, unsigned int BAUD_RATE, int RTS_PIN):
        PIUART(UART_string, BAUD_RATE) {this->RTS_PIN_ = RTS_PIN;};
    int SerialInit() noexcept;
    void SerialTerminate() const noexcept;
    int Write(char *buff,uint8_t size) const noexcept;
    int Read(char *buff, uint8_t size) const noexcept;
};

#endif  // GREAT_PIUART_H
