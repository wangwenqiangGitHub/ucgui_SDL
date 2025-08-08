#include "GUI.h"
 
int main(int argc, char *argv[])
{
    GUI_Init();
    GUI_SetColor(GUI_WHITE);
    GUI_DispString("Hello, world!");
    GUI_Delay(3000);
    return 0;
}
