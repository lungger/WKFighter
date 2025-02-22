#pragma once


namespace game_framework
{
	class Bar :public  BitmapPicture
	{
		friend class CDDraw;
	public:
        Bar();
		Bar(string, int, int, int, bool);
        ~Bar();
        int BelongPlayer;//屬於誰的(靠左或靠右)
        int newWidth;//新的寬度
		virtual void Draw(int, int,double,double);//繪出圖型
        virtual void Draw(int, int, double, double,CameraPosition);//繪出圖型
	};
}
