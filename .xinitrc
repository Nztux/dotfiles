#!/bin/bash

# load xresources
xrdb -merge ~/.Xresources

# load fontset
xset +fp ~/.fonts &
xset fp rehash &

# session
exec dwm
