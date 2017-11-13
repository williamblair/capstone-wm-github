#include <X11/Xlib.h>
#include <stdio.h>

#include "reparent.h"

#ifndef BUTTON_EVENTS_H_INCLUDED
#define BUTTON_EVENTS_H_INCLUDED

Bool hButtonPress(const XButtonEvent e);
Bool hButtonRelease(const XButtonEvent e);

Bool hMinimize(const XButtonEvent e, WMClient *c);
Bool hMaximize(const XButtonEvent e, WMClient *c);
Bool hClose(const XButtonEvent e, WMClient *c);

#endif
