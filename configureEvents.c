#include "configureEvents.h"
#include "reparent.h"

// variables from main.c
extern Display *d;
extern WMClient *clientHead;

Bool hConfigureNotify(const XConfigureEvent e)
{
    printf("Configure Notify Event!\n");
    
    return True;
}

Bool hConfigureRequest(const XConfigureRequestEvent e)
{
    printf("Configure Request Event!\n");
    
    XWindowChanges changes;
    changes.x = e.x;
    changes.y = e.y;
    changes.width = e.width;
    changes.height = e.height;
    changes.border_width = e.border_width;
    changes.sibling = e.above;
    changes.stack_mode = e.detail;
    
    // find the client
    WMClient *temp = clientHead;
    if(temp == NULL) printf("configureEvent: temp/clienthead null!\n");
    while(temp != NULL)
    {
        if(temp->child == e.window) break;
        temp = temp->next;
    }
    if(temp == NULL){
        printf("hConfigureRequest: failed to find client for the sent child window!\n");
        
        // change just the event window then
        XConfigureWindow(d, e.window, e.value_mask, &changes);
    }
    else {
        // otherwise change the client frame
        XConfigureWindow(d, temp->frame, e.value_mask, &changes);
    }
    
    
    return True;
}