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
        int BelongPlayer;//�ݩ�֪�(�a���ξa�k)
        int newWidth;//�s���e��
		virtual void Draw(int, int,double,double);//ø�X�ϫ�
        virtual void Draw(int, int, double, double,CameraPosition);//ø�X�ϫ�
	};
}
