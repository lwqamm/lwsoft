#pragma once
#ifndef __REQUIRED_RPCNDR1_H_VERSION__ABD
#define __REQUIRED_RPCNDR1_H_VERSION__ABD 500

//·ÃÎÊ¿ØÖÆ
class TsMutex//´´½¨ÁÙ½çÇøºÍÏú»ÙÁÙ½çÇø
{
public:
	typedef void* HANDLE;
	TsMutex(char* pszEventName);
	~TsMutex();
	//CRITICAL_SECTION m_mutex;
	HANDLE hEvent;
	void lock();
	void unlock();

};


class LwMutexlock
{
public:
	LwMutexlock(TsMutex* ptcmutex);
	~LwMutexlock();
	TsMutex* m_ptcmutex;
};

#define LW_BINDEVEN				  "LW_BIND_EVEN"
#define LW_UNBINDEVEN			  "LW_UNBIND_EVEN"
#define LW_KEYDOWNEVEN			  "LW_KEYDOWN_EVEN"
#define LW_KEYUPEVEN			  "LW_KEYUP_EVEN"//	
#define LW_KEYPRESSEVEN			  "LW_KEYPRESS_EVEN"
#define LW_KEYPRESSSTREVEN		  "LW_KEYPRESSSTR_EVEN"
#define LW_KEYPRESSCHAREVEN		  "LW_KEYPRESSCHAR_EVEN"

#define LW_LEFTDOWNEVEN			  "LW_LEFTDOWN_EVEN"
#define LW_LEFTUPEVEN			  "LW_LEFTUP_EVEN"
#define LW_LEFTCLICKEVEN		  "LW_LEFTCLICK_EVEN"
#define LW_MOVETOEVEN			  "LW_MOVETO_EVEN"
#define LW_FINDPICEVEN			  "LW_FINDPIC_EVEN"
#define LW_RIGHTCLICKEVEN		  "LW_RIGHTCLICK_EVEN"
#define LW_RIGHTDOWNEVEN		  "LW_RIGHTDOWN_EVEN"
#define LW_RIGHTUPEVEN			  "LW_RIGHTUP_EVEN"
#define LW_FINDCOLOREVEN		  "LW_FINDCOLOR_EVEN"
#define LW_GETCOLOREVEN			  "LW_GETCOLOR_EVEN"
#define LW_GETCURSORSHAPEEVEN	  "LW_GETCURSORSHAPE_EVEN"
#define LW_SETPATHEVEN			  "LW_SETPATH_EVEN"
#define LW_GETCURSORPOSEVEN		  "LW_GETCURSORPOS_EVEN"
#define LW_MOVEREVEN			  "LW_MOVER_EVEN"
#define LW_MIDDLECLICKEVEN		  "LW_MIDDLECLICK_EVEN"
#define LW_WHEELDOWNEVEN		  "LW_WHEELDOWN_EVEN"
#define LW_WHEELUPEVEN			  "LW_WHEELUP_EVEN"  
#define LW_CAPTUREEVEN			  "LW_CAPTUREE_EVEN" 
#define LW_LOCKINPUTEVEN		  "LW_LOCKINPUT_EVEN"
#define LW_OCREVEN				  "LW_OCR_EVEN"
#define LW_SETDICTEVEN			  "LW_SETDICT_EVEN"
#define LW_USEDICTEVEN			  "LW_USEDICT_EVEN"
#define LW_CLEARDICTEVEN		  "LW_CLEARDICT_EVEN"
#define LW_FINDSTREVEN			  "LW_FINDSTR_EVEN"
#define LW_GETNOWDICTEVEN		  "LW_GETNOWDICT_EVEN"
#define LW_CAPTUREGIFEVEN		   "LW_LW_CAPTUREGIF_EVEN"
#define LW_ENUMWINDOWEVEN		   "LW_ENUMWINDOW_EVEN"
#define LW_ENUMWINDOWBYPROCESSEVEN "LW_ENUMWINDOWBYPROCESS_EVEN"
#define LW_ENUMWINDOWBYPROCESSEVENID "LW_ENUMWINDOWBYPROCESS_EVENID"
#define LW_ENUMPROCESSEVEN	    "LW_ENUMPROCESS_EVEN"
#define LW_FINDDATAEVEN			"LW_FINDDATA_EVEN"
#define LW_FINDDOUBLEEVEN	    "LW_FINDDOUBL_EVEN"
#define LW_FINDFLOATEVEN	    "LW_FINDFLOAT_EVEN"
#define LW_FINDINTEVEN			"LW_FINDINT_EVEN"
#define LW_FINDSTRINGEVEN	    "LW_FINDSTRING_EVEN"
#define LW_MYSLEEPEVEN			"LW_MYSLEEP_EVEN"
#define LW_MYGETSCREENDATAEVEN	"LW_MYGETSCREENDATA_EVEN"
#define LW_MOVETOEXEVEN			"LW_MOVETOEX_EVEN"

#define LW_SENDSTRINGEVEN		  "LW_SENDSTRING_EVEN"
#define LW_SENDSTRING2EVEN		  "LW_SENDSTRING2_EVEN"
#define LW_SENDSTRINGIMEEVEN	  "LW_SENDSTRINGIME_EVEN"
//
////°ó¶¨»¥³â
//TsMutex gDXbindMutex(LW_BINDEVEN);
////½â°ó¶¨»¥³â
//TsMutex gDXUnbindMutex(LW_UNBINDEVEN);
////°´¼ü°´ÏÂ»¥³â
//TsMutex gDXKeyDownMutex(LW_KEYDOWNEVEN);
////°´¼üµ¯Æð»¥³â
//TsMutex gDXKeyUpMutex(LW_KEYUPEVEN);
////°´¼ü»¥³â
//TsMutex gDXKeyPressMutex(LW_KEYPRESSEVEN);
////KeyPressStr»¥³â
//TsMutex gDXKeyPressStrMutex(LW_KEYPRESSSTREVEN);
////KeyPressChar»¥³â
//TsMutex gDXKeyPressCharMutex(LW_KEYPRESSCHAREVEN);
////SendString»¥³â
//TsMutex gDXSendStringMutex(LW_SENDSTRINGEVEN);
////SendString»¥³â
//TsMutex gDXSendString2Mutex(LW_SENDSTRING2EVEN);
////SendStringIme»¥³â
//TsMutex gDXSendStringImeMutex(LW_SENDSTRINGIMEEVEN);
////LeftDown»¥³â		  
//TsMutex gDXLeftDownMutex(LW_LEFTDOWNEVEN);
////LeftUp»¥³â		  
//TsMutex gDXLeftUpMutex(LW_LEFTUPEVEN);
////LeftClick»¥³â		  
//TsMutex gDXLeftClickMutex(LW_MOVETOEVEN);
////MoveTo»¥³â		  
//TsMutex gDXMoveToMutex(LW_LEFTCLICKEVEN);
////FindPic»¥³â		  
//TsMutex gDXFindPicMutex(LW_FINDPICEVEN);
//////RightClick»¥³â		  
//TsMutex gDXRightClickMutex(LW_RIGHTCLICKEVEN);
////RightDown»¥³â		  
//TsMutex gDXRightDownMutex(LW_RIGHTDOWNEVEN);
////RightUp»¥³â		  
//TsMutex gDXRightUpMutex(LW_RIGHTUPEVEN);
////FindColor»¥³â		  
//TsMutex gDXFindColorMutex(LW_FINDCOLOREVEN);
////GetColor»¥³â		  
//TsMutex gDXGetColorMutex(LW_GETCOLOREVEN);
////GetCursorShape»¥³â		  
//TsMutex gDXGetCursorShapeMutex(LW_GETCURSORSHAPEEVEN);
////SetPath»¥³â		  
//TsMutex gDXSetPathMutex(LW_SETPATHEVEN);
////GetCursorPos»¥³â		  
//TsMutex gDXGetCursorPosMutex(LW_GETCURSORPOSEVEN);
////MoveR»¥³â		  
//TsMutex gDXMoveRMutex(LW_MOVEREVEN);
////MiddleClick»¥³â		  
//TsMutex gDXMiddleClickMutex(LW_MIDDLECLICKEVEN);
////WheelDown»¥³â						
//TsMutex gDXWheelDownMutex(LW_WHEELDOWNEVEN);
////WheelUp»¥³â						
//TsMutex gDXWheelUpMutex(LW_WHEELUPEVEN);
////Capture»¥³â						
//TsMutex gDXCaptureMutex(LW_CAPTUREEVEN);
////LockInput»¥³â						
//TsMutex gDXLockInputMutex(LW_LOCKINPUTEVEN);
////Ocr»¥³â						
//TsMutex gDXOcrMutex(LW_OCREVEN);
////SetDict»¥³â						
//TsMutex gDXSetDictMutex(LW_SETDICTEVEN);
////UseDict»¥³â						
//TsMutex gDXUseDictMutex(LW_USEDICTEVEN);
////ClearDict»¥³â						
//TsMutex gDXClearDictMutex(LW_CLEARDICTEVEN);
////FindStr»¥³â						
//TsMutex gDXFindStrMutex(LW_FINDSTREVEN);
////GetNowDict»¥³â						
//TsMutex gDXGetNowDictMutex(LW_GETNOWDICTEVEN);
////CaptureGif»¥³â						
//TsMutex gDXCaptureGifMutex(LW_CAPTUREGIFEVEN);
////EnumWindow»¥³â						
//TsMutex gDXEnumWindowMutex(LW_ENUMWINDOWEVEN);
////EnumWindowByProcess»¥³â						
//TsMutex gDXEnumWindowByProcessMutex(LW_ENUMWINDOWBYPROCESSEVEN);
////EnumProcess»¥³â						
//TsMutex gDXEnumProcessMutex(LW_ENUMPROCESSEVEN);
////FindData
//TsMutex gDXFindDataMutex(LW_FINDDATAEVEN);
////FindDouble
//TsMutex gDXFindDoubleMutex(LW_FINDDOUBLEEVEN);
////FindFloat
//TsMutex gDXFindFloatMutex(LW_FINDFLOATEVEN);
////FindInt
//TsMutex gDXFindIntMutex(LW_FINDINTEVEN);
////FindString
//TsMutex gDXFindStringMutex(LW_FINDSTRINGEVEN);
//
//TsMutex gDXMySleepMutex(LW_MYSLEEPEVEN);
////GetScreenData
//TsMutex gDXMyGetScreenDataMutex(LW_MYGETSCREENDATAEVEN);
////MoveToEx
//TsMutex gDXMoveToExMutex(LW_MOVETOEXEVEN);
#endif