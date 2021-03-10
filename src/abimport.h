/* Import (extern) header for application - AppBuilder 2.03  */

#if defined(__cplusplus)
extern "C" {
#endif

#include "abdefine.h"

extern ApWindowLink_t QNXChess;
extern ApWidget_t AbWidgets[ 11 ];


#if defined(__cplusplus)
}
#endif


#ifdef __cplusplus
int OnOpening_Window_Main( PtWidget_t *widget, ApInfo_t *data, PtCallbackInfo_t *cbinfo );
int OnClosing_Window_Main( PtWidget_t *widget, ApInfo_t *data, PtCallbackInfo_t *cbinfo );
int OnActivate_Redraw( PtWidget_t *widget, ApInfo_t *data, PtCallbackInfo_t *cbinfo );
int OnActivate_Raw( PtWidget_t *widget, ApInfo_t *data, PtCallbackInfo_t *cbinfo );
int OnActivate_Button_Move( PtWidget_t *widget, ApInfo_t *data, PtCallbackInfo_t *cbinfo );
int OnActivate_Button_InitWhite( PtWidget_t *widget, ApInfo_t *data, PtCallbackInfo_t *cbinfo );
int OnActivate_Button_InitBlack( PtWidget_t *widget, ApInfo_t *data, PtCallbackInfo_t *cbinfo );
int OnActivate_Button_LoadState( PtWidget_t *widget, ApInfo_t *data, PtCallbackInfo_t *cbinfo );
int OnActivate_Button_SaveState( PtWidget_t *widget, ApInfo_t *data, PtCallbackInfo_t *cbinfo );
int OnActivate_Button_RotateBoard( PtWidget_t *widget, ApInfo_t *data, PtCallbackInfo_t *cbinfo );
#endif
