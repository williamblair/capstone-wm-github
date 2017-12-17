/* Testing example manager rewrite in c */
#include <X11/Xlib.h>

#include <stdio.h>

#include "reparent.h"
#include "displayEvents.h"
#include "buttonEvents.h"
#include "configureEvents.h"
#include "destroyEvents.h"
#include "displayEvents.h"
#include "keyEvents.h"
#include "motionEvents.h"
#include "initCapstone.h"

#include "taskbar.h"

/***************************************/
/**         GLOBAL VARIABLES          **/
/***************************************/
Display *d; // connection to the X display
WMClient *clientHead; // the head of the WMClient linked list

//GC                  gc_taskbar;
//Window              task_bar; //X11 window for taskbar
//Window              task_win2;

/***************************************/
/**        FUNCTION PROTOTYPES        **/
/***************************************/
int errorHandler(Display *d, XErrorEvent *e);
Bool initX(void);
Bool reparentExistingWindows(void);
Bool mainLoop(void);

/* Taskbar prototypes */
//Window start_taskbar(Window pass);
//Window start_window(Window pass, Window task_bar, int x_pos, unsigned long color);

int main(int argc, char **argv)
{
    // parse the rc file
    if(argc != 2){
        printf("No rc file given! Using default location\n");
        if(!parseRC("files/capstoneInit.rc")){
            printf("Failed to load file!\n");
        }
        else{
            printf("Loaded file!\n");
        }
    }
    else{
        printf("Using argument file!\n");
        parseRC(argv[1]);
    }
    
    // init X
    if(!initX()) return -1;
    
    // load pixmaps for the window borders
    reparentLoadPixmaps("files/minimize.xpm",
                        "files/maximize.xpm",
                        "files/unmaximize.xpm",
                        "files/close.xpm");
                        
    // frame any programs running before the 
    // window manager started
    reparentExistingWindows();
    
    // defined in taskbar.c
    createTaskbar();
                        
    /* Create the task bar */
    /*task_bar = start_taskbar(task_bar);
    Window task_win = None;
    task_win = start_window(task_win, task_bar, 1, 0x4286f4);
    //Window task_win2 = start_window(task_win, task_bar, 50, 0x0abcde);
    task_win2 = start_window(task_win, task_bar, 50, 0x0abcde);
    XDrawString(d, task_win2, DefaultGC(d, DefaultScreen(d)), 0, 0, "Win 1", strlen("Win 1"));*/
    
    //Drawing a rectangle to the taskbar for testing purposes
    /*GC window_min = DefaultGC(d, DefaultScreen(d));
    XGCValues send_vals;
    send_vals.fill_rule=FillSolid;
    send_vals.foreground=1;
    XChangeGC(d, window_min, GCForeground, &send_vals);
    XFillRectangle(d, task_bar, window_min, 25, 5, 20, 20);
    XSelectInput(d, task_bar, 0);*/
    
    // check for and handle events
    mainLoop();
    
    reparentClosePixmaps();
    if(d) XCloseDisplay(d);
    return 0;
}

/***************************************/
/**        FUNCTION DEFINITIONS       **/
/***************************************/
int errorHandler(Display *d, XErrorEvent *e)
{
    
    if(e->error_code == BadAccess) {
        fprintf(stderr, "Another Window Manager Already Detected!\n");
        return -1;
    }
    
    return 0;
}

Bool initX(void)
{
    // open the display
    d = XOpenDisplay(NULL);
    if(!d){
        fprintf(stderr, "initX: Failed to open display!\n");
        return False;
    }
    
    // set error handler
    XSetErrorHandler(&errorHandler);
    
    // we want to be able to reparent windows
    XSelectInput(
        d,
        DefaultRootWindow(d),
        SubstructureRedirectMask | SubstructureNotifyMask | ButtonPressMask
    );
    
    // flushes outpu buffer, waits until all requests have
    // been received and processed
    XSync(d, False);
    
    return True;
}

Bool reparentExistingWindows(void)
{
    // Prevent windows from changing under us
    XGrabServer(d);
    
    // Get existing top level windows
    Window r, p, *children; // root, parent, children
    unsigned int numChildren;
    XQueryTree(
        d, 
        DefaultRootWindow(d),
        &r,
        &p,
        &children,
        &numChildren
    );
    
    // reframe each top level window
    unsigned int i;
    for(i=0; i<numChildren; i++)
    {
        reparentWindow(children[i], True);
    }
    
    // free allocated memory
    if(children) XFree(children);
    
    // finished chokeholding the server
    XUngrabServer(d);
    
    return True;
}

Bool mainLoop(void)
{
    XEvent e;
    
    while(True)
    {
        XNextEvent(d, &e);
        
        switch(e.type)
        {
            case CreateNotify:    hCreateNotify(e.xcreatewindow);   break;
            case DestroyNotify:   hDestroyNotify(e.xdestroywindow); break;
            case ReparentNotify:  hReparentNotify(e.xreparent);     break;
            case MapNotify:       hMapNotify(e.xmap);               break;
            case UnmapNotify:     hUnmapNotify(e.xunmap);           break;
            case ConfigureNotify: hConfigureNotify(e.xconfigure);   break;
            case MapRequest:      hMapRequest(e.xmaprequest);       break;
            case ConfigureRequest: hConfigureRequest(e.xconfigurerequest); break;
            case ButtonPress:      hButtonPress(e.xbutton);         break;
            case ButtonRelease:    hButtonRelease(e.xbutton);       break;
            case MotionNotify:     hMotionNotify(e.xmotion);        break;
            case KeyPress:         hKeyPress(e.xkey);               break;
            case KeyRelease:       hKeyRelease(e.xkey);             break;
            case Expose:           hExpose(e.xexpose);              break;
            
            default:
                printf("Unhandled Event: %d\n", e.type);
                break;
        }
    }
    
    return True;
}

/*Window start_taskbar(Window pass)
{
    pass=XCreateSimpleWindow(d, DefaultRootWindow(d),0,(HeightOfScreen(DefaultScreenOfDisplay(d))-25),(WidthOfScreen(DefaultScreenOfDisplay(d))),25, 0, BlackPixel(d,DefaultScreen(d)), WhitePixel(d, DefaultScreen(d)));
    XSelectInput(d, pass, ExposureMask|ButtonPressMask|KeyPressMask);
    gc_taskbar=XCreateGC(d, pass, 0,0);
    XSetBackground(d, gc_taskbar, WhitePixel(d, DefaultScreen(d)));
    XSetForeground(d, gc_taskbar, BlackPixel(d, DefaultScreen(d)));
    XClearWindow(d, pass);
    XMapRaised(d, pass);

    return pass;
}

Window start_window(Window pass, Window task_bar, int x_pos, unsigned long color)
{
    XWindowAttributes get_task_attrbs;
    XGetWindowAttributes(d, task_bar, &get_task_attrbs);
    unsigned task_win_h = ((get_task_attrbs.height*3)/4);
    printf("\nHeight of taskbar %u\n", task_win_h);
    pass = XCreateSimpleWindow(d, task_bar, x_pos, ((get_task_attrbs.height)/4), 40, task_win_h, 0, 0, color);
    XMapWindow(d, pass);

    return pass;
}
*/