# Configure the keyboard
setxkbmap -layout us,ara -variant ,digits -option grp:alt_shift_toggle

# Configure the wallpaper and transparency
feh --bg-scale ~/Pictures/Wallpapers/wallpaperflare.com_wallpaper.jpg &
xcompmgr &

# Start slstatus and ssh with dwm
slstatus & exec ssh-agent dwm
