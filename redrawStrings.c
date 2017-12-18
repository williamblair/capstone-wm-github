#include "redrawStrings.h"

// variables from main.c
extern Display *d;
extern WMClient *clientHead;

// variables from reparent.c
extern unsigned long titleFontColor;

// variables from taskbar.c
extern unsigned long taskbarFontColor;

void redrawStrings(void)
{
    WMClient *c = clientHead;
    while(c != NULL)
    {
        // set the color for the title bars
        XSetForeground(d, DefaultGC(d, DefaultScreen(d)), titleFontColor);
        
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
        
        // set the color of the font of the taskbar
        XSetForeground(d, DefaultGC(d, DefaultScreen(d)), taskbarFontColor);
        
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
}