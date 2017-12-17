#include "taskbar.h"
#include "reparent.h"

// extern variables from main.c
extern Display *d; // connection to the X display
extern WMClient *clientHead; // the head of the WMClient linked list

// Global Variables
Window taskbar;

Bool createTaskbar(void)
{
    taskbar = XCreateSimpleWindow(
        d, 
        RootWindow(d, DefaultScreen(d)),
        0,
        HeightOfScreen(DefaultScreenOfDisplay(d))-TASKBAR_HEIGHT,
        WidthOfScreen(DefaultScreenOfDisplay(d)),
        TASKBAR_HEIGHT, 
        0, 
        BlackPixel(d,DefaultScreen(d)), 
        WhitePixel(d, DefaultScreen(d))
    );
    
    XMapWindow(d, taskbar);
    
    return True;
}