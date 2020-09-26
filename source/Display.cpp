#include "Display.h"

Arduino_ST7789 display(PB_15, PB_14, PB_10, PB_9, PE_4, PE_5);
DigitalOut  displayBacklight(PB_9, 1);
