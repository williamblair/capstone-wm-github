/* For when windows are drawn to the screen */

#include "displayEvents.h"

// variables from main.c
extern Display *d;
extern Window task_win2;

Bool hCreateNotify(const XCreateWindowEvent e)
{
    printf("Create Notify Event!\n");
    
    return True;
}

Bool hReparentNotify(const XReparentEvent e)
{
    printf("Reparent Notify Event!\n");
    
    return True;
}

Bool hMapNotify(const XMapEvent e)
{
    printf("Map Notify Event!\n");
    
    return True;
}

Bool hMapRequest(const XMapRequestEvent e)
{
    printf("Map Request Event!\n");
    
    printf("Before Reparent Window!\n");
    reparentWindow(e.window, False);
    printf("After reparent window!\n");
    
    XMapWindow(d, e.window);
    
    return True;
}

Bool hExpose(const XExposeEvent e)
{
    printf("Expose Event!\n");
    
    //XDrawString(d, task_win2, DefaultGC(d, DefaultScreen(d)), 5, 15, "Win 1", strlen("Win 1"));
    
    return True;
}
