#include "destroyEvents.h"
#include "reparent.h"
#include "taskbar.h"

// variables from main.c
extern Display *d;
extern WMClient *clientHead;

Bool hDestroyNotify(const XDestroyWindowEvent e)
{
    printf("Destroy Notify Event!\n");
    
    resizeTaskIcons();
    
    return True;
}

Bool hUnmapNotify(const XUnmapEvent e)
{
    // TODO - unframe the window
    printf("Unmap Notify Event!\n");
    
    // Ignore event if it is triggered by reparenting a window that was mapped
    // before the window manager started.
    //
    // Since we receive UnmapNotify events from the SubstructureNotify mask, the
    // event attribute specifies the parent window of the window that was
    // unmapped. This means that an UnmapNotify event from a normal client window
    // should have this attribute set to a frame window we maintain. Only an
    // UnmapNotify event triggered by reparenting a pre-existing window will have
    // this attribute set to the root window.
    if(e.event == RootWindow(d, DefaultScreen(d))) {
        printf("Ignore unmapnotify for reparented pre-existing window!\n");
        return True;
    }
    
    // ignore if the windows were just minimized
    WMClient *c = clientHead;
    while(c != NULL)
    {
        if(c->child == e.window ||
           c->frame == e.window ||
           c->minWin == e.window ||
           c->maxWin == e.window ||
           c->closeWin == e.window ||
           c->titleBar == e.window ) break;

        c = c->next;
    }
    if(c == NULL){
        printf("hUnmapNotify: failed to find event window in clients!\n");
    }
    else{
        if(c->minimized){
            printf("Unmap event is for minimized window, not destroying!\n");
            return True;
        }
    }
    
    // destroy the client and reparent the child window to the
    // root before it is destroyed
    // defined in reparent.c
    unparentWindow(e.window);
    
    return True;
}

