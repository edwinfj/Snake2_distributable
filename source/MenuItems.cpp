#include "MenuItems.h"

MenuItems::MenuItems(void)
{
	activePos = 0;
}

MenuItems::~MenuItems(void)
{
}

//添加菜单项
void MenuItems::addItem(wstring title)
{
	ItemTitle.push_back(title);
}

//返回当前选中菜单项
int MenuItems::getActive(void)
{
	return activePos;
}

//收到UP键
void MenuItems::onKeyUp(void)
{
	if(--activePos < 0)
		activePos = (int)ItemTitle.size()-1;
}

//收到DOWN键
void MenuItems::onKeyDown(void)
{
	if(++activePos == (int)ItemTitle.size())
		activePos = 0;
}

//渲染菜单
void MenuItems::Render(HDC buffer)
{
	wchar_t str[40];
	 
	//
	Graphics imgraphics(buffer);
	SetBkMode(buffer,TRANSPARENT);
	SetTextColor(buffer,RGB(255,0,0));

	//设置字体,画刷与位置
	FontFamily  fontFamily(L"Times New Roman");
	Font        font(&fontFamily, 28, FontStyleItalic, UnitPixel);
	SolidBrush  solidBrush(Color(255, 0, 0, 255));
	SolidBrush  activeBrush(Color::Yellow );
	SolidBrush  shadowBrush(Color(0x30, 0xDA,0xA5 ,0x20));
	PointF      pointOrig(260.0f, 140.0f);
	PointF      pointF(0.0f, 0.0f);
	
	//渲染
	SolidBrush semiTransBrush(Color(180,0,0,0));
	RectF rect(0,0,640,480);
	imgraphics.FillRectangle (&semiTransBrush,rect);

	semiTransBrush.SetColor (Color(200,0,0,0));
	rect.X =190;
	rect.Y=90; 
	rect.Width = 260;
	rect.Height= 295;
	
	imgraphics.FillRectangle(&semiTransBrush,rect);

	Pen pen(Color(0xAF,0x80,0x80,0x80)  ,12);
	//pen.SetLineJoin (LineJoin::LineJoinRound );
	imgraphics.DrawRectangle(&pen,rect);	

	for(int i=0; i<(int)ItemTitle.size(); i++)
	{
		wsprintf(str,L"%-10s", ItemTitle[i].c_str());
		pointF.X = pointOrig.X;
		pointF.Y = pointOrig.Y + i*(font.GetHeight(96)+6);
		if(this->getActive() == i)
		{
			pointF.X += 4;
			pointF.Y += 4;
			imgraphics.DrawString(str, -1, &font, pointF, &shadowBrush);
			pointF.X -= 8;
			pointF.Y -= 8;
			imgraphics.DrawString(str, -1, &font, pointF, &activeBrush);
		}
		else
			imgraphics.DrawString(str, -1, &font, pointF, &solidBrush);
	}
}
