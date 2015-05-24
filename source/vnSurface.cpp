#include "vnSurface.h"

vnSurface::vnSurface(void)
{
	img = NULL;
}

vnSurface::vnSurface(WCHAR * str)
{
	img = new Image(str);
}


vnSurface::~vnSurface(void)
{
	if(img != NULL)
		delete img;
	
}

// ����ͼ��ָ��
Image * vnSurface::getImage(void)
{
	return img;
}

// ��png�ļ�����ͼ��
void vnSurface::LoadFromPNG(WCHAR * filename)
{
	//���ԭ��������ͼ�����ͷ�
	if(img != NULL)
		delete img;
	//������ͼ��
	img = new Image(filename);
}
