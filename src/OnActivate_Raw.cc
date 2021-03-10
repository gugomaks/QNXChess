/* Y o u r   D e s c r i p t i o n                       */
/*                            AppBuilder Photon Code Lib */
/*                                         Version 2.03  */

/* Standard headers */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/* Local headers */
#include "ablibs.h"
#include "abimport.h"
#include "proto.h"
#include "cmain.h"

extern CMain cMain;

int OnActivate_Raw( PtWidget_t *widget, ApInfo_t *apinfo, PtCallbackInfo_t *cbinfo )
{
 //получаем положение мышки	
 PhCursorInfo_t cursor_info; 	
 PhQueryCursor(0,&cursor_info);	 
 //пересчитываем его к окну
 short x,y;
 PtGetAbsPosition(ABW_QNXChess,&x,&y);
 long mouse_x=cursor_info.pos.x-x; 
 long mouse_y=cursor_info.pos.y-y; 
 if (cursor_info.button_state==Ph_BUTTON_SELECT) cMain.OnActivate_MouseButtonLeft(mouse_x,mouse_y);
 if (cursor_info.button_state==Ph_BUTTON_MENU) cMain.OnActivate_MouseButtonRight(mouse_x,mouse_y);
 return(Pt_CONTINUE);
}