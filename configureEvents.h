#include <X11/Xlib.h>
#include <stdio.h>

#ifndef CONFIGURE_EVENTS_H_INCLUDED
#define CONFIGURE_EVENTS_H_INCLUDED

Bool hConfigureNotify(const XConfigureEvent e);
Bool hConfigureRequest(const XConfigureRequestEvent e);

#endif
