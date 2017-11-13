/* reframes given windows */

#include "reparent.h"

// variables from main.c
extern Display *d;
extern WMClient *clientHead; // the head of the WMClient linked list
extern Window   task_bar; //task bar window for reparenting

// global variables
Pixmap minPixmap; // minimize image
Pixmap maxPixmap; // maximize image
Pixmap unmaxPixmap; // unmaximize image
Pixmap closePixmap; // close window image

unsigned long  titleBarColor = 0x000000; // color of the titleBar
unsigned long  borderColor   = 0x000000; // color of the window border

// function prototypes
Window make_task_window(int x_pos);

Bool reparentWindow(Window child, Bool before_wm)
{
    WMClient *c = NULL; // our current client to work on

    /* create a new entry in the list */
    if(clientHead == NULL) {
        clientHead = (WMClient *)malloc(sizeof(WMClient));
        /* TODO - test for NULL */

        c = clientHead;
    }
    else {
        /* get the last entry in the client list */
        WMClient *temp = clientHead;
        while(temp->next != NULL)
            temp = temp->next;

        c = (WMClient *)malloc(sizeof(WMClient));
        /* TODO - test for NULL */

        /* assign the new client structure to the end of the list */
        temp->next = c;
    }
    c->next  = NULL;
    c->child = child;
    c->maximized = False;
    c->minimized = False;
    c->w = c->h = c->x = c->y=0; // initialize the position variables
    
    // Get window info
    XWindowAttributes childWinInfo;
    XGetWindowAttributes(d, child, &childWinInfo);
    
    // if the window was created before the wm started,
    // frame only if visible and doesn't set override redirect
    if(before_wm) {
        if(childWinInfo.override_redirect ||
           childWinInfo.map_state != IsViewable) {
            printf("Before WM & override_redirect OR mapstate != IsViewable!\n");
            return True;
        }
    }
    
    // create the frame
    c->frame = XCreateSimpleWindow(
        d,
        RootWindow(d, DefaultScreen(d)),
        childWinInfo.x,
        childWinInfo.y,
        childWinInfo.width,
        childWinInfo.height+TITLE_HEIGHT,
        BORDER_WIDTH,
        borderColor,      // TODO - change this to the read in border color
        0x000000       // TODO - change to frame bg color
    );
    
    // create the title bar
    c->titleBar = XCreateSimpleWindow(
        d,
        c->frame,
        0,
        0,
        childWinInfo.width - BUTTON_SIZE*3, // give room for the 3 buttons
        TITLE_HEIGHT,
        0,
        0x000000,      // TODO - change this to the read in border color
        titleBarColor       // TODO - change to frame bg color
    );
    
    /* Create each button window */
    c->minWin = XCreateSimpleWindow(d,
	                             c->frame,    // Display *parent
	                             childWinInfo.width-(BUTTON_SIZE*3), // x coord
	                             0,                                // y coord
	                             BUTTON_SIZE,           // window width
	                             BUTTON_SIZE,              // window height
	                             0,                       // border size
	                             WhitePixel(d, DefaultScreen(d)),    // border
	                             0x00FF00);   // background
	c->maxWin = XCreateSimpleWindow(d,
	                             c->frame,    // Display *parent
	                             childWinInfo.width-(BUTTON_SIZE*2), // x coord
	                             0,                                // y coord
	                             BUTTON_SIZE,           // window width
	                             BUTTON_SIZE,              // window height
	                             0,                       // border size
	                             WhitePixel(d, DefaultScreen(d)),    // border
	                             0x00FF00);   // background      
    c->closeWin = XCreateSimpleWindow(d,
                                    c->frame,    // Display *parent
                                    childWinInfo.width-(BUTTON_SIZE*1), // x coord
                                    0,                                // y coord
                                    BUTTON_SIZE,           // window width
                                    BUTTON_SIZE,              // window height
                                    0,                       // border size
                                    WhitePixel(d, DefaultScreen(d)),    // border
                                    0x00FF00);   // background        
    
    c->task_icon = None;//XCreateSimpleWindow(d, task_bar, 21, ((get_task_attrbs.height)/4), 20, task_win_h, 0, 0, 0xf46e42);                                
    
    /* give each button window their image */
    XSetWindowBackgroundPixmap(d, c->minWin, minPixmap);
    XSetWindowBackgroundPixmap(d, c->maxWin, maxPixmap);
    XSetWindowBackgroundPixmap(d, c->closeWin, closePixmap);
    
    //XMapWindow(d, c->minWin);
    //XMapWindow(d, c->maxWin);
    //XMapWindow(d, c->closeWin);
    
    /* Grab a the mouse click on any of the min/max/close windows */
    XGrabButton(
        d,
        Button1,
        //Mod1Mask,
        None,
        c->minWin,
        False,
        ButtonPressMask | ButtonReleaseMask | ButtonMotionMask,
        GrabModeAsync,
        GrabModeAsync,
        None,
        None
    );
    XGrabButton(
        d,
        Button1,
        //Mod1Mask,
        None,
        c->maxWin,
        False,
        ButtonPressMask | ButtonReleaseMask | ButtonMotionMask,
        GrabModeAsync,
        GrabModeAsync,
        None,
        None
    );
    XGrabButton(
        d,
        Button1,
        //Mod1Mask,
        None,
        c->closeWin,
        False,
        ButtonPressMask | ButtonReleaseMask | ButtonMotionMask,
        GrabModeAsync,
        GrabModeAsync,
        None,
        None
    );
    
    // map the child window to our client
    c->child = child;
    
    // select input on the frame
    XSelectInput(
        d,
        c->frame,
        SubstructureNotifyMask | SubstructureRedirectMask
    );
    
    // Grab left mouse click on the title bar
    XGrabButton(
        d,
        Button1,
        //Mod1Mask,
        None,
        c->titleBar,
        False,
        ButtonPressMask | ButtonReleaseMask | ButtonMotionMask,
        GrabModeAsync,
        GrabModeAsync,
        None,
        None
    );
    
    // add the child to save set to restore if we crash
    XAddToSaveSet(d, child);
    
    // reparent the child window to our frame
    XReparentWindow(
        d,
        child,
        c->frame,
        0, TITLE_HEIGHT
    );
    
    // display the frame
    //XMapWindow(d, c->frame);
    //XMapWindow(d, c->titleBar);
    
    // Grab buttons on the child window
    //   a. Move windows with alt + left button.
    XGrabButton(
        d,
        Button1,
        Mod1Mask,
        child,
        False,
        ButtonPressMask | ButtonReleaseMask | ButtonMotionMask,
        GrabModeAsync,
        GrabModeAsync,
        None,
        None);
    //   b. Resize windows with alt + right button.
    XGrabButton(
        d,
        Button3,
        Mod1Mask,
        child,
        False,
        ButtonPressMask | ButtonReleaseMask | ButtonMotionMask,
        GrabModeAsync,
        GrabModeAsync,
        None,
        None);
    //   c. Kill windows with alt + f4.
    XGrabKey(
        d,
        XKeysymToKeycode(d, XK_F4),
        Mod1Mask,
        child,
        False,
        GrabModeAsync,
        GrabModeAsync);
    //   d. Switch windows with alt + tab.
    XGrabKey(
        d,
        XKeysymToKeycode(d, XK_Tab),
        Mod1Mask,
        child,
        False,
        GrabModeAsync,
        GrabModeAsync);
        
    // Get the name of the window
    char *childName = NULL;
    if(XFetchName(d, child, &childName)) {
        printf("Reparenting Window! Name: %s\n", childName);
        strcpy(c->title, childName);
    }
        
    // test drawing the title to the titleBar
    /*XDrawString(
        d, 
        c->titleBar, 
        DefaultGC(d, DefaultScreen(d)),
        10, 10,
        c->title,
        strlen(c->title)
    );*/
    
    //XWindowAttributes fAttribs; // frame attributes
    //XGetWindowAttributes(d, temp->frame, &fAttribs);
    XDrawString(
        d,
        c->titleBar,                                        // Drawable d
        DefaultGC(d, DefaultScreen(d)),                        // GC
        (childWinInfo.width / 2) - strlen(c->title)*CHAR_WIDTH, // x
        (TITLE_HEIGHT / 2) + CHAR_WIDTH/2,                                      // y
        c->title,                                           // string
        strlen(c->title)                                    // length of string
    );
    
    if(childName) XFree(childName);
    
    // display all child windows/window frame
    XMapWindow(d, c->frame);
    XMapSubwindows(d, c->frame);
    
    return True;
}

Bool unparentWindow(Window child)
{
    // Find the client of the corresponding child window
    WMClient *temp = clientHead;
    while(temp != NULL){
        if(temp->child == child)
            break;
        temp = temp->next;
    }
    if(temp == NULL) {
        printf("unparentwindow: failed to find child window!\n");
        return False;
    }
    
    // Unmap the frame
    XUnmapWindow(d, temp->frame);
    
    // reparent the client window to the root window
    XReparentWindow(
        d,
        child,
        RootWindow(d, DefaultScreen(d)),
        0,0
    );
    
    // remove the app window from the save set since we aren't reparenting it
    XRemoveFromSaveSet(d, child);
    
    // delete the client and all of its subwindows
    deleteClient(child);
    
    return True;
}

Bool deleteClient(Window child)
{
    WMClient *temp = clientHead;
    WMClient *head = temp;
    WMClient *caboose = NULL;
    if(temp!= NULL) caboose = temp->next;
    
    /* Make temp equal to the client with the sent child */
    while(temp != NULL){

        //if(temp->frame == parent) break;
        if(temp->child == child) break;
        /* keep track of the entry before and after temp */
        head = temp;
        temp = temp->next;
        if(temp != NULL) caboose = temp->next;
        else             caboose = NULL;
    }
    
    /* If we found a matching client with the given child */
    if(temp != NULL){
        /* Destroy the frame of the window (its parent) 
         * and free memory */
        printf("Before destroy subwindows!\n");
        XDestroySubwindows(d, temp->frame);
        
        printf("Before destroy frame!\n");
        XDestroyWindow(d, temp->frame);
        printf("After destroy frame!\n");
    
        /* reconnect the previous and after
         * WMclients in the list */

        if(temp != clientHead) head->next = caboose;
        else                   clientHead = caboose;

        free(temp);

    }
    /* We didn't find the child, send error */
    else{
        printf("deleteClient: Failed to find Client with sent child!\n");
    }
    
    return True;
}

/* test loading a pixmap */
//Window loadPixmap(const char *filename)
Pixmap loadPixmap(const char *filename)
{
    Pixmap p;
    Pixmap mask;
    XpmAttributes xpmattribs;
    
    //Window w;
    
    printf("Before create simple window!\n");
    
    /* create the window */
    /*w = XCreateSimpleWindow(
        d,
        RootWindow(d, DefaultScreen(d)),
        0,0, // x, y
        10,10, // w, h - can't be 0,0 or error
        0,   // border width,
        BlackPixel(d, DefaultScreen(d)),
        WhitePixel(d, DefaultScreen(d))
    );*/
    
    /* set pixmap attributes */
    xpmattribs.visual = DefaultVisual(d, DefaultScreen(d));
    xpmattribs.depth = DefaultDepth(d, DefaultScreen(d));
    xpmattribs.colormap = DefaultColormap(d, DefaultScreen(d));
    xpmattribs.valuemask = XpmDepth | XpmColormap | XpmVisual;
    
    printf("Before XpmReadFileToPixmap!\n");

    /* load the pixmap */
    if( XpmReadFileToPixmap(
            d,
            RootWindow(d, DefaultScreen(d)),
            filename,
            &p,
            &mask,
            &xpmattribs
        ) != XpmSuccess )
    {
        fprintf(stderr, "Failed to open pixmap %s\n", filename);
        //return (Window)0; // so you can test with if !Window
        return False;
    }
    
    printf("Before if mask free mask!\n");
    /* free the mask pixmap if not used */
    if(mask) {
        XFreePixmap(d, mask);
    }
    
    //printf("Before XSetWindowBackground!\n");
    
    /* draw the image to the window */
    //XSetWindowBackgroundPixmap(d, w, p);
    
    //printf("Before Resize Window!\n");
    
    /* resize the window to fit the image size */
    //XResizeWindow(d, w, xpmattribs.width, xpmattribs.height);
    
    //printf("Before XMapWindow!\n");
    
    /* make the window visible */
    //XMapWindow(d, w);
    
    /* debug test */
    //sleep(10);
    
    //XFreePixmap(d, p);
    //XDestroyWindow(d, w);
    //return (Window)0;
    //return Window;
    return p;
}

Bool reparentLoadPixmaps(const char *minimizePixmapName,
                         const char *maximizePixmapName,
                         const char *unmaxPixmapName,
                         const char *closePixmapName)
{
    /* TODO - error check */
    minPixmap   = loadPixmap(minimizePixmapName);
    maxPixmap   = loadPixmap(maximizePixmapName);
    unmaxPixmap = loadPixmap(unmaxPixmapName);
    closePixmap = loadPixmap(closePixmapName);
    
    return True;
}

void reparentClosePixmaps(void)
{
    if(minPixmap) XFreePixmap(d, minPixmap);
    if(maxPixmap) XFreePixmap(d, maxPixmap);
    if(unmaxPixmap) XFreePixmap(d, unmaxPixmap);
    if(closePixmap) XFreePixmap(d, closePixmap);
}

Window make_task_window(int x_pos)
{
  Window send;
  XWindowAttributes   get_task_attrbs;
  XGetWindowAttributes(d, task_bar, &get_task_attrbs);
  unsigned task_win_h = ((get_task_attrbs.height*3)/4);
  printf("\nHeight of taskbar %u\n", task_win_h);
  send = XCreateSimpleWindow(d, task_bar, x_pos, ((get_task_attrbs.height)/4), 20, task_win_h, 0, 0, 0xf46e42);
  XWindowAttributes   pass_attributes;
  XGetWindowAttributes(d, send, &pass_attributes);
  GC gc_taskbar_win = XCreateGC(d, send, 0,0);
  XDrawString(d, send, gc_taskbar_win, 0, 0, "Win 1", strlen("Win 1"));
  XMapWindow(d, send);

  return send;
}
