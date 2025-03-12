#!/bin/sh

CHOICE=`echo -e "HDMI\nVGA" | dmenu -i -p "Choose Port to Extend Monitor: "`

[ $CHOICE = "HDMI" ] `xrandr --output HDMI-1 --auto --right-of default && feh --bg-scale ~/Pictures/Wallpapers/wallpaperflare.com_wallpaper.jpg &`
[ $CHOICE = "VGA"  ] `xrandr --output VGA-1 --auto --right-of default && feh --bg-scale ~/Pictures/Wallpapers/wallpaperflare.com_wallpaper.jpg &`
