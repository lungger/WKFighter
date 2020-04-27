#pragma once
#include "stdafx.h"
#include "CollisionSensor.h"
#include "TypeConverter.h"
#include "EffectSprite.h"
#include "WKAudio.h"



using namespace std;
using namespace WKAudio_namespace;
using namespace CollisionSensor_namespace;


namespace game_framework
{
    #define AttackObjPH AttackObj *Attack, string BeloneName,BattlePlayer *Belone,BattlePlayer *Target,double Damage ,double SP_Damege,int Mass, bool IsRight,double HitVelocity_X, double HitVelocity_Y,double XR,double XL, double Y,double VX,double VY,double HitTime,double MaxAliveTime,int Attributes, bool CanCombo ,bool Drawable,bool Replay ,bool HitNoon,bool HitBreak,bool CanHitFly,bool CanBeDisappear,bool CanCrackOther,string HitEffect,int HitSound,CameraPosition Camera
    #define AttackObjPH_Normal AttackObj *Attack, BattlePlayer *Belone, BattlePlayer *Target, double Damage,  double HitVelocity_X, double HitVelocity_Y, double XR, double XL, double Y, double VX, double VY, double HitTime, double MaxAliveTime, string HitEffect,const int HitSound, CameraPosition Camera
    #define AttackObjPH_Shot AttackObj *Attack, BattlePlayer *Belone, BattlePlayer *Target, double Damage,  double HitVelocity_X, double HitVelocity_Y, double XR, double XL, double Y, double VX, double VY, double HitTime, double MaxAliveTime,int Mass,bool HitNoon,bool CanBeDisappear,bool CanCrackOther, string HitEffect,const int HitSound, CameraPosition Camera
    ////
    #define PerfectBlockTime 100
    ////

    class BattlePlayer;
    class EffectSprite;

    class AttackObj :public BitmapAnimation
    {
    public:
        AttackObj();
        AttackObj(string, int, int, bool, bool, bool);
        ~AttackObj();


        virtual void OnUpdate(string, CameraPosition);
		virtual void HitAction(CameraPosition);
        //�{���ܼ�
        double AliveTimer = 0;
        double ComboTimer = 0;

        double Timer1 = 0;
        double Timer2 = 0;
        bool IsHited;//�w�g����

                     //�ݩ��ܼ�
        double Damage;//�ˮ`
        double SP_Damege;//��SP�y�����
        double HitTime;//�ϼĤH�����ɶ�
        double MaxAliveTime;//�����̤j��ܮɶ�

        double HitVelocity_X;
        double HitVelocity_Y;

        int Mass;//�Z���O��
        int Attributes;//���A�ݩ�-1=�L
        bool CanCombo;//�i��������
        bool Drawable;//�O�_�ݭnø�s�X��
        bool Replay;//�O�_�N�������ɫ��򼷩�
        bool HitNoon;//�O�_�������N����
        bool HitBreak;//�O�_�}��
        bool CanHitFly;//�O�_�i����
        bool CanBeDisappear;//�i�Q��P
        bool CanCrackOther;//�i��P�O������
        bool GravityEffect;//�O�_�����O�v�T
		bool UseRectCollision;//�ϥίx�θI���P�w


        string HitEffect;//�����S�ĦW��
        int HitSound;//�����n��ID


        EffectSprite Effects;
        double Ahead(double move);

        BattlePlayer *Belone;
        BattlePlayer *Target;

    };





    class AttackManager
    {
    public:
        AttackManager();
        ~AttackManager();
        map<string, AttackObj> AttackObjects;//�x�s�Ҧ���������
        virtual void AttackAutoUpdate(AttackObj * Attack, string BeloneName, int tick, bool replay, CameraPosition Camera);
        virtual void AttackReset(AttackObjPH);
        virtual void AttackReset_Normal(AttackObjPH_Normal);
        virtual void AttackReset_Shot(AttackObjPH_Shot);
        virtual void DrawAllAttacks(int);
        virtual void InsertAttacks(string BeloneName, string name, int maxstep, int drawlayer, double pre, int category, COLORREF color, CameraPosition Camera);
        virtual void InsertAttacks(string BeloneName, string name, int maxstep, int drawlayer, double pre, int category, int current, COLORREF color, CameraPosition Camera);
    };
}
