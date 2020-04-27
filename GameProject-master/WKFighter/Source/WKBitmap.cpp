#pragma once
#include "stdafx.h"
#include <ddraw.h>
#include <windows.h>
#include <stdio.h>
#include <sstream>
#include "gamelib.h"
#include "WKBitmap.h"
#include "TypeConverter.h"
using namespace std;
using namespace TypeConverter_namespace;
namespace game_framework
{
    /////////////////////////////////////////////////////////////////////////////
    // BitmapPicture: ���Ѥ@�ӥH�U�\���ƪ�Bitmap�Ϥ�
    //1.�z����]�w
    //2.���湳���I��
    //3.�i�H����
    /////////////////////////////////////////////////////////////////////////////
    BitmapPicture::BitmapPicture()
    {
        Rect.X = 0;
        Rect.Y = 0;
        Rect.X_int = 0;
        Rect.Y_int = 0;
        visable = false;
        ResourcePath = "";
        CanPixelCollision = false;
        InSideCamera = false;
    }
    BitmapPicture::BitmapPicture(bool vis)
    {
        Rect.X = 0;
        Rect.Y = 0;
        Rect.X_int = 0;
        Rect.Y_int = 0;
        visable = vis;
        ResourcePath = "";
        CanPixelCollision = false;
        InSideCamera = false;
    }
    BitmapPicture::BitmapPicture(string respath, bool vis)
    {
        Rect.X = 0;
        Rect.Y = 0;
        Rect.X_int = 0;
        Rect.Y_int = 0;
        visable = vis;
        ResourcePath = respath;
        CanPixelCollision = false;
        InSideCamera = false;
    }
    BitmapPicture::BitmapPicture(string respath, bool vis, bool inside)
    {
        Rect.X = 0;
        Rect.Y = 0;
        Rect.X_int = 0;
        Rect.Y_int = 0;
        visable = vis;
        ResourcePath = respath;
        CanPixelCollision = false;
        InSideCamera = inside;
    }
    BitmapPicture::BitmapPicture(string respath, int X_in, int Y_in, bool vis, bool canhit, bool inside)
    {
        Rect.X = X_in;
        Rect.Y = Y_in;
        Rect.X_int = X_in;
        Rect.Y_int = Y_in;
        visable = vis;
        ResourcePath = respath;
        CanPixelCollision = canhit;
        InSideCamera = inside;
    }
    BitmapPicture::~BitmapPicture()
    {
    }
    void BitmapPicture::LoadTexture(COLORREF color)
    {
        char *cc = new char[3000];
        strcpy(cc, ResourcePath.c_str());
        if (this->isBitmapLoaded == false)
        {
            const int nx = 0;
            const int ny = 0;
            GAME_ASSERT(!isBitmapLoaded, "A bitmap has been loaded. You can not load another bitmap !!!");
            HBITMAP hbitmap = (HBITMAP)LoadImage(NULL, cc, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
            if (hbitmap == NULL)
            {
                char error_msg[300];
                sprintf(error_msg, "Loading bitmap from file \"%s\" failed !!!", cc);
                GAME_ASSERT(false, error_msg);
            }
            CBitmap *bmp = CBitmap::FromHandle(hbitmap); // memory will be deleted automatically
            BITMAP bitmapSize;
            bmp->GetBitmap(&bitmapSize);
            this->location.left = nx; this->location.top = ny;
            this->location.right = nx + bitmapSize.bmWidth;
            this->location.bottom = ny + bitmapSize.bmHeight;
            this->SurfaceID = CDDraw::RegisterBitmap(cc, color);
            this->isBitmapLoaded = true;
            Rect.Width = Width();
            Rect.Height = Height();
            if (CanPixelCollision)//�p�G���Ϥ��ݭn�I���Ϥ~�ϥ�
            {
                CDC dc;
                CDC* pDC = CDDraw::GetBackCDC();
                dc.CreateCompatibleDC(pDC);

                for (int y = 0; y < bitmapSize.bmHeight; y++)
                {
                    EffectRect.push_back(vector<bool>());
                    for (int x = 0; x < bitmapSize.bmWidth; x++)
                    {
                        EffectRect[y].push_back(false);

                        if (RGB(GetRValue(dc.GetPixel(x, y)), GetGValue(dc.GetPixel(x, y)), GetBValue(dc.GetPixel(x, y))) != color)
                        {
                            EffectRect[y][x] = true;
                        }
                    }
                }
                CDDraw::ReleaseBackCDC();
            }
            bmp->DeleteObject();
        }
        delete[] cc;
    }
    void BitmapPicture::LoadTexture(bool CanHit, COLORREF color)
    {
        char *cc = new char[3000];
        strcpy(cc, ResourcePath.c_str());
        if (this->isBitmapLoaded == false)
        {
            CanPixelCollision = CanHit;
            const int nx = 0;
            const int ny = 0;
            GAME_ASSERT(!isBitmapLoaded, "A bitmap has been loaded. You can not load another bitmap !!!");
            HBITMAP hbitmap = (HBITMAP)LoadImage(NULL, cc, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
            if (hbitmap == NULL)
            {
                char error_msg[300];
                sprintf(error_msg, "Loading bitmap from file \"%s\" failed !!!", cc);
                GAME_ASSERT(false, error_msg);
            }
            CBitmap *bmp = CBitmap::FromHandle(hbitmap); // memory will be deleted automatically
            BITMAP bitmapSize;
            bmp->GetBitmap(&bitmapSize);
            this->location.left = nx; this->location.top = ny;
            this->location.right = nx + bitmapSize.bmWidth;
            this->location.bottom = ny + bitmapSize.bmHeight;
            this->SurfaceID = CDDraw::RegisterBitmap(cc, color);
            this->isBitmapLoaded = true;
            Rect.Width = Width();
            Rect.Height = Height();
            if (CanHit)//�p�G���Ϥ��ݭn�I���Ϥ~�ϥ�
            {
                CDC dc;
                CDC* pDC = CDDraw::GetBackCDC();
                dc.CreateCompatibleDC(pDC);

                for (int y = 0; y < bitmapSize.bmHeight; y++)
                {
                    EffectRect.push_back(vector<bool>());
                    for (int x = 0; x < bitmapSize.bmWidth; x++)
                    {
                        EffectRect[y].push_back(false);

                        if (RGB(GetRValue(dc.GetPixel(x, y)), GetGValue(dc.GetPixel(x, y)), GetBValue(dc.GetPixel(x, y))) != color)
                        {
                            EffectRect[y][x] = true;
                        }
                    }
                }
                CDDraw::ReleaseBackCDC();
            }
            bmp->DeleteObject();
        }
        delete[] cc;
    }
    void BitmapPicture::LoadTexture(char *filename, bool CanHit, COLORREF color)
    {
        if (this->isBitmapLoaded == false)
        {
            CanPixelCollision = CanHit;
            const int nx = 0;
            const int ny = 0;
            GAME_ASSERT(!isBitmapLoaded, "A bitmap has been loaded. You can not load another bitmap !!!");
            HBITMAP hbitmap = (HBITMAP)LoadImage(NULL, filename, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
            if (hbitmap == NULL) {
                char error_msg[300];
                sprintf(error_msg, "Loading bitmap from file \"%s\" failed !!!", filename);
                GAME_ASSERT(false, error_msg);
            }
            CBitmap *bmp = CBitmap::FromHandle(hbitmap); // memory will be deleted automatically
            BITMAP bitmapSize;
            bmp->GetBitmap(&bitmapSize);
            this->location.left = nx; this->location.top = ny;
            this->location.right = nx + bitmapSize.bmWidth;
            this->location.bottom = ny + bitmapSize.bmHeight;
            this->SurfaceID = CDDraw::RegisterBitmap(filename, color);
            this->isBitmapLoaded = true;
            Rect.Width = Width();
            Rect.Height = Height();
            if (CanHit)//�p�G���Ϥ��ݭn�I���Ϥ~�ϥ�
            {
                CDC dc;
                CDC* pDC = CDDraw::GetBackCDC();
                dc.CreateCompatibleDC(pDC);
                for (int y = 0; y < bitmapSize.bmHeight; y++)
                {
                    EffectRect.push_back(vector<bool>());
                    for (int x = 0; x < bitmapSize.bmWidth; x++)
                    {
                        EffectRect[y].push_back(false);
                        COLORREF rgb = dc.GetPixel(x, y);
                        BYTE r = GetRValue(rgb);
                        BYTE g = GetGValue(rgb);
                        BYTE b = GetBValue(rgb);
                        if (RGB(r, g, b) != color)
                        {
                            EffectRect[y][x] = true;
                        }
                    }
                }
                CDDraw::ReleaseBackCDC();
            }
            bmp->DeleteObject();
        }
    }
    void BitmapPicture::OnUpdate()
    {
        Rect.X_int = (int)(Rect.X);
        Rect.Y_int = (int)(Rect.Y);
    }
    void BitmapPicture::OnUpdate(CameraPosition Camera)
    {
        if (InSideCamera)
        {
            Rect.X_int = (int)(Rect.X - Camera.X);
            Rect.Y_int = (int)(Rect.Y - Camera.Y);
        }
        else
        {
            Rect.X_int = (int)(Rect.X);
            Rect.Y_int = (int)(Rect.Y);
        }
    }
    void BitmapPicture::Draw(int CurrentLayer, int TargetLayer)
    {
        if (CurrentLayer == TargetLayer&&this->visable == true)//����L���Ϥ��h�Ť~�i�H���
        {
            SetTopLeft(Rect.X_int, Rect.Y_int);
            ShowBitmap();
        }
    }
    void BitmapPicture::Draw(int CurrentLayer, int TargetLayer, double fra)
    {
        if (CurrentLayer == TargetLayer&&this->visable == true)//����L���Ϥ��h�Ť~�i�H���
        {
            SetTopLeft(Rect.X_int, Rect.Y_int);
            int xl, xr, yt, yb;
            xl = (int)(this->Rect.X + (this->Rect.Width*(1 - fra)*0.5));
            yt = (int)(this->Rect.Y + (this->Rect.Height*(1 - fra)*0.5));
            xr = (int)((this->Rect.X + this->Rect.Width) - (this->Rect.Width*(1 - fra)*0.5));
            yb = (int)((this->Rect.Y + this->Rect.Height) - (this->Rect.Height*(1 - fra)*0.5));


            ShowBitmap(xl, yt, xr, yb);
        }
    }
    void BitmapPicture::SetResourcePath(string namein)
    {
        ResourcePath = namein;
    }
    string BitmapPicture::GetResourcePath()
    {
        return ResourcePath;
    }

    /////////////////////////////////////////////////////////////////////////////
    // BitmapAnimation: ���Ѥ@�ӥH�U�\���ƪ�Bitmap�Ϥ�
    //1.�z����]�w
    //2.���湳���I��(�C�i�ϳ����W�ߪ��I���P�_)
    //3.�i�H����
    //4.�]�t�F�@�t�C��BitmapPicture�A�i�H�������|�ʪ��Ϥ�
    /////////////////////////////////////////////////////////////////////////////
    BitmapAnimation::BitmapAnimation()
    {
        Name = "";
        Step = 0;
        AutoMaxStep = 0;
        AutoPlayTimer = 0;
        CanPixelCollision = false;
        visable = false;
        BitmapisRight = true;
        drawlayer = 0;
        TrackPoint = false;
        Velocity_X = 0;
        Velocity_Y = 0;
        Acceleration_X = 0;
        Acceleration_Y = 0;
    }
    BitmapAnimation::BitmapAnimation(bool vis)
    {
        Name = "";
        Step = 0;
        AutoMaxStep = 0;
        AutoPlayTimer = 0;
        CanPixelCollision = false;
        visable = vis;
        BitmapisRight = true;
        drawlayer = 0;
        TrackPoint = false;
        Velocity_X = 0;
        Velocity_Y = 0;
        Acceleration_X = 0;
        Acceleration_Y = 0;
    }
    BitmapAnimation::BitmapAnimation(string namein, bool vis)
    {
        Step = 0;
        AutoMaxStep = 0;
        AutoPlayTimer = 0;
        CanPixelCollision = false;
        Name = namein;
        visable = vis;
        BitmapisRight = true;
        drawlayer = 0;
        TrackPoint = false;
        Velocity_X = 0;
        Velocity_Y = 0;
        Acceleration_X = 0;
        Acceleration_Y = 0;
    }
    BitmapAnimation::BitmapAnimation(string namein, bool vis, bool inside)
    {
        Step = 0;
        AutoMaxStep = 0;
        AutoPlayTimer = 0;
        CanPixelCollision = false;
        Name = namein;
        visable = vis;
        InSideCamera = inside;
        BitmapisRight = true;
        drawlayer = 0;
        TrackPoint = false;
        Velocity_X = 0;
        Velocity_Y = 0;
        Acceleration_X = 0;
        Acceleration_Y = 0;
    }
    BitmapAnimation::BitmapAnimation(string namein, int X, int Y, bool vis, bool CanHit, bool inside)
    {
        Step = 0;
        AutoMaxStep = 0;
        AutoPlayTimer = 0;
        CanPixelCollision = CanHit;
        Name = namein;
        visable = vis;
        InSideCamera = inside;
        Rect.X = X;
        Rect.Y = Y;
        Rect.X_int = X;
        Rect.Y_int = Y;
        BitmapisRight = true;
        drawlayer = 0;
        TrackPoint = false;
        Velocity_X = 0;
        Velocity_Y = 0;
        Acceleration_X = 0;
        Acceleration_Y = 0;
    }
    BitmapAnimation::~BitmapAnimation()
    {

    }
    void BitmapAnimation::AutoPlay(int frequence, bool replay)
    {
        if (AutoPlayTimer >= frequence)
        {
            AutoPlayTimer = 0;
            if (Step < AutoMaxStep - 1)
            {
                Step += 1;
            }
            else
            {
                if (replay)
                {
                    Step = 0;
                }
                else
                {
                    this->visable = false;
                    this->DisplayBitmap->visable = false;
                }
            }
        }
        else
        {
            AutoPlayTimer += TIMER_TICK_MILLIDECOND;
        }

    }
    void BitmapAnimation::AutoLoadBitmaps(string name, int MaxSteps, bool CanPixelCollisionin, COLORREF color)
    {
        AutoMaxStep = MaxSteps;
        CanPixelCollision = CanPixelCollisionin;
        string StepString = IntToString(MaxSteps);

        for (int i = 0; i < MaxSteps; i += 1)
        {
            string str = ("Content\\Bitmaps\\" + name + "\\" + name + "_" + IntToString(i) + ".bmp");
            BitmapPictures.insert(std::pair<string, BitmapPicture>(str, BitmapPicture(visable)));
            char *cc = new char[65535];
            strcpy(cc, str.c_str());
            BitmapPictures[str].LoadTexture(cc, CanPixelCollisionin, color);
            delete[] cc;
        }
        OnUpdate();
    }
    //Effect�n�����k
    void BitmapAnimation::AutoLoadBitmaps(string folder, string name, int MaxSteps, double pre, bool CanPixelCollisionin, COLORREF color)
    {
        AutoMaxStep = MaxSteps;
        CanPixelCollision = CanPixelCollisionin;
        string StepString = IntToString(MaxSteps);
        PreAutoFrequence = pre;

        for (int i = 0; i < MaxSteps; i += 1)
        {
            string str;
            str = ("Content\\Bitmaps\\" + folder + "\\" + name + "_" + IntToString(i) + ".bmp");
            BitmapPictures.insert(std::pair<string, BitmapPicture>(str, BitmapPicture(visable)));
            char *cr = new char[65535];
            strcpy(cr, str.c_str());
            BitmapPictures[str].LoadTexture(cr, CanPixelCollisionin, color);
            delete[] cr;
            str = ("Content\\Bitmaps\\" + folder + "\\" + name + "_" + IntToString(i) + "_L.bmp");
            BitmapPictures.insert(std::pair<string, BitmapPicture>(str, BitmapPicture(visable)));
            char *cl = new char[65535];
            strcpy(cl, str.c_str());
            BitmapPictures[str].LoadTexture(cl, CanPixelCollisionin, color);
            delete[] cl;
        }
    }
    void BitmapAnimation::OnUpdate()
    {
        string Actionstring;
        if (BitmapisRight)
        {
            Actionstring = "Content\\Bitmaps\\" + Name + "\\" + Name + "_" + IntToString(Step) + ".bmp";
        }
        else
        {
            Actionstring = "Content\\Bitmaps\\" + Name + "\\" + Name + "_" + IntToString(Step) + "_L.bmp";
        }
        char *cc = new char[65535];
        strcpy(cc, Actionstring.c_str());
        DisplayBitmap = &BitmapPictures[cc];
        Rect.Width = DisplayBitmap->Rect.Width;
        Rect.Height = DisplayBitmap->Rect.Height;
        Rect.X_int = (int)(Rect.X);
        Rect.Y_int = (int)(Rect.Y);
        DisplayBitmap->Rect.X = Rect.X_int;
        DisplayBitmap->Rect.Y = Rect.Y_int;
        DisplayBitmap->OnUpdate();
        DisplayBitmap->visable = visable;
        delete[] cc;
    }
    void BitmapAnimation::OnUpdate(CameraPosition Camera)
    {
        string Actionstring;
        if (BitmapisRight)
        {
            Actionstring = "Content\\Bitmaps\\" + Name + "\\" + Name + "_" + IntToString(Step) + ".bmp";
        }
        else
        {
            Actionstring = "Content\\Bitmaps\\" + Name + "\\" + Name + "_" + IntToString(Step) + "_L.bmp";
        }
        char *cc = new char[65535];
        strcpy(cc, Actionstring.c_str());
        DisplayBitmap = &BitmapPictures[cc];
        Rect.Width = DisplayBitmap->Rect.Width;
        Rect.Height = DisplayBitmap->Rect.Height;
        if (InSideCamera)
        {
            Rect.X_int = (int)(Rect.X - Camera.X);
            Rect.Y_int = (int)(Rect.Y - Camera.Y);
        }
        else
        {
            Rect.X_int = (int)(Rect.X);
            Rect.Y_int = (int)(Rect.Y);
        }
        DisplayBitmap->Rect.X = Rect.X_int;
        DisplayBitmap->Rect.Y = Rect.Y_int;
        DisplayBitmap->OnUpdate();
        DisplayBitmap->visable = visable;
        delete[] cc;
    }
    void BitmapAnimation::OnUpdate(string unsingfolder, CameraPosition Camera)
    {
        string Actionstring;
        if (BitmapisRight)
        {
            Actionstring = "Content\\Bitmaps\\" + unsingfolder + "\\" + Name + "_" + IntToString(Step) + ".bmp";
        }
        else
        {
            Actionstring = "Content\\Bitmaps\\" + unsingfolder + "\\" + Name + "_" + IntToString(Step) + "_L.bmp";
        }
        char *cc = new char[65535];
        strcpy(cc, Actionstring.c_str());
        DisplayBitmap = &BitmapPictures[cc];
        Rect.Width = DisplayBitmap->Rect.Width;
        Rect.Height = DisplayBitmap->Rect.Height;
        if (InSideCamera)
        {
            Rect.X_int = (int)(Rect.X - Camera.X);
            Rect.Y_int = (int)(Rect.Y - Camera.Y);
        }
        else
        {
            Rect.X_int = (int)(Rect.X);
            Rect.Y_int = (int)(Rect.Y);
        }
        DisplayBitmap->Rect.X = Rect.X_int;
        DisplayBitmap->Rect.Y = Rect.Y_int;
        DisplayBitmap->OnUpdate();
        DisplayBitmap->visable = visable;
        delete[] cc;
    }
    string BitmapAnimation::GetName()
    {
        return Name;
    }
    void BitmapAnimation::SetName(string namein)
    {
        Name = namein;

    }

}