# DeviceStutterFix
Monster Hunter Rise stutters when devices are plugged in or out as it tries to figure out if there's a gamepad to use for the game. 

Sadly this happens even for non-controller devices, which is especially bad when games from Xbox Game Pass or the Microsoft Store are installed, since Windows uses virtual disk drives for these games which randomly get created and removed all the time, even when the games don't run.
Every time this happens the game stutters.

This plugin intercepts WM_DEVICECHANGE messages and only sends them to the game when an XInput device triggered the message.

## Installation
1. Install REFramework (at least v1.1.1 required).
2. Put REF_DeviceStutterFix.dll into reframework/plugins/ inside your Monster Hunter Rise base directory.
