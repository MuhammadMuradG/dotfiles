#!/bin/sh

CHOICE=`ls "/dev/ada0s"* | dmenu -i -p "Choose partition: "`

case $CHOICE in
	"/dev/ada0s2")
		`st sudo ntfs-3g /dev/ada0s2 /media/windows-partition`
		;;
	"/dev/ada0s5")
		`st sudo ntfs-3g /dev/ada0s5 /media/data-partition`
		;;
	"/dev/ada0s"*)
		`st echo "Does not match with valid partition!"`
		;;
esac
