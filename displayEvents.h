/* For when windows are drawn to the screen */

#include <X11/Xlib.h>

#include <stdio.h>

#include "reparent.h"

#ifndef DISPLAY_EVENTS_H_INCLUDED
#define DISPLAY_EVENTS_H_INCLUDED

Bool hCreateNotify(const XCreateWindowEvent e);
Bool hReparentNotify(const XReparentEvent e);
Bool hMapNotify(const XMapEvent e);
Bool hMapRequest(const XMapRequestEvent e);
Bool hExpose(const XExposeEvent e);

#endif
