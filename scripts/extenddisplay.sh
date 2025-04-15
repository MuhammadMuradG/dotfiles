#!/bin/sh

CHOICE=$(echo -e "Refresh\nExtend\nDuplicate" | dmenu -i -p "Choose the action on second monitor: ")

if [ "$CHOICE" = "Refresh" ]
then
    xrandr
    xrandr --output eDP-1 --auto
    xrandr --output HDMI-2 --auto
elif [ "$CHOICE" = "Extend" ]
then
    xrandr --output HDMI-2 --auto --right-of eDP-1
elif [ "$CHOICE" = "Duplicate" ]
then
    xrandr --output HDMI-2 --auto --scale-from 1920x1080 --same-as eDP-1
fi

feh --bg-scale ~/Pictures/Wallpapers/wallpaperflare.com_wallpaper.jpg &
