#include "AboutDlg.h"
//对话框消息处理函数
//返回值类型为BOOL,与普通窗口处理函数不同。
BOOL CALLBACK AboutDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

     switch (message)
     {
     case WM_INITDIALOG :
          return TRUE ;	//返回真，表示消息被处理了。
          
     case WM_COMMAND :
          switch (LOWORD (wParam))
          {
          case IDOK :
          case IDCANCEL :
               EndDialog (hDlg, 0) ;	//使用EndDialog关闭对话框
               return TRUE ; //返回真，表示消息被处理了。
          }
          break ;
     }
     return FALSE ; ////返回假，表示消息未被用户处理,又缺省消息处理函数去处理。
}