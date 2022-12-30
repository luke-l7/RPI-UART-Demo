#ifndef GREAT_PIUART_HPP
#define GREAT_PIUART_HPP
#include <utility>
#include <cstdint>
#include "mutex"
using namespace std;

#define BAD_FILE_ERR "Cannot Initialize/open the uart, Ensure it is not used by other applications."
#define INIT_ERR "Uninitialized Serial."
#define PARTIAL_WRITE_ERR "Partial transmit error, "
#define GENERAL_ERR "An error occurred"
#define PIGPIO_LIB_ERR "PIGPIO init error."

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
    bool       is_initialized_;
    /// mutex used in read, write functions
    std::mutex        rw_mutex;
    /// either raises/lowers the RTS
    void raiseToSpeak() const noexcept;
    /// Prints an error, either to DEBUG_PRINT, regular cout or SD Card
    static void printErr(char* msg) noexcept;
public:
    PIUART(char* UART_string, unsigned int BAUD_RATE): UART_(UART_string),
        RTS_PIN_(-1), handle_(-1), BAUD_RATE_(BAUD_RATE), is_initialized_(false) {};
    PIUART(char* UART_string, unsigned int BAUD_RATE, int RTS_PIN):
        PIUART(UART_string, BAUD_RATE) {this->RTS_PIN_ = RTS_PIN;};
    /**
     * Initializes the UART and it's libraries.
     *
     * @return 0 upon success, -1 otherwise.
     */
    int serial_init() noexcept;
    /**
     * Frees the allocations and parameters from initializing the UART.
     */
    void serial_terminate() const noexcept;
    /**
     * Transmits ´size´ bytes from ´buffer´ over the UART.
     * @param buff : buffer to transmit from
     * @param size : size of buffer/ #of bytes
     * @return 0 if successful, -1 otherwise
     */
    int write(std::byte* buff,uint8_t size) noexcept;
    /**
     * Reads ´size´ bytes from the UART.
     * @param buff : buffer to write into
     * @param size : size of buffer/ #of bytes
     * @return 0 if successful, -1 otherwise
     */
    int read(std::byte* buff, uint8_t size) noexcept;
    /**
     * Reads 1 char from serial buffer
     * if no char is available, returns null
     * @return
     */
    byte read() noexcept;
};

#endif  // GREAT_PIUART_HPP
