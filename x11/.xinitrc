#!/bin/bash

# load xresources
xrdb -merge ~/.Xresources

# load fontset
xset +fp ~/.fonts &
xset fp rehash &

# wallpaper
feh --bg-fill ~/Pictures/Wallpaper/multicolor.jpg

# session
session=${1:-pekwm}
case $session in
    2bwm	      ) exec 2bwm;;
    dwm               ) exec dwm;;
    openbox           ) exec openbox-session;;
    pekwm             ) exec pekwm;;
    *) exec $1;;
esac
