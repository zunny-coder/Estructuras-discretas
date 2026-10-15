#include <windows.h>
#include <commctrl.h>
#include <stdio.h>
#include "resource.h"
HINSTANCE hInst;
HRGN figura;
void F(HDC hdc,int x,int y,int a)
{   HRGN c=CreateRectRgn(x-a,y-a,x+a,y+a);
    CombineRgn(figura,figura,c,RGN_OR);
    DeleteObject(c);

    RECT r;
    GetClipBox(hdc,&r);
    FillRect(hdc,&r,(HBRUSH)GetStockObject(WHITE_BRUSH));
    FrameRgn(hdc,figura,(HBRUSH)GetStockObject(BLACK_BRUSH),1,1);

    Sleep(40);

    if(a>10)
    {
        F(hdc,x-a,y-a,a/2);
        F(hdc,x-a,y+a,a/2);
        F(hdc,x+a,y-a,a/2);
        F(hdc,x+a,y+a,a/2);
    }
}

BOOL CALLBACK DlgMain(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
        case WM_PAINT:
        {
            HDC hdc;
            PAINTSTRUCT ps;
            hdc=BeginPaint(hwndDlg,&ps);
            figura=CreateRectRgn(0,0,0,0);
            F(hdc,200,200,100);
            DeleteObject(figura);
            EndPaint(hwndDlg,&ps);
        }
        return TRUE;
        case WM_INITDIALOG:
        {
        }
        return TRUE;
        case WM_CLOSE:
        {   EndDialog(hwndDlg,0);
        }
        return TRUE;
        case WM_COMMAND:
        {   switch(LOWORD(wParam))
            {
            }
        }
        return TRUE;
    }
    return FALSE;
}
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                     LPSTR lpCmdLine, int nShowCmd)
{
    hInst=hInstance;
    InitCommonControls();
    return DialogBox(hInst,MAKEINTRESOURCE(DLG_MAIN),
                     NULL,(DLGPROC)DlgMain);
}
