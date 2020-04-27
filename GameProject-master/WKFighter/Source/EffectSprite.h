#pragma once
#include "stdafx.h"

namespace game_framework
{
    class EffectSprite
    {
    public:
        EffectSprite();
        ~EffectSprite();

        map<string, BitmapAnimation>  Content;//�x�s�Ҧ��S��
        void EffectAutoUpdate(BitmapAnimation*, int, bool, CameraPosition);//(���S�Ħ۰ʧ�s���A�A��bUpdate��)
        //����@��Effect(BitmapAnimation,Camera,XR,XL,Y,VX,VY,Track,���k)
        void BootEffect(BitmapAnimation*, CameraPosition, double, double, double,double,double,bool,bool);
        void DrawAllEffection(int);//��s�禡�A�B�H�۵�������
        void AutoLoadEffections(COLORREF);//Ū���C���������S��
        void InsertEffection(string, int, int, double, COLORREF);//Ū���C���������S��


    };
}

