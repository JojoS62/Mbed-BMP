#pragma once

#include "mbed.h"
#include "NetworkInterface.h"

extern NetworkInterface* network;
extern Callback<void()> cbStartServer;
extern Callback<void()> cbStopServer;

void ethernet_init();
