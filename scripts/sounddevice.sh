#!/bin/sh

CHOICE=$(echo -e "SoundCard\nAirbuds" | dmenu -i -p "Choose the sound device: ")

if [ "$CHOICE" = "SoundCard" ]
then
    st sudo sh -c 'pkill virtual_oss; sysctl hw.snd.basename_clone=1'
elif [ "$CHOICE" = "Airbuds" ]
then
    st sudo sh -c 'virtual_oss -S -a o,-4 -C 2 -c 2 -r 48000 -b 16 -s 4ms -R /dev/dsp1 -P /dev/bluetooth/airbuds -d dsp -t vdsp.ctl &'
fi
