// GDITest.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "GDITest.h"
#include "MainFrame.h"
#include "./wtl81/atlapp.h"

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{

    CMainFrame frame;
    frame.Create(NULL, CRect(0, 0, 500, 400), NULL, WS_OVERLAPPEDWINDOW|WS_VISIBLE);

    CMessageLoop msg_loop;
    msg_loop.Run();

	return 0;
}
