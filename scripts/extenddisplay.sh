#!/bin/sh

CHOICE=`echo -e "Extend\nDuplicate" | dmenu -i -p "Choose the action on second monitor: "`

[ $CHOICE = "Extend" ] `xrandr --output HDMI-2 --auto --right-of eDP-1 && feh --bg-scale ~/Pictures/Wallpapers/wallpaperflare.com_wallpaper.jpg &`
[ $CHOICE = "Duplicate" ] `xrandr --output HDMI-2 --same-as eDP-1 && feh --bg-scale ~/Pictures/Wallpapers/wallpaperflare.com_wallpaper.jpg &`
