#include <X11/Xlib.h>

#include <stdio.h>

#ifndef WMCLIENT_H_INCLUDED
#define WMCLIENT_H_INCLUDED

// groups frame windows and the actual app windows
typedef struct WMClient
{
    Window frame;    // the border/container window
    Window titleBar; // the title bar to click/drag
    Window minWin; // minimize, maximize, and close subwindows
    Window maxWin;
    Window closeWin;
    Window child;  // the actual application content window
    Window taskIcon; // the window that shows up on the taskbar

    unsigned int x; // the x and y position before maximizing the window
    unsigned int y;
    unsigned int w; // the width and height before maximizing the window
    unsigned int h;
    
    Bool maximized; // true if the window is fullscreen
    Bool minimized; // true if the window is minimized
    
    char title[50]; // title of the window

    struct WMClient *next;
} WMClient;

#endif
