#!/bin/bash
#/usr/bin/enlightenment_start.oe >/dev/null 2>/dev/null &

# Prepare the display and X session
echo "255" > /sys/class/leds/lcd-backlight/brightness
sleep 1
export DISPLAY=:0.0
/usr/bin/Xorg -br >/dev/null 2>/dev/null &

#Launch streaming server
#ffserver

#Launch default X app
fb-startup &

