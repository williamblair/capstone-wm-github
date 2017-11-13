#include <X11/Xlib.h>
#include <stdio.h>

#ifndef DESTROY_EVENTS_H_INCLUDED
#define DESTROY_EVENTS_H_INCLUDED

Bool hDestroyNotify(const XDestroyWindowEvent e);
Bool hUnmapNotify(const XUnmapEvent e);

#endif
