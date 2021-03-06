#include <X11/Xlib.h>
#include <stdio.h>

#include "WMClient.h"
#include "taskbar.h"
#include "redrawStrings.h"
#include "reparent.h"

#ifndef MOTION_EVENTS_H_INCLUDED
#define MOTION_EVENTS_H_INCLUDED

Bool hMotionNotify(const XMotionEvent e);

#endif
