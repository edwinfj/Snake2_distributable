#include "AboutDlg.h"
//�Ի�����Ϣ������
//����ֵ����ΪBOOL,����ͨ���ڴ�������ͬ��
BOOL CALLBACK AboutDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

     switch (message)
     {
     case WM_INITDIALOG :
          return TRUE ;	//�����棬��ʾ��Ϣ�������ˡ�
          
     case WM_COMMAND :
          switch (LOWORD (wParam))
          {
          case IDOK :
          case IDCANCEL :
               EndDialog (hDlg, 0) ;	//ʹ��EndDialog�رնԻ���
               return TRUE ; //�����棬��ʾ��Ϣ�������ˡ�
          }
          break ;
     }
     return FALSE ; ////���ؼ٣���ʾ��Ϣδ���û�����,��ȱʡ��Ϣ������ȥ����
}