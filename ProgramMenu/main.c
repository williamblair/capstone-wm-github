/* Program Menu Test */
#include <X11/Xlib.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

//#include "MenuEntry.h"

const int ENTRY_HEIGHT = 20; // height of one entry text in the window
const int ENTRY_OFFSET = 15; // how far from the top to start to draw the text

typedef struct MenuEntry {
    char displayString[50];
    char execString[50];
    struct MenuEntry *next;
} MenuEntry;

/* head of the list */
MenuEntry *menuHead;

/* The menu window */
Window menWindow;

/* X11 display */
Display *d;

/* Linked list of menu entries */
//MenuEntry *menuEntryHead = NULL;

XEvent e; // event structure

Bool initX(void); // open the x server
void createWindow(int x, int y); // initializes the menWindow

Bool addMenuEntry(const char *dispstring, const char *execstring);
Bool fillMenuList(const char *fname);
Bool freeMenuList(void);
void printMenuList(void);

Bool resizeWindow(void); // figure out how many menu entries there are and resize the window to fit them
Bool fillWindow(void); // reads the display entries from the list and adds them to the window
Bool drawSelectRect(const int mouseY); // draws the square around the current selection on the screen

Bool runMenuEntry(const int mouseY);

int main(int argc, char **argv)
{
    
    /* Make sure args were passed */
    if(argc != 4){
        printf("Usage: %s [x] [y] [menu_file]\n", argv[0]);
        return 0;
    }

    /* read from the menu file and fill the list */
    if( !fillMenuList(argv[3]) ) return -1;

    /* test print */
    printMenuList();
 
    /* Open the display */
    if(!initX()) return -1;
    
    /* initialize and start drawing the window */
    int x = 0, y = 0;
    sscanf(argv[1], "%d", &x);
    sscanf(argv[2], "%d", &y);
    printf("X: %d      Y: %d\n", x, y);
    createWindow(x, y);
    
    /* Read the number of entries in the menu list and resize accordingly */
    resizeWindow();
    
    while(1)
    {
        XNextEvent(d, &e);
        if(e.type == Expose) {
            /* draw something to the window */
            //XDrawRectangle(d, menWindow, DefaultGC(d, DefaultScreen(d)), 20, 20, 10, 10);
            fillWindow(); // draw all the menu entries
        }
        else if(e.type == MotionNotify) {
            printf("Pos: (%d,%d)\n", e.xbutton.x, e.xbutton.y);
            XClearWindow(d, menWindow);
            drawSelectRect(e.xbutton.y);
            fillWindow(); // draw all the menu entries
        }
        else if(e.type == ButtonPress) {
            if(runMenuEntry(e.xbutton.y)) break; // if returned true we ran a command so exit
        }
        else if(e.type == KeyPress) {
            break;
        }
    }
    
    /* Shut stuff down */
    freeMenuList();
    if(menWindow) XDestroyWindow(d, menWindow);
    if(d) XCloseDisplay(d);
    return 0;
}

Bool initX(void)
{
    /* open the connection to the server */
    d = XOpenDisplay(NULL); // open the default display
    if(!d){
        fprintf(stderr, "Failed to open display!\n");
        return False;
    }
    
    return True;
}

void createWindow(int x, int y)
{
    /* create the window */
    menWindow = XCreateSimpleWindow(
        d,
        RootWindow(d, DefaultScreen(d)),    // Display *parent
        x,                                // x coord
        y,                                // y coord
        100,           // window width
        100,              // window height
        1,                       // border size
        BlackPixel(d, DefaultScreen(d)),    // border
        WhitePixel(d, DefaultScreen(d))     // background
    );
    
    /* select input for the window */
    XSelectInput(d, menWindow, ExposureMask | KeyPressMask | ButtonPressMask | PointerMotionMask);

    /* We don't want this window to be rebordered */
    XSetWindowAttributes swa;
    swa.override_redirect = True;
    XChangeWindowAttributes(d, menWindow, CWOverrideRedirect, &swa);
     
}

Bool readMenuList(char *fname, MenuEntry *head)
{
    /* initialize the start of the list */
    //menuHead = (MenuEntry *)malloc(sizeof(MenuEntry));
    MenuEntry *m = head;

    FILE *fp = fopen(fname, "r");
    if(!fp){
        fprintf(stderr, "Failed to open '%s'\n", fname);
        return False;
    }

    char currentDisplay[50];
    char currentExec[50];
    while(fgets(currentDisplay, 50, fp) && fgets(currentExec, 50, fp))
    {
        m = (MenuEntry*)malloc(sizeof(MenuEntry));

        /* Todo - check for error */
        m->next = NULL;

        /* copy both strings into the struct */
        strcpy(m->displayString, currentDisplay);
        strcpy(m->execString, currentExec);

        m = m->next; // move toward the next string
    }
    
    if(fp) fclose(fp);
    return True;
}

Bool freeMenuList(void)
{
    MenuEntry *cursor, *temp;
    
    if(menuHead == NULL) return False;

    cursor = menuHead->next;
    menuHead->next = NULL;
    while(cursor != NULL)
    {
        temp = cursor->next;
        free(cursor);
        cursor = temp;
    }

    return True;
}

void printMenuList(void)
{
    MenuEntry *temp = menuHead;
    int entry_count = 0;
    while(temp != NULL)
    {
        printf("Entry %d: %s, %s\n", entry_count++, temp->displayString, temp->execString);
        temp = temp->next;
    }
}

Bool addMenuEntry(const char *dispstring, const char *execstring)
{
    MenuEntry *m; // the new entry

    /* allocate memory for the head or new string if necessary */
    if(menuHead == NULL) {
        menuHead = (MenuEntry*)malloc(sizeof(MenuEntry));
        m = menuHead;
    }
    else {
        MenuEntry *temp = menuHead;
        while(temp->next != NULL){
            temp = temp->next;
        }

        m = (MenuEntry*)malloc(sizeof(MenuEntry));
        temp->next = m;
    }

    m->next = NULL;

    /* copy the strings into the entry */
    strcpy(m->displayString, dispstring);
    strcpy(m->execString, execstring);

    return True;
}

Bool fillMenuList(const char *fname)
{
    /* open the menu file */
    FILE *fp = fopen(fname, "r");
    if(!fp){
        fprintf(stderr, "Failed to open '%s'\n", fname);
        return False;
    }

    /* holds the next 2 lines from the file */
    char displaystring[50];
    char execstring[50];
    while(fgets(displaystring, 50, fp) && fgets(execstring, 50, fp))
    {
        /* remove the newline feeds from the strings */
        strtok(displaystring, "\n");
        strtok(execstring, "\n");

        /* add them as a new entry in the list */
        addMenuEntry(displaystring, execstring);
    }

    if(fp) fclose(fp);

    return True;
}

Bool resizeWindow(void)
{
    MenuEntry *m = menuHead;
    int count = 0;
    while(m != NULL){
        count++;
        m = m->next;
    }
    XResizeWindow(
        d,
        menWindow,
        150,
        count * ENTRY_HEIGHT
    );

    /* Now that the window is of proper size draw it */
    XMapWindow(d, menWindow);

    return True;
}

Bool fillWindow(void)
{
    
    MenuEntry *m = menuHead;
    if(!m) {
        fprintf(stderr, "Null menuHead!\n");
        return False;
    }
    
    int current_y = ENTRY_OFFSET; // the y position to draw the next display text
    int num_entries = 0; // keep track of how many strings in the list
    while(m != NULL) 
    {
        XDrawString(
            d,  // Display *d
            menWindow, // Drawable d
            DefaultGC(d, DefaultScreen(d)), // GC gc
            5, // x pos
            current_y, // y pos
            m->displayString, // string to draw
            strlen(m->displayString) // string length
        );
        
        current_y += ENTRY_HEIGHT;
        num_entries++;
        
        m = m->next;
    }
    
    return True;
}

Bool drawSelectRect(const int mouseY)
{
    if(mouseY == 0) {
        printf("Mouse Position 0!\n");
        return False;
    }
    
    XWindowAttributes menWinAttribs;
    XGetWindowAttributes(d, menWindow, &menWinAttribs);
    
    int drawY=0;
    while(drawY < mouseY) drawY += ENTRY_HEIGHT; // move the height to the entry level first above the cursor y
    drawY -= ENTRY_HEIGHT; // we needed to move to the entry position 1 before the mouse position
    
    XDrawRectangle(d, menWindow, DefaultGC(d, DefaultScreen(d)), 0, drawY, menWinAttribs.width, ENTRY_HEIGHT);
    
    return True;
}

Bool runMenuEntry(const int mouseY)
{
    if(mouseY == 0) {
        printf("Click: mouse y == 0\n");
        return False;
    }
    
    MenuEntry *m = menuHead;
    
    /* figure out which entry to run */
    int position=0;
    int i=0;
    while(position < mouseY){ 
        position += ENTRY_HEIGHT; 
        i++;
    }
    i--; // since the while moved us to the next entry above move down 1
    
    int j=0;
    for(j=0; j<i; j++){
        m = m->next;
    }
    
    /* move the menu pointer i number of entries down */
    printf("Running: '%s'\n", m->execString);
    char command[60];
    strcpy(command, m->execString);
    strcat(command, " &"); // run the command in the background so we don't wait for it to finish
    system(command);
    return True;
}
