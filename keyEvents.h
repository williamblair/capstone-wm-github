#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <stdio.h>
#include <string.h>

#ifndef KEY_EVENTS_H_INCLUDED
#define KEY_EVENTS_H_INCLUDED

Bool hKeyPress(const XKeyEvent e);
Bool hKeyRelease(const XKeyEvent e);

#endif
