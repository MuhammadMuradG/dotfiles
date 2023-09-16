# Configure the keyboard
setxkbmap -layout us,ara -variant ,digits -option grp:alt_shift_toggle

# Start slstatus and ssh with dwm
slstatus & exec ssh-agent dwm
