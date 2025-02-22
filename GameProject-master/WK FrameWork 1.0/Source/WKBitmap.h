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
        //建構子
        BitmapPicture();
        BitmapPicture(bool);
        BitmapPicture(string, bool);
        BitmapPicture(string, bool,bool);
        ~BitmapPicture();

        //方法函式
        void LoadTexture(bool, COLORREF);//讀取圖檔(使用ResourcePath)
        void LoadTexture(char *, bool, COLORREF);//讀取圖檔
        void OnUpdate();
        void OnUpdate(CameraPosition);
        void Draw(int, int);//繪出圖型
        void Draw(int, int, CMovingBitmap&);//繪出圖型
        void SetResourcePath(string);
        string GetResourcePath();//得到資源路徑連結位置

        //屬性成員
        BitMapRectangle Rect;//圖片材質矩形 掌管座標跟長寬，會在讀取檔案時設定完成，並且可以在外部更動
        vector<vector<bool> > EffectRect;//碰撞有效區域，執行像素碰撞使用
        bool visable;//是否可見
        bool CanPixelCollision;//是否可像素碰撞，如果該圖片無需使用則關閉，可大幅提升效率
        bool InSideCamera;

    private:
        string ResourcePath;//更改名字後建議重讀圖檔
    };

    class BitmapAnimation
    {
    public:
        //建構子
        BitmapAnimation();
        BitmapAnimation(bool);
        BitmapAnimation(string, bool);
        BitmapAnimation(string, bool,bool);
        ~BitmapAnimation();

        //方法函式
        void AutoPlay(int);
        virtual void AutoLoadBitmaps(string, int, bool, COLORREF);//依照Name自動讀取檔名
        virtual void OnUpdate();//更新函式，放在OnMove中(圖片才能動)
        virtual void OnUpdate(CameraPosition);//更新函式，且隨著視角移動
        string GetName();//得到Name
        void SetName(string);//更改名字後需要立刻重讀圖檔!!

        //屬性成員
        BitMapRectangle Rect;//圖片材質矩形 掌管座標跟長寬，會在讀取檔案時設定完成，並且可以在外部更動
        BitmapPicture *DisplayBitmap;//永遠把顯示用的Bitmap指向對應的BitmapPicture==當前所顯示的BitmapPicture
        int Step;//當前步驟數
        int AutoMaxStep;//使用自動播放時的最大步驟數
        double AutoPlayTimer;//使用自動播放時的計時器
        bool visable;//是否可見
        bool CanPixelCollision;//是否使用像素碰撞，所有動作分割都會套用
        bool InSideCamera;
        map<string, BitmapPicture>  BitmapPictures;//該Animation的所有圖片動作
    private:
            string Name;//此可動圖檔的名稱[資源命名規則:放在Content\\Bitmaps\\Name\\Name_Step.bmp]

    };

}

