# capstone-wm-github
github host of capstone window manager

# BUILD
Compile with 'make', clean with 'make clean'

requires Xlib and Xpm libraries (libx11-dev and libxpm-dev)

# RUN
You have two options:

1) Using Xephyr
Install xypher, and then run

  make
  ./build_and_run.sh

2) xinit/startx

add this to the bottom of ~/.xinitrc:

  exec ./main

then run 'startx' from this directory

Currently there is no way to exit the window manager so you'll have to 
hop to a different tty and kill the startx process :P
