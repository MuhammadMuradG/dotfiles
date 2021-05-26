#!/usr/local/bin/zsh

choice=$(echo "Shutdown\nReboot\nLogout\nExit" | dmenu -i -p "Choose action: ")

[ $choice = "Shutdown" ] && st sudo poweroff
[ $choice = "Reboot"   ] && st sudo reboot
[ $choice = "Logout"   ] && slock
[ $choice = "Exit"     ] && pkill dwm
