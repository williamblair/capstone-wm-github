#include "keyEvents.h"

// variables from main.c
extern Display *d;

Bool hKeyPress(const XKeyEvent e)
{
    printf("Key Press Event!\n");
    
    // Close window on alt+f4
    if( (e.state & Mod1Mask) && 
        (e.keycode == XKeysymToKeycode(d, XK_F4))
      )
    {
        // Find if we support standard deletion protocols
        Atom *supportedProtocols = NULL;
        int   nProtocols = 0; // the number of supported protocols
        XGetWMProtocols(
            d, 
            e.window, 
            &supportedProtocols,
            &nProtocols
        );
        int i=0;
        while(i < nProtocols)
        {
            if(*(supportedProtocols + i) == XInternAtom(d, "WM_DELETE_WINDOW", False)) {
                printf("Found support for WM_DELETE_WINDOW!\n");
                break;
            }
            i++;
        }
        // WM_DELETE_WINDOW not supported
        if(i >= nProtocols) {
            printf("Failed to find support for WM_DELETE_WINDOW!\n");
            
            XKillClient(d, e.window);
            
        }
        // WM_DELETE_WINDOW supported
        else {
            // send an XEvent for deleting the window
            XEvent msg;
            
            memset(&msg, 0, sizeof(msg));
            msg.xclient.type = ClientMessage;
            msg.xclient.message_type = XInternAtom(d, "WM_PROTOCOLS", False);
            msg.xclient.window = e.window;
            msg.xclient.format = 32;
            msg.xclient.data.l[0] = XInternAtom(d, "WM_DELETE_WINDOW", False);
            
            XSendEvent(d, e.window, False, 0, &msg);
        }
    }
    
    // TODO - add alt+tab to switch windows
    
    return True;
}


Bool hKeyRelease(const XKeyEvent e)
{
    printf("Key Release Event!\n");
    
    return True;
}