#pragma once
#include "TypeConverter.h"
using namespace std;
using namespace TypeConverter_namespace;

namespace game_framework
{
	struct BitMapRectangle
	{
		int X_int = 0;
		int Y_int = 0;
		double X = 0;
		double Y = 0;
		int Width = 0;
		int Height = 0;
	};
	struct CameraPosition
	{
		int X = 0;
		int Y = 0;
		double X_double = 0;
		double Y_double = 0;
	};
	class BitmapPicture :public   CMovingBitmap
	{
		friend class CDDraw;
	public:
		//�H�t
		BitmapPicture();
		//(�O�_�i��)
		BitmapPicture(bool);
		//(���|,�O�_�i��)
		BitmapPicture(string, bool);
		//(���|,�O�_�i��,�O�_�������Y�v�T)
		BitmapPicture(string, bool, bool);
		//(���|,X,Y,�O�_�i��,�O�_�i�I��,�O�_�������Y�v�T)
		BitmapPicture(string, int, int, bool, bool, bool);
		//�Ѻc�l
		~BitmapPicture();

		//��k�禡
		//Ū������(�u�ݿ�J�z����)
		void LoadTexture(COLORREF);
		//Ū������(�ϥ�ResourcePath,�z����)
		void LoadTexture(bool, COLORREF);
		//Ū������(���|,�O�_�i�����I��,�z����)
		void LoadTexture(char *, bool, COLORREF);
		void OnUpdate();
		void OnUpdate(CameraPosition);
		//ø�X�ϫ�
		virtual void Draw(int, int);
		virtual void Draw(int, int,double);

		//�]�w�귽���|�s��
		void SetResourcePath(string);
		//�o��귽���|�s����m
		string GetResourcePath();

		//�ݩʦ���
		BitMapRectangle Rect;//�Ϥ�����x�� �x�ޮy�и���e�A�|�bŪ���ɮ׮ɳ]�w�����A�åB�i�H�b�~�����
		vector<vector<bool> > EffectRect;//�I�����İϰ�A���湳���I���ϥ�
		bool visable;//�O�_�i��
		bool CanPixelCollision;//�O�_�i�����I���A�p�G�ӹϤ��L�ݨϥΫh�����A�i�j�T���ɮĲv
		bool InSideCamera;

	private:
		string ResourcePath;//���W�r���ĳ��Ū����
	};
	class BitmapAnimation
	{
	public:
		//�غc�l
		BitmapAnimation();
		//(�O�_�i��)
		BitmapAnimation(bool);
		//(���|,�O�_�i��)
		BitmapAnimation(string, bool);
		//(���|,�O�_�i��,�O�_�������Y�v�T)
		BitmapAnimation(string, bool, bool);
		//(���|,X,Y,�O�_�i��,�O�_�i�I��,�O�_�������Y�v�T)
		BitmapAnimation(string, int, int, bool, bool, bool);
		//�Ѻc�l
		~BitmapAnimation();

		//��k�禡
		void AutoPlay(int, bool);//�۰ʼ���Ϥ�(�W�v,�O�_���Ƽ���)
		virtual void AutoLoadBitmaps(string, int, bool, COLORREF);//�̷�Name�۰�Ū���ɦW
		virtual void AutoLoadBitmaps(string, string, int, double, bool, COLORREF);//�̷Ӹ�Ƨ���Name�۰�Ū���ɦW    //Effect�n�����k
		virtual void OnUpdate();//��s�禡�A��bOnMove��(�Ϥ��~���)
		virtual void OnUpdate(CameraPosition);//��s�禡�A�B�H�۵�������
		virtual void OnUpdate(string, CameraPosition);//Effectfolder�A�b�ɦW�e�w�[�r��
		string GetName();//�o��Name
		void SetName(string);//���W�r��ݭn�ߨ譫Ū����!!

		//�ݩ��ܼ�
		int AutoMaxStep;//�ϥΦ۰ʼ���ɪ��̤j�B�J��
		int drawlayer;//ø�Ϲϼh
		double PreAutoFrequence;//�w�]�������W�v
		bool visable;//�O�_�i��
		bool CanPixelCollision;//�O�_�ϥι����I���A�Ҧ��ʧ@���γ��|�M��
		bool InSideCamera;//�O�_�������Y�v�T
		bool BitmapisRight;//�O�_�V�k
		bool TrackPoint;//�O�_����l�ܬY�@�I
		bool loop = false;//�O�_����("�w�]=�_")

		//�{���ܼ�
		double AutoPlayTimer;//�ϥΦ۰ʼ���ɪ��p�ɾ�
		int Step;//��e�B�J��
        double Acceleration_X;//X�[�t��
        double Acceleration_Y;//Y�[�t��
        double Velocity_X = 0;//X�b�t��
        double Velocity_Y = 0;//Y�b�t��
        double Acceleration_gravity = 0.5;//���O�[�t��

		//�ݩʦ���
		BitMapRectangle Rect;//�Ϥ�����x�� �x�ޮy�и���e�A�|�bŪ���ɮ׮ɳ]�w�����A�åB�i�H�b�~�����
		BitmapPicture *DisplayBitmap;//�û�����ܥΪ�Bitmap���V������BitmapPicture==��e����ܪ�BitmapPicture
		map<string, BitmapPicture>  BitmapPictures;//��Animation���Ҧ��Ϥ��ʧ@
	private:
		string Name;//���i�ʹ��ɪ��W��[�귽�R�W�W�h:��bContent\\Bitmaps\\Name\\Name_Step.bmp]
	};
}

