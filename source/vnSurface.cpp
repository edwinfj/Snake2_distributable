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

// 返回图形指针
Image * vnSurface::getImage(void)
{
	return img;
}

// 从png文件载入图像
void vnSurface::LoadFromPNG(WCHAR * filename)
{
	//如果原来载入有图像，则释放
	if(img != NULL)
		delete img;
	//载入新图像
	img = new Image(filename);
}
