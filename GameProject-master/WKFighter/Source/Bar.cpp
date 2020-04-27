#include "stdafx.h"
#include <ddraw.h>
#include <windows.h>
#include <stdio.h>
#include <sstream>
#include "gamelib.h"
#include "WKBitmap.h"
#include "TypeConverter.h"
#include "Bar.h"

namespace game_framework
{
    Bar::Bar()
    {

    }
    Bar::Bar(string path, int BelongPlayerin, int X, int Y, bool vis) : BitmapPicture(path, X, Y, vis, false, false)
    {
        BelongPlayer = BelongPlayerin;
        newWidth = 200;
    }
    Bar::~Bar()
    {
    }
    void Bar::Draw(int CurrentLayer, int TargetLayer, double now, double max)
    {
        Rect.X_int = (int)(Rect.X);
        Rect.Y_int = (int)(Rect.Y);
        newWidth = (int)(((double)Rect.Width)*(now / max));
        if (newWidth <= 0)
            this->visable = false;
        else if (newWidth > 0)
            this->visable = true;

        if (CurrentLayer == TargetLayer&&this->visable == true)//����L���Ϥ��h�Ť~�i�H���
        {
            if (BelongPlayer == 1)
            {
                SetTopLeft(Rect.X_int, Rect.Y_int);
                ShowBitmap(this->Rect.X_int, this->Rect.Y_int, this->Rect.X_int + newWidth, this->Rect.Y_int + this->Rect.Height);
            }
            else if (BelongPlayer == 2)
            {
                SetTopLeft(Rect.X_int, Rect.Y_int);
                ShowBitmap(this->Rect.X_int + (Rect.Width - newWidth), this->Rect.Y_int, this->Rect.X_int + Rect.Width, this->Rect.Y_int + this->Rect.Height);
            }
        }

    }
    void Bar::Draw(int CurrentLayer, int TargetLayer, double now, double max, CameraPosition Camera)
    {
        Rect.X_int = (int)(Rect.X - Camera.X_double);
        Rect.Y_int = (int)(Rect.Y - Camera.Y_double);
        newWidth = (int)(((double)Rect.Width)*(now / max));
        if (newWidth <= 0)
            this->visable = false;
        else if (newWidth > 0)
            this->visable = true;

        if (CurrentLayer == TargetLayer&&this->visable == true)//����L���Ϥ��h�Ť~�i�H���
        {
            if (BelongPlayer == 1)
            {
                SetTopLeft(Rect.X_int, Rect.Y_int);
                ShowBitmap(this->Rect.X_int, this->Rect.Y_int, this->Rect.X_int + newWidth, this->Rect.Y_int + this->Rect.Height);
            }
            else if (BelongPlayer == 2)
            {
                SetTopLeft(Rect.X_int, Rect.Y_int);
                ShowBitmap(this->Rect.X_int + (Rect.Width - newWidth), this->Rect.Y_int, this->Rect.X_int + Rect.Width, this->Rect.Y_int + this->Rect.Height);
            }
        }
    }
}