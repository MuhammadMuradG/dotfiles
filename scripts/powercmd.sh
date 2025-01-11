#!/bin/sh

CHOICE=`echo -e "Shutdown\nRestart\nLogout\nExit" | dmenu -i -p "Choose action: "`

[ $CHOICE = "Shutdown" ] && `st sudo shutdown -p now`
[ $CHOICE = "Restart"  ] && `st sudo shutdown -r now`
[ $CHOICE = "Logout"   ] && `slock`
[ $CHOICE = "Exit"     ] && `st sudo pkill dwm`
