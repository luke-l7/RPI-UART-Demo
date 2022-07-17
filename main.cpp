#include "PIUART.h"
char* UART = "/dev/ttyAMA0";
#define BAUD_RATE 9600
int main(){
    PIUART piuart = PIUART(UART,BAUD_RATE,7);
    piuart.SerialInit();
    piuart.SerialTerminate();
    return 0;
}

