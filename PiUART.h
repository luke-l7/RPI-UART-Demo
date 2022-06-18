#ifndef RPI_UART_DEMO_PIUART_H
#define RPI_UART_DEMO_PIUART_H
#include <utility>
#include "string"
using namespace std;
/**
 * Implementation of Serial Communication on the PI
 *
 * Using the header <pigpio>.
 * for more info and documentation refer to the webpage https://abyz.me.uk/rpi/pigpio/
 */
class PiUART
{
private:
    /// the UART_ to use
    string  UART_;
    /// RTS 'raise to speak' pin
    int     RTS_PIN_;
    /// UART pigpio handle id
    int     handle_;
public:
    explicit PiUART(string UART_string): UART_(std::move(UART_string)), RTS_PIN_(-1), handle_(-1) {};
    PiUART(string UART_string, int RTS_PIN): UART_(std::move(UART_string)),RTS_PIN_(RTS_PIN), handle_(-1){} ;
    int SerialInit() noexcept;
    int Write(char *buff,std::uint8_t size) noexcept;
    int Read(char *buff, std::uint8_t size) noexcept;
};


#endif //RPI_UART_DEMO_PIUART_H
