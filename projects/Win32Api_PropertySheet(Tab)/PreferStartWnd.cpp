#include "framework.h"
#include "PreferStartWnd.h"


//-----------------------------------------------------------------------------
//      ��������ۼ��� ������Ƽ ������ ��ȭ���� Proc
//-----------------------------------------------------------------------------
DLGFNC(PreferStartWndDlgProc)
{
    int I;

    switch (Msg)
    {
    case WM_INITDIALOG:
        //���� ��ȭ���� ó���� ����
        return TRUE;

    case WM_NOTIFY:
        switch (((NMHDR*)lPrm)->code)
        {
        case PSN_SETACTIVE:     //�� Tab�� ���� ��
            PreferPropSheetPage = 2;
            break;

        case PSN_KILLACTIVE:    //�� TAB�� ���� ��
            I = FALSE;
            //�Է��� ���� ������ �ִ� ��� I=TRUE ����
            //SetWindowLong(hWnd, DWL_MSGRESULT, I);      //DWL_MSGRESULT�� TRUE�� �Է��ϸ� �� �������� ������ ����
            SetWindowLong(hWnd, DWLP_MSGRESULT, I);      //DWL_MSGRESULT�� TRUE�� �Է��ϸ� �� �������� ������ ����
            return TRUE;                                //TRUE�� �������� ������ ���� ���� �ص� �ҿ����

        case PSN_APPLY:         //Ȯ���� ������ ��
            //�Է��� ���� ������ ����
            MessageBox(hWnd, "2������", AppTitle, MB_OK);
            break;

        case PSN_RESET:         //���Ű�� ����
            MessageBox(hWnd, "2������", AppTitle, MB_OK);
            break;
        }
        break;

    case WM_COMMAND:
        //���� ��ȭ���� ó���� ����
        return TRUE;
    }

    return FALSE;
}
