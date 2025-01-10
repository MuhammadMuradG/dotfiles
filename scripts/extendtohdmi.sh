#!/bin/sh

xrandr --output LVDS-1 --gamma 1.0:0.8:0.6 --brightness 0.9 &&

xrandr --output HDMI-1 --auto --right-of LVDS-1 &&

feh --bg-scale ~/Pictures/Wallpapers/wallpaperflare.com_wallpaper.jpg &
