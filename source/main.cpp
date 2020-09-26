#include "mbed.h"
#include <string>
#include "mbed-trace/mbed_trace.h"
//#include "myEthernet.h"
#include "Display.h"

extern "C" {
int bmp_main(int argc, char **argv);
};


int main() {
    printf("Hello from "  MBED_STRINGIFY(TARGET_NAME) "\n");
    printf("Mbed OS version: %d.%d.%d\n", MBED_MAJOR_VERSION, MBED_MINOR_VERSION, MBED_PATCH_VERSION);
    printf("test TCPServer\n");
    
    mbed_trace_init();
    
    // local display stuff
    display.begin();
    display.fillScreen(ST7789_BLACK);
    display.drawRect(0, 0, 240, 240, ST7789_BLUE);
    
    display.setTextSize(2);
    display.setTextColor(ST7789_GREEN);
    display.setCursor(10, 20);
    display.printf("Mbed-BMP V0.1");

    //ethernet_init();

    bmp_main(0, nullptr);

    
    // main loop, check for key pressed
    while(1) {
        char ch = getc(stdin);

        switch (ch) {
        }

        ThisThread::sleep_for(10ms);
    }
}

