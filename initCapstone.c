/* Stuff for reading the rc file */

#include "initCapstone.h"

/* Defined in reparent.c */
extern unsigned long titleBarColor;
extern unsigned long borderColor;
extern unsigned long titleFontColor;

/* defined in taskbar.c */
extern unsigned long taskbarFontColor;

/* Defined in main.c */
extern char          *menuFilePath;

Bool parseRC(const char *fname)
{
    FILE *fp = fopen(fname, "r");
    if(!fp)
    {
        fprintf(stderr, "parseRC: Failed to open %s\n", fname);
        return False;
    }

    /* what the current configuration is within the wm, like the menu file path */
    //char *currentSetting = (char *)malloc(sizeof(char) * 50); 
    char *currentSetting = NULL;
    char *currentLine = NULL;

    /* The value for the current entry */
    //char *currentEntry = (char *)malloc(sizeof(char) * 50);
    //char *currentEntry = NULL;

    //size_t entrySize=0; // stores the size allocated for the currentsetting line
    size_t lineSize=0;

    while(getline(&currentLine, &lineSize, fp) != -1)
    {
        if(currentLine[0] != '#' && currentLine[0] != '\n')
        {
            sscanf(currentLine, "%ms", &currentSetting);

            printf("currentSetting: %s\n", currentSetting);
            
            /* Program Menu file */
            if(strcmp(currentSetting, "menuFile:") == 0)
            {
                char *dummy = NULL; // holds the first part of the string
                //char *menuLoc = NULL;
                //sscanf(currentLine, "%ms %ms", &dummy, &menuLoc);
                sscanf(currentLine, "%ms %ms", &dummy, &menuFilePath);
                printf("MenuFile location: %s\n", menuFilePath);
                if(dummy) free(dummy);
                //if(menuLoc) free(menuLoc);
            }

            /* Frame Color */
            else if(strcmp(currentSetting, "titleBarColor:") == 0)
            {
                char *dummy = NULL;
                //unsigned long frameColor = 0;
                sscanf(currentLine, "%ms %lx", &dummy, &titleBarColor);
                printf("TitleBarColor Color: 0x%lX\n", titleBarColor);
                if(dummy) free(dummy);
            }
            
            /* Border color */
            else if(strcmp(currentSetting, "borderColor:") == 0)
            {
                char *dummy = NULL;
                sscanf(currentLine, "%ms %lx", &dummy, &borderColor);
                printf("borderColor Color: 0x%lX\n", borderColor);
            }
            
            /* title font color */
            else if(strcmp(currentSetting, "titleFontColor:") == 0)
            {
                char *dummy = NULL;
                sscanf(currentLine, "%ms %lx", &dummy, &titleFontColor);
                printf("Title font Color: 0x%lX\n", titleFontColor);
            }
            
            /* taskbar font color */
            else if(strcmp(currentSetting, "taskbarFontColor:") == 0)
            {
                char *dummy = NULL;
                sscanf(currentLine, "%ms %lx", &dummy, &taskbarFontColor);
                printf("Taskbar font Color: 0x%lX\n", taskbarFontColor);
            }
        }
    }

    if(currentLine) free(currentLine);
    if(currentSetting) free(currentSetting);
    //if(currentEntry) free(currentEntry);
    if(fp) fclose(fp);
    return True;
}

