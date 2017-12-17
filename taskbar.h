#include <X11/Xlib.h>

#include <stdio.h>

#include "WMClient.h"

#ifndef TASKBAR_H_INCLUDED
#define TASKBAR_H_INCLUDED

#define TASKBAR_HEIGHT 25

Bool createTaskbar(void);
Bool resizeTaskIcons(void);

#endif // TASKBAR_H_INCLUDED
