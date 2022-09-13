#! /bin/bash

CZ=1
CA=1
YI=1

# xset fp rehash &
# xset fp+ /home/zyal/.fonts &

picom -f &

hsetroot -solid '#000000' &

slstatus &
dunst &

sleep 1

pnmixer &
$HOME/.fehbg &

export EDITOR=vim
export VISUAL=vim

# start some nice programs

if [ -d /etc/X11/xinit/xinitrc.d ] ; then
 for f in /etc/X11/xinit/xinitrc.d/?*.sh ; do
  [ -x "$f" ] && . "$f"
 done
 unset f
fi

while true; do
	BCHECK
	GREET
	sleep 3s
done &

exec dwm
