#include "Uart.h"


#ifdef DEBUG
Uart uart;
#define DEBUG_PRINT(x) uart.envoyerMessage(x) // ou par RS-232
#else
#define DEBUG_PRINT(x) do {} while (0)  // code mort
#endif