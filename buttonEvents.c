#include "buttonEvents.h"

// variables from main.c
extern Display *d;
extern WMClient *clientHead;

/* location of the programs list for the program menu,
 * set by parseRC in initCapstone.c */
char *menuFilePath = NULL;

// the initial position of the mouse on a movement event
int startMouseX = 0;
int startMouseY = 0;

// the initial position of the window on a movement event
int startWinX = 0;
int startWinY = 0;

// the initial size of the window on a resize event
int startWinWidth = 0;
int startWinHeight = 0;

// function just for our purposes here to unminimze a window
Bool hRemap(const XButtonEvent e, WMClient *c);

Bool hButtonPress(const XButtonEvent e)
{
    printf("Button Press Event!\n");
    
    // if the root window was pressed we want to bring up our program menu
    if(e.window == RootWindow(d, DefaultScreen(d)))
    {
        printf("Root Window Press!\n");
        
        // initial program to run
        char menuCommand[100];
        sprintf(menuCommand, "./ProgramMenu/main %d %d %s &", e.x_root, e.y_root, menuFilePath);
        
        printf("Menu Command: %s\n", menuCommand);
        
        // run the program menu!
        system(menuCommand);
        
        return True;
    }

    // Save the current mouse position to check for difference while moving
    startMouseX = e.x_root;
    startMouseY = e.y_root;

    // subwindow meaning the root window took the event
    // but there is a window under it
    /*if(e.subwindow != None){

        printf("Subwindow not none!\n");

        // find the client window and raise it
        WMClient *temp = clientHead;
        while(temp != NULL)
        {
            if(temp->child == e.subwindow ||
               temp->titleBar == e.subwindow) break;
            temp = temp->next;
        }
        if(temp == NULL){
            printf("hButtonPress: failed to find child/titlebar in clients!\n");
            return False;
        }

        // raise the frame
        XRaiseWindow(d, temp->frame);

        return True;
    }*/

    // Save current window information

    WMClient *temp = clientHead;
    while(temp != NULL)
    {
        // either the frame or child window is clicked
        //if(temp->child == e.window) break;
        if(temp->child    == e.window ||
           temp->titleBar == e.window ||
           temp->minWin   == e.window ||
           temp->maxWin   == e.window ||
           temp->taskIcon == e.window ||
           temp->closeWin == e.window) break;
        temp = temp->next;
    }
    if(temp == NULL){
        printf("hButtonPress: failed to find child or frame within clients!\n");
        return False;
    }
    
    /* test if any special windows were pressed */
    if(e.window == temp->minWin)
    {
        hMinimize(e, temp);
        return True;
    }
    else if(e.window == temp->maxWin)
    {
        hMaximize(e, temp);
        return True;
    }
    else if(e.window == temp->closeWin)
    {
        hClose(e, temp);
        return True;
    }
    else if(e.window == temp->taskIcon)
    {
        hRemap(e, temp);
        redrawStrings();
        return True;
    }

    Window r;
    int x, y;
    unsigned int w, h, bWidth, depth;
    XGetGeometry(
        d,
        temp->frame,
        &r,
        &x, &y,
        &w, &h,
        &bWidth,
        &depth
    );

    startWinX = x;
    startWinY = y;

    startWinWidth = w;
    startWinHeight = h;

    XRaiseWindow(d, temp->frame);

    redrawStrings();

    /*XWindowAttributes fAttribs; // frame attributes
    XGetWindowAttributes(d, temp->frame, &fAttribs);
    XDrawString(
        d,
        temp->titleBar,                                        // Drawable d
        DefaultGC(d, DefaultScreen(d)),                        // GC
        (fAttribs.width / 2) - strlen(temp->title)*CHAR_WIDTH, // x
        (TITLE_HEIGHT / 2) + CHAR_WIDTH/2,                                      // y
        temp->title,                                           // string
        strlen(temp->title)                                    // length of string
    );*/

    return True;
}

Bool hButtonRelease(const XButtonEvent e)
{
    printf("Button Release Event!\n");

    return True;
}

Bool hMinimize(const XButtonEvent e, WMClient *c)
{
    printf("Minimize area!\n");


    /* Get current window size/position and store in client */
    /*WMClient *temp = clientHead;
    while(temp != NULL)
    {
        if(temp->minWin == xE.xbutton.subwindow) break;
        temp = temp->next;
    }
    if(temp != NULL){
    */
        XWindowAttributes winAttribs;
        XGetWindowAttributes(d, c->frame, &winAttribs);

        /* store current position */
        c->x = winAttribs.x;
        c->y = winAttribs.y;
        c->w = winAttribs.width;
        c->h = winAttribs.height;

        /* Iconify the window */
        XIconifyWindow(d, c->child, DefaultScreen(d));
        printf("After iconify window!\n");

        /* Set minimizing so we will run the
         * code in ClientMessage */
        //minimizing = True;
        
        /* Make the windows invisible */
        XUnmapSubwindows(d, c->frame);
        XUnmapWindow(d, c->frame);
                        
        /* set minimized to True*/
        c->minimized = True;

        return True;
}

Bool hMaximize(const XButtonEvent e, WMClient *c)
{
    printf("Maximize Button Clicked!\n");

        XWindowAttributes winAttribs;
        XGetWindowAttributes(d, c->frame, &winAttribs);
        if(!c->maximized)
        {
            c->x = winAttribs.x;
            c->y = winAttribs.y;
            c->w = winAttribs.width;
            c->h = winAttribs.height;

            printf("Stored attributes: (%d,%d,%d,%d)\n", c->x, c->y, c->w, c->h);
            
            /* Maximize the window */
           XMoveResizeWindow(
                d, 
                c->frame,
                0, 0,    // x, y
                WidthOfScreen(DefaultScreenOfDisplay(d)) - BORDER_WIDTH*2, // w, h
                HeightOfScreen(DefaultScreenOfDisplay(d)) - BORDER_WIDTH*2
            );
        }
        else
        {
            /* Restore the previous size and position of the
             * window before it was maximized */
            XMoveResizeWindow(
                d, 
                c->frame,
                c->x, c->y,    // x, y
                c->w, c->h // w, h
            );
        }
        
        XWindowAttributes fAttribs;
        XGetWindowAttributes(d, c->frame, &fAttribs);
        
        /* Now resize the children */
        XResizeWindow(
            d,
            c->child,
            fAttribs.width,
            fAttribs.height - TITLE_HEIGHT
        );
        XResizeWindow(
            d,
            c->titleBar,
            fAttribs.width - BUTTON_SIZE*3,
            TITLE_HEIGHT
        );
        XMoveWindow(
            d,
            c->minWin,
            fAttribs.width - BUTTON_SIZE*3,
            0
        );
        XMoveWindow(
            d,
            c->maxWin,
            fAttribs.width - BUTTON_SIZE*2,
            0
        );
        XMoveWindow(
            d,
            c->closeWin,
            fAttribs.width - BUTTON_SIZE*1,
            0
        );
                                
        // Signal in the configure notify event we want this to run
        //maximize_window = True;
        // switch the status of the window's maximize status
        c->maximized = !c->maximized;

        // redraw the title
        XDrawString(
            d,
            c->titleBar,                                        // Drawable d
            DefaultGC(d, DefaultScreen(d)),                        // GC
            (fAttribs.width / 2) - strlen(c->title)*CHAR_WIDTH, // x
            (TITLE_HEIGHT / 2) + CHAR_WIDTH/2,                                      // y
            c->title,                                           // string
            strlen(c->title)                                    // length of string
        );
    
    return True;
}

Bool hClose(const XButtonEvent e, WMClient *c)
{
    printf("Close button pressed!\n");
    
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
            
            XKillClient(d, c->child);
            
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
            
            XSendEvent(d, c->child, False, 0, &msg);
        }
    
    return True;
}

Bool hRemap(const XButtonEvent e, WMClient *c)
{
    printf("Remap Window Event on window: %s\n", c->title);
    
    // reset the minimized boolean
    c->minimized = False;
    
    // remap the frame
    XMapRaised(d, c->frame);
    
    // remap all of the windows
    XMapSubwindows(d, c->frame);
    
    return True;
}
