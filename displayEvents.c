/* For when windows are drawn to the screen */

#include "displayEvents.h"

// variables from main.c
extern Display *d;
extern WMClient *clientHead;

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
    
    WMClient *c = clientHead;
    
    while(c != NULL)
    {
        // redraw the title bar string
        XWindowAttributes fAttribs; // frame attributes
        XGetWindowAttributes(d, c->frame, &fAttribs);
        XDrawString(
            d,
            c->titleBar,                                        // Drawable d
            DefaultGC(d, DefaultScreen(d)),                        // GC
            (fAttribs.width / 2) - strlen(c->title)*CHAR_WIDTH, // x
            (TITLE_HEIGHT / 2) + CHAR_WIDTH/2,                                      // y
            c->title,                                           // string
            strlen(c->title)                                    // length of string
        );
        
        // draw the program title
        XDrawString(
            d, 
            c->taskIcon, 
            DefaultGC(d, DefaultScreen(d)),
            5,
            TASKBAR_HEIGHT / 2,
            c->title,
            strlen(c->title)
        );
        
        c = c->next;
    }
    
    return True;
}
