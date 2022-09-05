#pragma
#include "framework.h"
#include "ChildDialog2.h"

extern HINSTANCE hInst;

CONST CHAR  AppTitle[] = "WIN32 메인 윈도우 창 템플릿";
HWND        hWndModalless;

// 함수 정의
//-----------------------------------------------------------------------------
//       자식 다이얼로그2 메세지 처리
//-----------------------------------------------------------------------------
INT_PTR CALLBACK ChildDialog2_CmdProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return InitChildDialog2(hDlg, message, wParam, lParam);

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        else
        {
            WM_CmdProc_ChildDialog2(hDlg, message, wParam, lParam);
        }
        break;


    case WM_NOTIFY:
        WM_NotifyProc_ChildDialog2(hDlg, message, wParam, lParam);
        break;

    case WM_PAINT:          //화면을 그려야 할 이유가 생겼을 떄
    {
        PAINTSTRUCT ps;

        BeginPaint(hDlg, &ps);
        DrawAll(hDlg, ps.hdc);
        EndPaint(hDlg, &ps);
    }
        break;



    }
    return (INT_PTR)FALSE;
}

INT_PTR WINAPI InitChildDialog2(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    RECT rect_Client;
    GetClientRect(GetParent(hDlg), &rect_Client);
    MoveWindow(hDlg, 0, 50, rect_Client.right - rect_Client.left, rect_Client.bottom - rect_Client.top, TRUE);
    ShowWindow(hDlg, SW_HIDE);

    return TRUE;
}

//-----------------------------------------------------------------------------
//      자식 다이얼로그2 WM_COMMAND 메세지 처리
//-----------------------------------------------------------------------------
void WINAPI WM_CmdProc_ChildDialog2(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    int wprm = LOWORD(wParam);
    switch (wprm)
    {
    case ModalDialogCmdID:      //모달형 대화상자
        DialogBox(hInst, MAKEINTRESOURCE(TestDialogID), hDlg, ModalTestDlgProc);
        break;

    case ModallessDialogCmdID:  //모달리스형 대화상자
        if (hWndModalless != NULL) break;
        CreateDialog(hInst, MAKEINTRESOURCE(TestDialogID), hDlg, ModallessTestDlgProc);
        break;

    default:
        break;
    }
}


//-----------------------------------------------------------------------------
//      자식 다이얼로그2 WM_NOTIFY 메세지 처리
//-----------------------------------------------------------------------------
void WINAPI WM_NotifyProc_ChildDialog2(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

}





//-----------------------------------------------------------------------------
//      스크린 디버그 함수
//-----------------------------------------------------------------------------
VOID Printf_Child2(LPCSTR FormStr, ...)
{
    HDC  hDC;
    va_list VL;
    CHAR Buff[MAX_PATH];
#if SCREENDEBUG
    static int  DebugPosY = 0;
#endif

    va_start(VL, FormStr);
    wvnsprintf(Buff, sizeof(Buff), FormStr, VL);
    va_end(VL);

#if SCREENDEBUG
    hDC = GetDC(NULL);
    TextOut(hDC, 0, DebugPosY, Buff, lstrlen(Buff));
    ReleaseDC(NULL, hDC);
    if ((DebugPosY += 16) >= GetSystemMetrics(SM_CYSCREEN)) DebugPosY = 0;
#else
    OutputDebugString(Buff);
#endif
    //DebugFile("%s\r\n",Buff);
}




//-----------------------------------------------------------------------------
//              공백을 Skip함
//-----------------------------------------------------------------------------
LPCSTR WINAPI SkipSpace(LPCSTR lp)
{
    UCHAR Cha;

    for (;;)
    {
        Cha = *(BYTE*)lp;
        if (Cha == 0 || Cha > ' ') break;
        lp++;
    }
    return lp;
}




//-----------------------------------------------------------------------------
//      다음 단어의 위치를 줍니다 (공백이나 TAB기준)
//      현재단어와 공백을 지나 다음 단어의 위치를 줍니다
//      현재위치가 공백이면 바로 다음 나오는 단어
//      '나 "로 묶인경우 하나의 단어로 인식합니다
//-----------------------------------------------------------------------------
LPCSTR WINAPI NextWord(LPCSTR lp, int WordCnt)
{
    int Cha, FirstCha;

    for (;;)
    {
        lp = SkipSpace(lp);       //공백스킵
        FirstCha = lp[0];
        if (FirstCha == 0 || WordCnt == 0) break;
        WordCnt--;

        if (FirstCha == 0x27 || FirstCha == 0x22) lp++;     //"'", '"'
        else FirstCha = 0;

        for (;;)                        //단어스킵
        {
            Cha = *(BYTE*)lp++;
            if (Cha == 0) { lp--; break; }
            if (FirstCha != 0)
            {
                if (FirstCha == Cha) break;
            }
            else {
                if (Cha <= ' ') { lp--; break; }
            }
        }
    }
    return lp;
}




//-----------------------------------------------------------------------------
//      모든 화면 그리는 동작
//-----------------------------------------------------------------------------
VOID WINAPI DrawAll(HWND hWnd, HDC hDC)
{
    RECT R;
    static CONST CHAR DispText[] = "메인 윈도우 입니다.";

    GetClientRect(hWnd, &R);
    DrawText(hDC, DispText, lstrlen(DispText), &R, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}




//-----------------------------------------------------------------------------
//      모달 대화상자 처리
//-----------------------------------------------------------------------------
BOOL WINAPI ModalTestDlgProc(HWND hWnd, UINT Msg, WPARAM wPrm, LPARAM lPrm)
{
    switch (Msg)
    {
    case WM_INITDIALOG:
        return TRUE;

    case WM_COMMAND:
        switch (LOWORD(wPrm))
        {
        case IDOK:
            EndDialog(hWnd, IDCANCEL);
            break;
        case IDCANCEL:
            EndDialog(hWnd, IDCANCEL);
            break;
        }
    }
    return FALSE;
}




//-----------------------------------------------------------------------------
//      모달리스 대화상자 처리
//-----------------------------------------------------------------------------
BOOL WINAPI ModallessTestDlgProc(HWND hWnd, UINT Msg, WPARAM wPrm, LPARAM lPrm)
{
    switch (Msg)
    {
    case WM_INITDIALOG:
        hWndModalless = hWnd;
        ShowWindow(hWndModalless, SW_SHOW);
        return TRUE;

    case WM_COMMAND:
        switch (LOWORD(wPrm))
        {
        case IDOK:
            hWndModalless = NULL;
            DestroyWindow(hWnd);
            break;
        case IDCANCEL:
            hWndModalless = NULL;
            DestroyWindow(hWnd);
        }
    }
    return FALSE;
}


