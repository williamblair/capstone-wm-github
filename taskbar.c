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

Bool resizeTaskIcons(void)
{
    int numClients = 0;    // the total number of WMClients
    int taskIconWidth = 0; // the width of 1 taskbar window
    int x = 0;             // the x position of the current client icon
    
    WMClient *c = clientHead;
    if(!c) {
        fprintf(stderr, "resizeTaskIcons: clientHead NULL!\n");
        return False;
    }
    
    // Get the total number of clients
    while(c != NULL)
    {
        numClients++;
        c = c->next;
    }
    
    // calculate the width of each taskIcon window
    taskIconWidth = WidthOfScreen(DefaultScreenOfDisplay(d)) / numClients;
    
    // resize and move each client icon
    c = clientHead;
    while(c != NULL)
    {
        // move/resize the window
        XMoveResizeWindow(
            d, 
            c->taskIcon, 
            x, 
            0, 
            taskIconWidth, 
            TASKBAR_HEIGHT
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
        
        x += taskIconWidth;
        
        c = c->next;
    }
    
    return True;
}