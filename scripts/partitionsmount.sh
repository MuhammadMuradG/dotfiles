#!/usr/local/bin/zsh

choice=$(ls "/dev/ada0s"* | dmenu -i -p "Choose partition: ")

[ $choice = "ada0s3"   ] && st sudo ntfs-3g /dev/ada0s3 /media/windows-partition
[ $choice = "ada0s5"   ] && st sudo ntfs-3g /dev/ada0s5 /media/data-partition
[ $choice = "/dev/ada0s"*   ] && st echo "Does not match with valid partition!"
