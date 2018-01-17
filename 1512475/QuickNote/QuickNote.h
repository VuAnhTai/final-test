#pragma once

#include "resource.h"

#include <WindowsX.h>

#include <Shellapi.h> //NOTIFYICONDATA
#include <Strsafe.h> //StringCchCopy()

#include <winuser.h>
#include <float.h>
#include <stdio.h>
#include <iostream>
#include <io.h>
#include <fcntl.h>
#include <windows.h>
//listview
#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#include <commctrl.h>
#pragma comment(lib, "Comctl32.lib")

//file UNICODE
#include <fstream>
#include <locale>	//wof, wif
#include <codecvt>

//GDI+
#include <objidl.h>
#include <gdiplus.h>
#pragma comment (lib,"Gdiplus.lib")

NOTIFYICONDATA nid;