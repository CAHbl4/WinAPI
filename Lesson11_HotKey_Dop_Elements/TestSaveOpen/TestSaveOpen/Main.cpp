#include <windows.h>
#include <tchar.h>
#include <fstream>
#include "resource.h"

using namespace std;

HMENU hMenu;
HWND hDialog,hEdit,hList;
HACCEL hAccelTable;
HHOOK hHook;

BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow)
{
	// ��������� ������� �������������.
    hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDR_ACCELERATOR1));
    DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
	// ���������� ������� �������������.
    DestroyAcceleratorTable(hAccelTable);
	return 0;

}

LRESULT CALLBACK GetMsgProc(int code, WPARAM wParam, LPARAM lParam)
{
    // ��������� �� ��������� "�����" � lParam.
    MSG *pMsg = (MSG *)lParam;

    if(pMsg->message >= WM_KEYFIRST && pMsg->message <= WM_KEYLAST)
    {
        // ����������� ������� ������ � WM_COMMAND.
        if(TranslateAccelerator(hDialog, hAccelTable, pMsg))
        {
            // ���� ��������� �������������, ���������� ���, ������������ ��� � WM_NULL.
            // ���� ����� �� �������, ��������� ������ � ������, � �� ���������� "�������".
           pMsg->message = WM_NULL;
        }
    }

    // �������� ��������� ������.
    return CallNextHookEx(hHook, code, wParam, lParam);
}

BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	
   switch (message)
   {
   case WM_INITDIALOG:
	   // ������������� ��������� ��� WH_GETMESSAGE �� ������� �����.
       hHook = SetWindowsHookEx(WH_GETMESSAGE, (HOOKPROC)GetMsgProc, NULL, GetCurrentThreadId());
	   hDialog=hWnd;
	   hMenu=LoadMenu(GetModuleHandle(NULL),MAKEINTRESOURCE(IDR_MENU1));
		SetMenu(hWnd,hMenu);
		hEdit = GetDlgItem(hWnd, IDC_EDIT1);
		hList = GetDlgItem(hWnd, IDC_LIST1);
		return TRUE;
   case WM_COMMAND:
	   switch(LOWORD(wParam))
		   {
	   case   ID_FILE_OPEN40001:
		   {
			   TCHAR FullPath[MAX_PATH] = {0};
      OPENFILENAME open = {sizeof(OPENFILENAME)};
      open.hwndOwner = hWnd;
	  open.lpstrFilter = TEXT("Text Files(*.txt)\0 * .txt\0All Files(*.*)\0 * .*\0");
      open.lpstrFile = FullPath;
      open.nMaxFile = MAX_PATH;
	  open.Flags = OFN_OVERWRITEPROMPT | OFN_PATHMUSTEXIST | OFN_EXPLORER;
      open.lpstrDefExt = TEXT("txt");
      if(GetOpenFileName(&open))
      {
         TCHAR str[300] = { 0 };
		 lstrcat(str, FullPath);
		 wifstream in(FullPath);
		 if (!in)
		 {
			 MessageBox(NULL, TEXT("������ ������ �����"), 0, MB_OK);
			 return TRUE;
		 }
		 in.getline(str, 300);

		 MessageBox(hWnd, str, TEXT("file"), MB_OK | MB_ICONINFORMATION);
		 in.close();
         MessageBox(hWnd, str, TEXT("dhjhfkh	"), MB_OK | MB_ICONINFORMATION);
		 SetWindowText(hEdit, str);
      }

		   MessageBox(hWnd,TEXT("Ferst"),0,MB_OK);
		   }
		   break;
		  case   ID_FILE_SAVE40002:
			  {
				  TCHAR FullPath[MAX_PATH] = {0};
      OPENFILENAME open = {sizeof(OPENFILENAME)};
      open.hwndOwner = hWnd;
      open.lpstrFilter = TEXT("Text Files(*.txt)\0*.txt\0All Files(*.*)\0*.*\0");
      open.lpstrFile = FullPath;
      open.nMaxFile = MAX_PATH;
      open.lpstrInitialDir = TEXT("E:\\");
      open.Flags = OFN_CREATEPROMPT | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY;
      if(GetSaveFileName(&open))
      {
		  TCHAR str[300] = {0};
         lstrcat(str, FullPath);
		 wofstream out(FullPath);
		 if (!out)
		 {
			 MessageBox(NULL, TEXT("������ ������ �����"), 0, MB_OK);
			 return TRUE;
		 }
		 GetWindowText(hEdit, str, 300);
		 out << str << endl;
		 
		 MessageBox(hWnd, str, TEXT("edit1"), MB_OK | MB_ICONINFORMATION);
		 out.close();
      }

		   MessageBox(hWnd,TEXT("Second"),0,MB_OK);
			  }
		   break;
		   case   ID_FILE_EXIT:
			   // ������� ���.
            UnhookWindowsHookEx(hHook);
		   EndDialog(hWnd, 0);
		   break;


	   }
	   return TRUE;
   case WM_CLOSE:
	   // ������� ���.
            UnhookWindowsHookEx(hHook);
	   EndDialog(hWnd, 0);
      return TRUE;
   }
   return FALSE;
}