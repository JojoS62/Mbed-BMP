#include "Display.h"

// public network interface
NetworkInterface* network;
SocketAddress mySocketAddress;

Callback<void()> cbStartServer;
Callback<void()> cbStopServer;


static void onEthIfUp() 
{
    if (cbStartServer) {
        cbStartServer.call();
    }
}

static void onEthIfDown() 
{
    if (cbStopServer) {
        cbStopServer.call();
    }
}

static void onEthIfEvent(nsapi_event_t evt, intptr_t value)
{
    if (NSAPI_EVENT_CONNECTION_STATUS_CHANGE == evt) {
        display.setCursor(10, 60);
        switch (value) {
            case NSAPI_STATUS_LOCAL_UP:
                display.setTextColor(ST7789_GREEN, ST7789_BLACK);
                display.printf("EthIF local up      ");
                printf("EthIF local up\n");
                break;
            case NSAPI_STATUS_GLOBAL_UP:

                display.setTextColor(ST7789_GREEN, ST7789_BLACK);
                display.printf("EthIF global up     ");
                display.setTextColor(ST7789_YELLOW, ST7789_BLACK);
                printf("EthIF global up\n");
                network->get_ip_address(&mySocketAddress);
                printf("my IP is: %s\n", mySocketAddress.get_ip_address());
                onEthIfUp();
                display.setCursor(10, 40);
                display.printf(mySocketAddress.get_ip_address());
                break;
            case NSAPI_STATUS_DISCONNECTED:
                display.setTextColor(ST7789_RED, ST7789_BLACK);
                display.printf("EthIF disconnected  ");
                printf("EthIF disconnected\n");
                display.setCursor(10, 40);
                display.printf("                ");
                onEthIfDown();
                break;
            case NSAPI_STATUS_CONNECTING:
                onEthIfDown();
                display.setTextColor(ST7789_CYAN, ST7789_BLACK);
                display.printf("EthIF connecting    ");
                printf("EthIF connecting\n");
                display.setCursor(10, 40);
                display.printf("                ");
                break;
            case NSAPI_STATUS_ERROR_UNSUPPORTED:
                display.setTextColor(ST7789_RED, ST7789_BLACK);
                display.printf("status unknown      ");
                printf("EthIF status unknown\n");
                break;
        }
    }
}

void ethernet_init() 
{
    // Connect to the network with the default networking interface
    // using non blocking, async event driven
    network = NetworkInterface::get_default_instance();
    if (!network) {
        printf("Cannot connect to the network, see serial output\n");
    } 

    network->set_blocking(true);
    //network->attach(callback(onEthIfEvent));
    network->connect();
}
