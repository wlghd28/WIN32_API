#pragma
#include "framework.h"
#include "ChildDialog3.h"

#define WMCMDID LOWORD(wPrm)


#define NAMEMAX     16      //�ֹε�ϻ� �ִ� �ѱ� ���̴� 6��
#define GROUPMAX    16      //�з��� �ִ� ����
#define TELNOMAX    20      //082)010-1111-2222

CONST CHAR AppTitle[] = "Win32Api_Dialog_Child3";
extern HINSTANCE hInst;
HBRUSH hBrBtnBG_Child3;



// �Լ� ����
//-----------------------------------------------------------------------------
//       �ڽ� ���̾�α�2 �޼��� ó��
//-----------------------------------------------------------------------------
INT_PTR CALLBACK ChildDialog3_CmdProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return InitChildDialog3(hDlg, message, wParam, lParam);

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        else
        {
            WM_CmdProc_ChildDialog3(hDlg, message, wParam, lParam);
        }
        break;


    case WM_NOTIFY:
        WM_NotifyProc_ChildDialog3(hDlg, message, wParam, lParam);
        break;


    case WM_DESTROY:
        DeleteObject(hBrBtnBG_Child3);
        break;
    case WM_DRAWITEM:

        if (LOWORD(wParam) == IDC_BUTTON_CHILD3_ADD)
        {
            DrawOwnerButton_Child3((DRAWITEMSTRUCT*)lParam, CheckBtmID);
            return TRUE;
        }

        if (LOWORD(wParam) == IDC_BUTTON_CHILD3_CANCEL)
        {
            DrawOwnerButton_Child3((DRAWITEMSTRUCT*)lParam, CancelBtmID);
            return TRUE;
        }

        break;


    }
    return (INT_PTR)FALSE;
}

INT_PTR WINAPI InitChildDialog3(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    RECT rect_Client;
    GetClientRect(GetParent(hDlg), &rect_Client);
    MoveWindow(hDlg, 0, 20, rect_Client.right - rect_Client.left, rect_Client.bottom - rect_Client.top, TRUE);
    ShowWindow(hDlg, SW_HIDE);


    SendDlgItemMessage(hDlg, IDC_LIST_CHILD3_VIEWER, LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT);
    LV_InsertColumn_Child3(hDlg, IDC_LIST_CHILD3_VIEWER, 0, 70, "�̸�", 0);
    LV_InsertColumn_Child3(hDlg, IDC_LIST_CHILD3_VIEWER, 1, 40, "����", 0);
    LV_InsertColumn_Child3(hDlg, IDC_LIST_CHILD3_VIEWER, 2, 80, "��ȭ��ȣ", 0);
    LV_InsertColumn_Child3(hDlg, IDC_LIST_CHILD3_VIEWER, 3, 40, "�߿�", 0);
    LV_InsertColumn_Child3(hDlg, IDC_LIST_CHILD3_VIEWER, 4, 60, "�з�", 0);

    CB_AddString_Child3(hDlg, IDC_COMBO_CHILD3_GROUP, "����");
    CB_AddString_Child3(hDlg, IDC_COMBO_CHILD3_GROUP, "ģ��");
    CB_AddString_Child3(hDlg, IDC_COMBO_CHILD3_GROUP, "���Ƹ�");
    CB_AddString_Child3(hDlg, IDC_COMBO_CHILD3_GROUP, "��Ÿ");

    hBrBtnBG_Child3 = CreateSolidBrush(RGB(192, 192, 192));



    return TRUE;
}

//-----------------------------------------------------------------------------
//      �ڽ� ���̾�α�2 WM_COMMAND �޼��� ó��
//-----------------------------------------------------------------------------
void WINAPI WM_CmdProc_ChildDialog3(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    int wprm = LOWORD(wParam);

    int  I, Row, Sex, Importent;
    CHAR Name[NAMEMAX];
    CHAR Group[GROUPMAX];
    CHAR TelNo[TELNOMAX];
    CHAR Buff[128];

    switch (wprm)
    {
    case IDC_BUTTON_CHILD3_ADD:      //�߰���ư
        GetDlgItemText(hDlg, IDC_EDIT_CHILD3_NAME, Name, sizeof(Name));
        if (Name[0] == 0)
        {
            MessageBox(hDlg, "�̸��� �Է��ϼ���.", AppTitle, MB_OK);
            SetFocus(GetDlgItem(hDlg, IDC_EDIT_CHILD3_NAME));
            break;
        }

        if (CheckDuplicateName_Child3(hDlg, Name))
        {
            MessageBox(hDlg, "�̹� ���� �̸��� �ֽ��ϴ�.", AppTitle, MB_OK);
            SetFocus(GetDlgItem(hDlg, IDC_EDIT_CHILD3_NAME));
            break;
        }

        GetDlgItemText(hDlg, IDC_EDIT_CHILD3_PHONENUMBER, TelNo, sizeof(TelNo));
        if (TelNo[0] == 0)
        {
            MessageBox(hDlg, "��ȭ��ȣ�� �Է��ϼ���.", AppTitle, MB_OK);
            SetFocus(GetDlgItem(hDlg, IDC_EDIT_CHILD3_PHONENUMBER));
            break;
        }

        GetDlgItemText(hDlg, IDC_COMBO_CHILD3_GROUP, Group, sizeof(Group));
        if (Group[0] == 0)
        {
            MessageBox(hDlg, "�з��� �����ϼ���.", AppTitle, MB_OK);
            SetFocus(GetDlgItem(hDlg, IDC_COMBO_CHILD3_GROUP));
            break;
        }

        Sex = IsDlgButtonChecked(hDlg, IDC_RADIO_CHILD3_SEX);
        Importent = IsDlgButtonChecked(hDlg, IDC_CHECK_CHILD3_IMPORTANT);

        wnsprintf(Buff, sizeof(Buff), "%s %s %s %s %s", Group, Name, TelNo,
            Sex != 0 ? "��" : "��", Importent != 0 ? "�߿�" : "");

        //LB_AddString(hWnd, PhoneBookViewerLBID, Buff);
        Row = LV_GetItemCount_Child3(hDlg, IDC_LIST_CHILD3_VIEWER);
        LV_InsertItem_Child3(hDlg, IDC_LIST_CHILD3_VIEWER, Row, Name, 0);
        LV_SetItemText_Child3(hDlg, IDC_LIST_CHILD3_VIEWER, Row, 1, Sex != 0 ? "��" : "��");
        LV_SetItemText_Child3(hDlg, IDC_LIST_CHILD3_VIEWER, Row, 2, TelNo);
        LV_SetItemText_Child3(hDlg, IDC_LIST_CHILD3_VIEWER, Row, 3, Importent != 0 ? "��" : "");
        LV_SetItemText_Child3(hDlg, IDC_LIST_CHILD3_VIEWER, Row, 4, Group);

        break;

    case IDC_BUTTON_CHILD3_DELETE:   //������ư
        if ((I = LV_GetSelected_Child3(hDlg, IDC_LIST_CHILD3_VIEWER, -1)) < 0)
        {
            MessageBox(hDlg, "������ �׸��� �����ϼ���.", AppTitle, MB_OK);
            break;
        }
        LV_DeleteItem_Child3(hDlg, IDC_LIST_CHILD3_VIEWER, I);
        break;

    case IDC_BUTTON_CHILD3_CANCEL:          //�ݱ�
        EndDialog(hDlg, 0);

    default:
        break;
    }
}


//-----------------------------------------------------------------------------
//      �ڽ� ���̾�α�2 WM_NOTIFY �޼��� ó��
//-----------------------------------------------------------------------------
void WINAPI WM_NotifyProc_ChildDialog3(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

}





//-----------------------------------------------------------------------------
//      ��ũ�� ����� �Լ�
//-----------------------------------------------------------------------------
VOID Printf_Child3(LPCSTR FormStr, ...)
{
    HDC  hDC;
    char szTmp[MAX_PATH];
    static int  DebugPosY = 0;

    hDC = GetDC(NULL);
    wvsprintf(szTmp, FormStr, (LPSTR)(&FormStr + 1));
    //VsprintfN(szTmp, sizeof(szTmp), FormStr, &FormStr+1);
    TextOut(hDC, 0, DebugPosY, szTmp, lstrlen(szTmp));
    ReleaseDC(NULL, hDC);

    //DebugFile("%s\r\n",szTmp);
    //OutputDebugString(szTmp);

    DebugPosY += 16;
    if (DebugPosY >= GetSystemMetrics(SM_CYSCREEN)) DebugPosY = 0;
}



//-----------------------------------------------------------------------------
//      �̸��� �ߺ��Ǹ� TRUE�� ������
//-----------------------------------------------------------------------------
BOOL WINAPI CheckDuplicateName_Child3(HWND hWnd, LPCSTR ToFileStr)
{
    return FALSE;
}




//-----------------------------------------------------------------------------
//      ListView�� �ķ��߰�
//      Align= LVCFMT_LEFT/LVCFMT_CENTER/LVCFMT_RIGHT
//-----------------------------------------------------------------------------
VOID WINAPI LV_InsertColumn_Child3(HWND hWnd, int LVID, int Column, int Width, LPCSTR ColumnName, int Align)
{
    LV_COLUMN  LVC;

    LVC.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
    LVC.fmt = Align;
    LVC.cx = Width;
    LVC.pszText = (LPSTR)ColumnName;
    SendDlgItemMessage(hWnd, LVID, LVM_INSERTCOLUMN, Column, (LPARAM)&LVC);
}



//-----------------------------------------------------------------------------
//      ListView���� ���� �߰�
//-----------------------------------------------------------------------------
int WINAPI LV_InsertItem_Child3(HWND hWnd, int LVID, int Row, LPCSTR DataStr, LPARAM ItemData)
{
    LV_ITEM LVI;

    ZeroMemory(&LVI, sizeof(LV_ITEM));
    LVI.mask = LVIF_TEXT | LVIF_PARAM;
    LVI.iSubItem = 0;            //�� �ָ� ���� ����
    LVI.iItem = Row;
    LVI.lParam = ItemData;     //������ �� ��
    LVI.pszText = (LPSTR)DataStr;
    return (int)SendDlgItemMessage(hWnd, LVID, LVM_INSERTITEM, 0, (LPARAM)&LVI);
}



//-----------------------------------------------------------------------------
//      ListView�� Item���� ����
//-----------------------------------------------------------------------------
int WINAPI LV_GetItemCount_Child3(HWND hWnd, int LVID)
{
    return SendDlgItemMessage(hWnd, LVID, LVM_GETITEMCOUNT, 0, 0);
}



//-----------------------------------------------------------------------------
//      ListView Item Text����
//-----------------------------------------------------------------------------
VOID WINAPI LV_SetItemText_Child3(HWND hWnd, int LVID, int Row, int Column, LPCSTR DataStr)
{
    LV_ITEM LVI;

    ZeroMemory(&LVI, sizeof(LV_ITEM));
    LVI.mask = LVIF_TEXT;
    LVI.iSubItem = Column;
    LVI.pszText = (LPSTR)DataStr;
    SendDlgItemMessage(hWnd, LVID, LVM_SETITEMTEXT, Row, (LPARAM)&LVI);
}



//-----------------------------------------------------------------------------
//      ListView�� ���õ� Item��ȣ�� ���� (�����ΰ�� -1)
//-----------------------------------------------------------------------------
int WINAPI LV_GetSelected_Child3(HWND hWnd, int LVID, int StartItemNo)
{
    return (int)SendDlgItemMessage(hWnd, LVID, LVM_GETNEXTITEM, StartItemNo, LVNI_SELECTED);
}



//-----------------------------------------------------------------------------
//      ListView�� �־��� Item�� ������
//-----------------------------------------------------------------------------
BOOL WINAPI LV_DeleteItem_Child3(HWND hWnd, int LVID, int DelItemNo)
{
    return (BOOL)SendDlgItemMessage(hWnd, LVID, LVM_DELETEITEM, DelItemNo, 0);
}



//-----------------------------------------------------------------------------
//      �޺��ڽ��� �׸� �߰�
//-----------------------------------------------------------------------------
int WINAPI CB_AddString_Child3(HWND hWnd, int CBID, LPCSTR ToAddStr)
{
    return SendDlgItemMessage(hWnd, CBID, CB_ADDSTRING, 0, (LPARAM)ToAddStr);
}



//-----------------------------------------------------------------------------
//       hBitmap�� �׸�
//-----------------------------------------------------------------------------
VOID WINAPI DrawBitmap_Child3(HDC hDC, int DestX, int DestY, int Width, int Height,
    HBITMAP hBtm, int SrcX, int SrcY, int CopyMode)
{
    HDC hMemDC;

    hMemDC = CreateCompatibleDC(hDC);
    SelectObject(hMemDC, hBtm);
    BitBlt(hDC, DestX, DestY, Width, Height, hMemDC, SrcX, SrcY, CopyMode);
    DeleteDC(hMemDC);
}



//-----------------------------------------------------------------------------
//      �������� �����ʾƷ��� �ٸ������� �簢���� �׸��ϴ�
//-----------------------------------------------------------------------------
VOID WINAPI DrawTwoColorRect_Child3(HDC hDC, RECT* R, COLORREF Col1, COLORREF Col2)
{
    HPEN hPenOld;

    hPenOld = (HPEN)SelectObject(hDC, CreatePen(PS_SOLID, 1, Col1));
    MoveToEx(hDC, R->left, R->top, NULL); LineTo(hDC, R->right, R->top);
    MoveToEx(hDC, R->left, R->top, NULL); LineTo(hDC, R->left, R->bottom);
    DeleteObject(SelectObject(hDC, hPenOld));

    hPenOld = (HPEN)SelectObject(hDC, CreatePen(PS_SOLID, 1, Col2));
    MoveToEx(hDC, R->right, R->top, NULL); LineTo(hDC, R->right, R->bottom);
    MoveToEx(hDC, R->left, R->bottom, NULL); LineTo(hDC, R->right + 1, R->bottom);
    DeleteObject(SelectObject(hDC, hPenOld));
}



//-----------------------------------------------------------------------------
//      ���ʵ�� ��ư�� �׸��ϴ�
//-----------------------------------------------------------------------------
VOID WINAPI DrawOwnerButton_Child3(DRAWITEMSTRUCT* DIS, int BtmID)
{
    RECT    R;
    BITMAP  BI;
    HBITMAP hBtm;
    CHAR    Buff[20];

    R = DIS->rcItem;

    FillRect(DIS->hDC, &DIS->rcItem, hBrBtnBG_Child3);     //������ �׸�

    //�׵θ��� �׸�
    DrawTwoColorRect_Child3(DIS->hDC, &R, (DIS->itemState & ODS_SELECTED) ? RGB(105, 105, 105) : RGB(255, 255, 255), RGB(105, 105, 105));
    InflateRect(&R, -1, -1);
    DrawTwoColorRect_Child3(DIS->hDC, &R, RGB(227, 227, 227), RGB(160, 160, 160));
    InflateRect(&R, -1, -1);


    if ((hBtm = LoadBitmap(hInst, MAKEINTRESOURCE(BtmID))) != NULL)
    {
        GetObject(hBtm, sizeof(BITMAP), &BI);

        if (DIS->itemState & ODS_SELECTED) OffsetRect(&R, 1, 1);    //�������ǥ��

        DrawBitmap_Child3(DIS->hDC, R.left + 5, R.top + ((R.bottom - R.top - BI.bmHeight) >> 1),
            BI.bmWidth, BI.bmHeight,
            hBtm, 0, 0, SRCCOPY);

        //��ư�� Ÿ��Ʋ�� ǥ����
        GetWindowText(DIS->hwndItem, Buff, sizeof(Buff));
        R.left += 5 + BI.bmWidth;
        //SetBkColor(DIS->hDC, RGB(192,192,192));
        SetBkMode(DIS->hDC, TRANSPARENT);
        DrawText(DIS->hDC, Buff, -1, &R, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

        DeleteObject(hBtm);
    }
}

