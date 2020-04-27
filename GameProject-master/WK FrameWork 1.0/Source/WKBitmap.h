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
    };


    class BitmapPicture : CMovingBitmap
    {
        friend class CDDraw;
    public:
        //�غc�l
        BitmapPicture();
        BitmapPicture(bool);
        BitmapPicture(string, bool);
        BitmapPicture(string, bool,bool);
        ~BitmapPicture();

        //��k�禡
        void LoadTexture(bool, COLORREF);//Ū������(�ϥ�ResourcePath)
        void LoadTexture(char *, bool, COLORREF);//Ū������
        void OnUpdate();
        void OnUpdate(CameraPosition);
        void Draw(int, int);//ø�X�ϫ�
        void Draw(int, int, CMovingBitmap&);//ø�X�ϫ�
        void SetResourcePath(string);
        string GetResourcePath();//�o��귽���|�s����m

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
        BitmapAnimation(bool);
        BitmapAnimation(string, bool);
        BitmapAnimation(string, bool,bool);
        ~BitmapAnimation();

        //��k�禡
        void AutoPlay(int);
        virtual void AutoLoadBitmaps(string, int, bool, COLORREF);//�̷�Name�۰�Ū���ɦW
        virtual void OnUpdate();//��s�禡�A��bOnMove��(�Ϥ��~���)
        virtual void OnUpdate(CameraPosition);//��s�禡�A�B�H�۵�������
        string GetName();//�o��Name
        void SetName(string);//���W�r��ݭn�ߨ譫Ū����!!

        //�ݩʦ���
        BitMapRectangle Rect;//�Ϥ�����x�� �x�ޮy�и���e�A�|�bŪ���ɮ׮ɳ]�w�����A�åB�i�H�b�~�����
        BitmapPicture *DisplayBitmap;//�û�����ܥΪ�Bitmap���V������BitmapPicture==��e����ܪ�BitmapPicture
        int Step;//��e�B�J��
        int AutoMaxStep;//�ϥΦ۰ʼ���ɪ��̤j�B�J��
        double AutoPlayTimer;//�ϥΦ۰ʼ���ɪ��p�ɾ�
        bool visable;//�O�_�i��
        bool CanPixelCollision;//�O�_�ϥι����I���A�Ҧ��ʧ@���γ��|�M��
        bool InSideCamera;
        map<string, BitmapPicture>  BitmapPictures;//��Animation���Ҧ��Ϥ��ʧ@
    private:
            string Name;//���i�ʹ��ɪ��W��[�귽�R�W�W�h:��bContent\\Bitmaps\\Name\\Name_Step.bmp]

    };

}

