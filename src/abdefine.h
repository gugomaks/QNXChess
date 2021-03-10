/* Define header for application - AppBuilder 2.03  */

#if defined(__cplusplus)
extern "C" {
#endif

/* 'QNXChess' Window link */
extern const int ABN_QNXChess;
#define ABW_QNXChess                         AbGetABW( ABN_QNXChess )
extern const int ABN_PtList_Main_Log;
#define ABW_PtList_Main_Log                  AbGetABW( ABN_PtList_Main_Log )
extern const int ABN_PtList_Main_PrincipalMove;
#define ABW_PtList_Main_PrincipalMove        AbGetABW( ABN_PtList_Main_PrincipalMove )
extern const int ABN_PtButton_Main_SaveState;
#define ABW_PtButton_Main_SaveState          AbGetABW( ABN_PtButton_Main_SaveState )
extern const int ABN_PtButton_Main_RotateBoard;
#define ABW_PtButton_Main_RotateBoard        AbGetABW( ABN_PtButton_Main_RotateBoard )
extern const int ABN_PtButton_Main_LoadState;
#define ABW_PtButton_Main_LoadState          AbGetABW( ABN_PtButton_Main_LoadState )
extern const int ABN_PtButton_Main_Move;
#define ABW_PtButton_Main_Move               AbGetABW( ABN_PtButton_Main_Move )
extern const int ABN_PtText_Main_Move;
#define ABW_PtText_Main_Move                 AbGetABW( ABN_PtText_Main_Move )
extern const int ABN_PtComboBox_Main_ChangeType;
#define ABW_PtComboBox_Main_ChangeType       AbGetABW( ABN_PtComboBox_Main_ChangeType )
extern const int ABN_PtButton_Main_InitWhite;
#define ABW_PtButton_Main_InitWhite          AbGetABW( ABN_PtButton_Main_InitWhite )
extern const int ABN_PtButton_Main_InitBlack;
#define ABW_PtButton_Main_InitBlack          AbGetABW( ABN_PtButton_Main_InitBlack )

#define AbGetABW( n ) ( AbWidgets[ n ].wgt )

#define AB_OPTIONS "s:x:y:h:w:S:"

#if defined(__cplusplus)
}
#endif

