#include "wake.h"
#include "WakeOnLan.h"
#include "WiFi.h"
#include "config.h"

WiFiUDP UDP;
WakeOnLan WOL(UDP);

void wol_init()
{
    UDP.begin(9);

    WOL.setRepeat(3, 100);
    WOL.calculateBroadcastAddress(WiFi.localIP(), WiFi.subnetMask());
}

void wake()
{
    WOL.sendMagicPacket(wake_device_MAC.c_str());
}