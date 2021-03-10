/* Event header for application - AppBuilder 2.03  */

#if defined(__cplusplus)
extern "C" {
#endif

static const ApEventLink_t AbApplLinks[] = {
	{ 3, 0, 0L, 0L, 0L, &QNXChess, NULL, NULL, 0, NULL, 0, 0, 0, 0, },
	{ 0 }
	};

static const ApEventLink_t AbLinks_QNXChess[] = {
	{ 8, 0, 0L, 0L, 0L, NULL, NULL, "QNXChess", 18023, OnOpening_Window_Main, 0, 0, 0, 0, },
	{ 8, 0, 0L, 0L, 0L, NULL, NULL, "QNXChess", 18024, OnClosing_Window_Main, 0, 0, 0, 0, },
	{ 8, 0, 0L, 0L, 0L, NULL, NULL, "QNXChess", 2009, OnActivate_Redraw, 0, 0, 0, 0, },
	{ 8, 0, 0L, 0L, 0L, NULL, NULL, "QNXChess", 10003, OnActivate_Redraw, 0, 0, 0, 0, },
	{ 8, 0, 0L, 0L, 0L, NULL, NULL, "QNXChess", 2010, OnActivate_Redraw, 0, 0, 0, 0, },
	{ 8, 1, 0L, 0L, 2L, NULL, NULL, "QNXChess", 1011, OnActivate_Raw, 0, 0, 0, 0, },
	{ 8, 0, 0L, 0L, 0L, NULL, NULL, "QNXChess", 18021, OnActivate_Redraw, 0, 0, 0, 0, },
	{ 8, 0, 0L, 0L, 0L, NULL, NULL, "PtButton_Main_SaveState", 2009, OnActivate_Button_SaveState, 0, 0, 0, 0, },
	{ 8, 0, 0L, 0L, 0L, NULL, NULL, "PtButton_Main_RotateBoard", 2009, OnActivate_Button_RotateBoard, 0, 0, 0, 0, },
	{ 8, 0, 0L, 0L, 0L, NULL, NULL, "PtButton_Main_LoadState", 2009, OnActivate_Button_LoadState, 0, 0, 0, 0, },
	{ 8, 0, 0L, 0L, 0L, NULL, NULL, "PtButton_Main_Move", 2009, OnActivate_Button_Move, 0, 0, 0, 0, },
	{ 8, 0, 0L, 0L, 0L, NULL, NULL, "PtButton_Main_InitWhite", 2009, OnActivate_Button_InitWhite, 0, 0, 0, 0, },
	{ 8, 0, 0L, 0L, 0L, NULL, NULL, "PtButton_Main_InitBlack", 2009, OnActivate_Button_InitBlack, 0, 0, 0, 0, },
	{ 0 }
	};

const char ApOptions[] = AB_OPTIONS;

#if defined(__cplusplus)
}
#endif

