#pragma once
#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include <windows.h>
#include <vector>
#include "audio.h"
#include "gamelib.h"
#include "Keycode.h"
#include "KeyBoardState.h"
#include "WKBitmap.h"
#include "BattlePlayer.h"
#include "CollisionSensor.h"
#include "TypeConverter.h"
#include "WKAudio.h"
#include "AttackObj.h"
#include "Characters.h"
#include "EffectSprite.h"
#include "FunctionUser.h"

using namespace std;
using namespace WKAudio_namespace;
using namespace CollisionSensor_namespace;
using namespace TypeConverter_namespace;
using namespace FunctionUser_namespace;

namespace game_framework
{
    #pragma region �s�W�ʧ@�о�
    /*
    �p��s�W�@�Ө���ʧ@
    1.�ǳƦn�Ϥ��A�Ϥ��R�W�W�h(�ʧ@�V�k):����W��\�ʧ@�W��_Step.bmp
    �������ǳƦn��A�ǳƥ��k�ۤϪ��Ϥ��A�åB�ɦW��:����W��\�ʧ@�W��_Step_L.bmp

    2.����void Matchstick::AutoLoadBitmaps(GPH)�̭��s�W�ʧ@��InsertAction("�ʧ@�W��", �ʧ@�̤j��, color);

    3.�p�G����������A��void Matchstick::AutoLoadAttacks(GPH)�s�W
    Attacks.InsertAttacks(GetName(), "�ʧ@�W��", ��������̤jStep��, ø�s�ϼh, �Ϥ��ܤƳt��, ��������, color, Camera);

    4.�bvoid Matchstick::OnUpdate(GPH)���s�W�۹������禡

    5.�s�gGoto�禡�A�D�n�O�Ψӱ���i�J�Ӱʧ@�ɪ���l���ܼơC

    6.��BattlePlayer�s�gCanTo�C

    7.�s�gOn�禡�A�ʧ@������A�H�@��IF�P�_�O�_�b�o�Ӱʧ@�̭��A�HSTEP�MTIMER����ʧ@�y�{�A�̫ᵹ���@�q�����ɶ�������i�H���L�i�檺�ʧ@(CanTo)�C
    */
    #pragma endregion

    #pragma region ����H

    Matchstick::Matchstick(int number) :BattlePlayer()
    {
        Restvalues(number);
    }
    Matchstick::~Matchstick()
    {

    }

    void Matchstick::Restvalues(int number)
    {
        //��O���ܼ�
        HP_Max = Matchstick_HP_Max;//�̤j�ͩR��
        SP_Max = Matchstick_SP_Max;//�̤j��O
        recovery = 0;
        Rush_cost = Matchstick_Rush_Cost;//�Ĩ���Ӷq
        StandbySPincrements = Matchstick_StandbySPincrements;
        RunningSPincrements = Matchstick_RunningSPincrements;
        RunSpeed = Matchstick_RunSpeed;
        ChargeSPincrements = Matchstick_ChargeSPincrements;
        //�{���ܼ�
        SetName("Matchstick");
        PlayerNumber = number;//���a�s��
        if (number == 1)
        {
            IsRight = true;
        }
        else if (number == 2)
        {
            IsRight = false;
        }
        HP = HP_Max;//��e�ͩR
        SP = SP_Max / 2;//��e��O
        CanControl = false;//�i�H����
        Invincible = false;//�L�Ī��A
        Action = "�ݾ�";//�ʧ@���A
        Step = 0;//��e�B�J��
        visable = true;//�O�_�i��
        CanPixelCollision = true;//�O�_�ϥι����I���A�Ҧ��ʧ@���γ��|�M��
        InSideCamera = true;//�O�_�������Y�v�T
        Velocity_X = 0;//X�t��
        Velocity_Y = 0;//Y�t��
        Acceleration_X = 0;//X�[�t��
        Acceleration_Y = 0;//Y�[�t��
        Throughing = false;
        HitFly = false;
        BreakPoint = 0;
        Acceleration_gravity = 0.5;
    }

    //Ū�ɦb��
    void Matchstick::AutoLoadBitmaps(GPH)
    {
        //���ħP�w��BitRect
        BodyPicture.LoadTexture(color);


        InsertAction("�ݾ�", 1, color);
        InsertAction("����", 4, color);
        InsertAction("�Ĩ�", 1, color);
        InsertAction("���D", 4, color);
        InsertAction("���m", 0, color);
        InsertAction("�m��", 3, color);
        InsertAction("����", 2, color);
        InsertAction("���m����", 0, color);
        InsertAction("����1", 4, color);
        InsertAction("����2", 4, color);
        InsertAction("����3", 4, color);
        InsertAction("�W��", 4, color);
        InsertAction("�W�S��", 3, color);
        InsertAction("�U��", 5, color);
        InsertAction("�S��1", 5, color);
        InsertAction("�Ŵ�1", 4, color);
        InsertAction("�Ŵ�2", 4, color);
        InsertAction("�ŤU��", 7, color);
        InsertAction("�ŤW��", 7, color);
        InsertAction("�Ĩ봶", 0, color);
        InsertAction("�Ĩ�S��", 1, color);
        InsertAction("�j��", 6, color);

        //LoadEffects
        Effects.AutoLoadEffections(color);
        //LoadAttacks
        AutoLoadAttacks(GPP);
        AnimationUpdate(Camera);
    }

    //���U��������
    void Matchstick::AutoLoadAttacks(GPH)
    {

        Attacks.InsertAttacks(GetName(), "Normal1", 0, 5, 16, 0, color, Camera);
        Attacks.InsertAttacks(GetName(), "Normal2", 0, 5, 16, 0, color, Camera);
        Attacks.InsertAttacks(GetName(), "Normal3", 0, 5, 16, 0, color, Camera);
        Attacks.InsertAttacks(GetName(), "Normal4", 0, 5, 16, 0, color, Camera);
        Attacks.InsertAttacks(GetName(), "Normal5", 0, 5, 16, 0, color, Camera);
        Attacks.InsertAttacks(GetName(), "Normal6", 0, 5, 16, 0, color, Camera);
        Attacks.InsertAttacks(GetName(), "Normal7", 0, 5, 16, 0, color, Camera);
        Attacks.InsertAttacks(GetName(), "RushSkill", 2, 5, 8, 0, color, Camera);
        Attacks.InsertAttacks(GetName(), "UpSkill", 2, 5, 8, 0, 1, color, Camera);
        Attacks.InsertAttacks(GetName(), "Counterattact", 4, 5, 20, 0, color, Camera);
        Attacks.InsertAttacks(GetName(), "Skill1", 2, 5, 20, 0, 5, color, Camera);//�h�@�ӰѼƬO�㦳�s����
    }

    //���U�ʧ@�b��
    void Matchstick::OnUpdate(GPH)
    {

        InputJudge(KeyState_now, KeyState_last);
        CheckHit(GPP);
        OnStandby(GPP);
        OnRunning(GPP);
        OnRush(GPP);
        OnJump(GPP);
        OnGuard(GPP);
        OnCharge(GPP);
        OnHit(GPP);
        OnHitGuard(GPP);
        OnNormalAttack1(GPP);
        OnNormalAttack2(GPP);
        OnNormalAttack3(GPP);
        OnSkill1(GPP);
        OnAirAttack1(GPP);
        OnAirAttack2(GPP);
        OnAirDownAttack(GPP);
        OnAirUpAttack(GPP);
        OnDownAttack(GPP);
        OnUpAttack(GPP);
        OnRushAttack(GPP);
        OnRushSkill(GPP);
        OnUpSkill(GPP);
        OnUltimateSkill(GPP);
        //��s�Ҧ�Effect���ʧ@
        map<string, BitmapAnimation>::iterator Iter_Effect;
        for (Iter_Effect = Effects.Content.begin(); Iter_Effect != Effects.Content.end(); Iter_Effect++)
            Effects.EffectAutoUpdate(&(Iter_Effect->second), (int)(((Iter_Effect->second).PreAutoFrequence)), (Iter_Effect->second).loop, Camera);

        //��s�Ҧ�Attacks���ʧ@
        map<string, AttackObj>::iterator Iter_Attack;
        for (Iter_Attack = Attacks.AttackObjects.begin(); Iter_Attack != Attacks.AttackObjects.end(); Iter_Attack++)
            Attacks.AttackAutoUpdate(&(Iter_Attack->second), GetName(), (int)(((Iter_Attack->second).PreAutoFrequence)), (Iter_Attack->second).Replay, Camera);


        this->PhysicalMovement(GPP);
        AnimationUpdate(Camera);

        //����
        ProduceBreakPoint(GPP);
        ProduceRecovery(GPP);
        CheckPerfectBlock(GPP);

        #pragma region �ҥ~���p

        if (!(Action == "�j��"))
        {
            Effects.Content["OraOraFire"].visable = false;
        }
        if (!(Action == "�Ĩ�S��"))
        {
            Attacks.AttackObjects["RushSkill"].visable = false;
        }
        #pragma endregion



    }

    void Matchstick::GotoRush(GPH)
    {
        if (SP >= Rush_cost)
        {
            GainSP(-Rush_cost);
            Action = "�Ĩ�";
            Step = 0;
            RushTimer = 0;
        }
    }
    void Matchstick::OnRush(GPH)
    {
        if (Action == "�Ĩ�")
        {
            #pragma region �Ĩ�D�{��
            RushTimer += TIMER_TICK_MILLIDECOND;
            if (Step == 1)
                Velocity_Y = 0;
            if (RushTimer < 40 && Step == 0)
                Velocity_X = 0;
            if (RushTimer >= 40 && Step == 0)
            {
                RushTimer = 0;
                Step = 1;
                Effects.BootEffect(&Effects.Content["Airboost"], Camera, Rect.X, Rect.X + 30, Rect.Y - 30, 0, 0, false, IsRight);
                Throughing = true;
                PlaySounds(Sounds.Rush, false);
                if (IsRight)
                {
                    Velocity_X = 38;
                    Acceleration_X = -3.5;
                    Invincible = true;
                }
                else
                {
                    Velocity_X = -38;
                    Acceleration_X = +3.5;
                    Invincible = true;
                }
            }
            else if (RushTimer <= 80 && Step == 1)//�٨�
            {
                if (IsRight&&Velocity_X < 0)
                    Velocity_X = 0;
                else if (IsRight == false && Velocity_X > 0)
                    Velocity_X = 0;

                CanToRushAttack;
                CanToRushSkill;

            }
            #pragma endregion

            //���`����
            if (RushTimer > 80 && Step == 1)
            {
                RushTimer = 0;
                Throughing = false;
                Invincible = false;
                Velocity_X = 0;
                Acceleration_X = 0;

                #pragma region �^���S��
                Effects.Content["AirBoost"].Step = 0;
                Effects.Content["AirBoost"].visable = false;
                Effects.Content["AirBoost"].OnUpdate("Effects", Camera);
                #pragma endregion

                #pragma region �P�_���Ӧ^����Ӱʧ@
                if (OnGround)
                    GotoStandby(GPP);
                else
                    GotoDrop(GPP);
                #pragma endregion

            }

        }
    }

    void Matchstick::GotoNormalAttack1(GPH)
    {
        if (SP >= Matchstick_NormalAttack1_Cost)
        {
            GainSP(-Matchstick_NormalAttack1_Cost);
            Action = "����1";
            Step = 0;
            NormalAttack1Timer = 0;
        }
    }
    void Matchstick::OnNormalAttack1(GPH)
    {
        if (Action == "����1")
        {
            NormalAttack1Timer += TIMER_TICK_MILLIDECOND;

            #pragma region �ʧ@�D��
            //�B�z�����O
            ProduceFriction(1, 1);
            if (NormalAttack1Timer >= 16 && Step <= 2)
            {
                NormalAttack1Timer = 0;
                Step += 1;

                #pragma region ���ͧ�������
                //�X��
                if (Step >= 3)
                {
                    Velocity_X += Ahead(3.5);
                    Attacks.AttackReset_Normal(
                        &(Attacks.AttackObjects["Normal1"]), this, Enemy,
                        Matchstick_NormalAttack1_Damage,
                        2, 2, Rect.X + 108, Rect.X - 2, Rect.Y + 52, 0, 0,
                        120, 30, "PunchHit", Sounds.NormalHit, Camera);
                }
                #pragma endregion


            }
            else if (NormalAttack1Timer >= 40 && Step == 3)
            {
                NormalAttack1Timer = 0;
                Step = 4;
            }
            #pragma endregion

            #pragma region ��O���ʧ@
            if (NormalAttack1Timer < 100 && Step >= 4)
            {
                //��O���ʧ@
                CanToNormalAttack2;
                CanToSkill1;
                CanToJump;
                CanToRush;
                CanToUpAttack;
                CanToDownAttack;
                CanToUpSkill;
            }
            else if (NormalAttack1Timer >= 100 && Step >= 4)
            {
                //���`����
                GotoStandby(GPP);
            }
            #pragma endregion

        }
    }

    void Matchstick::GotoNormalAttack2(GPH)
    {
        if (SP >= Matchstick_NormalAttack2_Cost)
        {
            GainSP(-Matchstick_NormalAttack2_Cost);
            Action = "����2";
            Step = 0;
            NormalAttack1Timer = 0;
        }
    }
    void Matchstick::OnNormalAttack2(GPH)
    {
        if (Action == "����2")
        {
            NormalAttack1Timer += TIMER_TICK_MILLIDECOND;
            #pragma region �ʧ@�D��
            //�B�z�����O
            ProduceFriction(1, 1);
            if (NormalAttack1Timer >= 16 && Step <= 2)
            {
                NormalAttack1Timer = 0;
                Step += 1;
                if (Step >= 3)
                {
                    Velocity_X += Ahead(3.5);
                    #pragma region ���ͧ�������
                    //�X��
                    Attacks.AttackReset_Normal(
                        &(Attacks.AttackObjects["Normal1"]), this, Enemy,
                        Matchstick_NormalAttack2_Damage,
                        3.5, 2, Rect.X + 108, Rect.X - 2, Rect.Y + 52, 0, 0,
                        120, 30, "PunchHit", Sounds.NormalHit, Camera);
                    #pragma endregion
                }
            }
            else if (NormalAttack1Timer >= 50 && Step == 3)
            {
                NormalAttack1Timer = 0;
                Step = 4;
            }
            #pragma endregion

            #pragma region ��O���ʧ@
            if (NormalAttack1Timer < 100 && Step >= 4)
            {
                //��O���ʧ@
                CanToNormalAttack3;
                CanToSkill1;
                CanToJump;
                CanToRush;
                CanToUpAttack;
                CanToDownAttack;
                CanToUpSkill;

            }
            else if (NormalAttack1Timer >= 100 && Step >= 4)
            {
                //���`����
                GotoStandby(GPP);
            }
            #pragma endregion






        }
    }

    void Matchstick::GotoNormalAttack3(GPH)
    {
        if (SP >= Matchstick_NormalAttack3_Cost)
        {
            GainSP(-Matchstick_NormalAttack3_Cost);
            Velocity_X += Ahead(5);
            Velocity_Y -= 5;
            Action = "����3";
            Step = 0;
            NormalAttack1Timer = 0;
        }
    }
    void Matchstick::OnNormalAttack3(GPH)
    {
        if (Action == "����3")
        {
            NormalAttack1Timer += TIMER_TICK_MILLIDECOND;
            #pragma region �ʧ@�D��
            ProduceFriction(0.2, 0.25);
            if (NormalAttack1Timer >= 84 && Step <= 2)
            {
                Step += 1;
                if (Step >= 3)
                {
                    #pragma region ���ͧ�������
                    //�򥻳]�w
                    Attacks.AttackReset_Normal(
                        &(Attacks.AttackObjects["Normal2"]), this, Enemy,
                        Matchstick_NormalAttack3_Damage,
                        12, 7.5, Rect.X + 147, Rect.X - 7, Rect.Y + 25, 0, 0,
                        200, 30, "PunchHit", Sounds.NormalHit, Camera);
                    //�B�~�]�w
                    Attacks.AttackObjects["Normal2"].CanHitFly = true;

                    #pragma endregion
                }
            }
            else if (NormalAttack1Timer >= 150 && Step == 3)
            {
                NormalAttack1Timer = 0;
                Step = 4;
            }
            #pragma endregion

            #pragma region ��O���ʧ@
            if (NormalAttack1Timer < 100 && Step >= 4)
            {
                CanToJump;
                CanToRush;
            }
            else if (NormalAttack1Timer >= 100 && Step >= 4)
            {
                //���`����
                GotoStandby(GPP);
            }
            #pragma endregion

        }
    }

    void Matchstick::GotoSkill1(GPH)
    {
        if (SP >= Matchstick_Skill1_Cost)
        {
            GainSP(-Matchstick_Skill1_Cost);
            if (Velocity_Y > 0 && OnGround == false)
                Velocity_Y = 0;
            Action = "�S��1";
            Step = 0;
            Shot1Timer = 0;
        }
    }
    void Matchstick::OnSkill1(GPH)
    {
        if (Action == "�S��1")
        {

            Shot1Timer += TIMER_TICK_MILLIDECOND;

            #pragma region �ʧ@�D��
            if (OnGround)
                ProduceFriction(1, 1);
            else
                ProduceFriction(0.15, 0.75);
            if (Shot1Timer >= 50 && Step == 0)
            {
                Step = 1;
                if (Velocity_Y > 0 && OnGround == false)
                    Velocity_Y = 0;
            }
            if (Shot1Timer >= 16 && Step >= 1 && Step <= 3)
            {
                if (Shot1Current >= 5)
                    Shot1Current = 0;
                Shot1Timer = 0;
                Step += 1;
                if (Step == 3)
                {
                    #pragma region ���ͧ�������
                    //�X��
                    Attacks.AttackReset_Shot(&(Attacks.AttackObjects["Skill1_" + IntToString(Shot1Current)]), this, Enemy,
                        Rina_DownSkill_Damage,
                        2, 3.5,
                        Rect.X + 75, Rect.X + 10, Rect.Y + 52, Ahead(4.5), 0,
                        120, 1000, 2,
                        true, true, true,
                        "PunchHit", Sounds.NormalHit, Camera);
                    Shot1Current += 1;

                    #pragma endregion
                }
            }
            else if (Shot1Timer >= 50 && Step == 4)
            {
                Shot1Timer = 0;
                Step = 5;
            }
            #pragma endregion

            #pragma region ��O���ʧ@
            if (Shot1Timer < 100 && Step >= 5)
            {
                //��O���i��ʧ@
                if (OnGround)
                {
                    CanToNormalAttack1;
                    CanToUpAttack;
                    CanToDownAttack;
                    CanToUpSkill;
                }
                else
                {
                    CanToAirUpAttack;
                    CanToAirDownAttack;
                    CanToAirAttack1;
                    CanToFastDrop;
                }

                CanToRush;
                CanToJump;
            }
            else if (Shot1Timer >= 100 && Step >= 5)
            {
                //���`����
                if (OnGround)
                    GotoStandby(GPP);
                else
                    GotoDrop(GPP);
            }
            #pragma endregion

        }
    }

    void Matchstick::GotoAirAttack1(GPH)
    {
        if (SP >= Matchstick_AirAttack1_Cost)
        {
            GainSP(-Matchstick_AirAttack1_Cost);
            Action = "�Ŵ�1";
            Step = 0;
            if (Velocity_Y > 0)
            {
                Velocity_Y = 0;
            }
            NormalAttack1Timer = 0;
        }
    }
    void Matchstick::OnAirAttack1(GPH)
    {
        if (Action == "�Ŵ�1")
        {

            NormalAttack1Timer += TIMER_TICK_MILLIDECOND;

            #pragma region ���k����
            if (CanControl&&Button_now.button_Right == false && CanControl&&Button_now.button_Left == false)
            {
                ProduceFriction(0.15, 1);
            }
            else if (CanControl&&Button_now.button_Right == true)
            {
                IsRight = true;
                RunAhead(0.5, RunSpeed / 2);
            }
            else if (CanControl&&Button_now.button_Left == true)
            {
                IsRight = false;
                RunAhead(0.5, RunSpeed / 2);
            }
            #pragma endregion

            #pragma region �ʧ@�D��
            if (NormalAttack1Timer >= 50 && Step == 0)
            {
                Step = 1;
            }
            if (NormalAttack1Timer >= 16 && Step >= 1 && Step <= 3)
            {
                NormalAttack1Timer = 0;
                Step += 1;
                #pragma region ���ͧ�������
                if (Step == 3)
                {
                    //�X��
                    Attacks.AttackReset_Normal(
                        &(Attacks.AttackObjects["Normal3"]), this, Enemy,
                        Matchstick_AirAttack1_Damage,
                        2, 5, Rect.X + 108, Rect.X - 2, Rect.Y + 90, Velocity_X / 3, 0,
                        150, 30, "PunchHit", Sounds.NormalHit, Camera);
                }
                #pragma endregion
            }
            else if (NormalAttack1Timer >= 125 && Step == 3)
            {
                NormalAttack1Timer = 0;
                Step = 4;
            }
            #pragma endregion

            #pragma region ��O���ʧ@
            if (NormalAttack1Timer < 125 && Step >= 4)
            {
                //��O���i��ʧ@
                CanToAirAttack2;
                CanToSkill1;
                CanToRush;
                CanToAirDownAttack;
                CanToAirUpAttack;
                CanToJump;
                CanToFastDrop;
            }
            else if (NormalAttack1Timer >= 125 && Step >= 4)
            {
                //���`����
                if (OnGround)
                    GotoStandby(GPP);
                else
                    GotoDrop(GPP);
            }
            #pragma endregion

        }
    }

    void Matchstick::GotoAirAttack2(GPH)
    {
        if (SP >= Matchstick_AirAttack2_Cost)
        {
            GainSP(-Matchstick_AirAttack2_Cost);
            Action = "�Ŵ�2";
            Step = 0;
            Velocity_X += Ahead(4);
            Velocity_Y = -3.5;
            NormalAttack1Timer = 0;
        }
    }
    void Matchstick::OnAirAttack2(GPH)
    {
        if (Action == "�Ŵ�2")
        {
            ProduceFriction(0.1, 0.15);
            NormalAttack1Timer += TIMER_TICK_MILLIDECOND;
            if (NormalAttack1Timer >= 84 && Step <= 2)
            {
                Step += 1;
                if (Step >= 3)
                {
                    //��¦�]�w
                    Attacks.AttackReset_Normal(
                        &(Attacks.AttackObjects["Normal2"]), this, Enemy,
                        Matchstick_AirAttack2_Damage,
                        12, 7.5, Rect.X + 142, Rect.X, Rect.Y + 60, Velocity_X / 3, 0,
                        250, 50, "PunchHit", Sounds.NormalHit, Camera);
                    //�B�~�]�w
                    Attacks.AttackObjects["Normal2"].CanHitFly = true;
                }
            }
            else if (NormalAttack1Timer >= 150 && Step == 3)
            {
                NormalAttack1Timer = 0;
                Step = 4;
            }
            else if (NormalAttack1Timer < 100 && Step >= 4)
            {
                //��O���ʧ@
            }
            else if (NormalAttack1Timer >= 100 && Step >= 4)
            {
                //���`����
                if (OnGround)
                    GotoStandby(GPP);
                else
                    GotoDrop(GPP);
            }

        }
    }

    void Matchstick::GotoUpAttack(GPH)
    {
        if (SP >= Matchstick_UpAttack_Cost)
        {
            GainSP(-Matchstick_UpAttack_Cost);
            Action = "�W��";
            Step = 0;
            NormalAttack1Timer = 0;
        }
    }
    void Matchstick::OnUpAttack(GPH)
    {
        if (Action == "�W��")
        {
            NormalAttack1Timer += TIMER_TICK_MILLIDECOND;

            #pragma region �ʧ@�D��
            //�B�z�����O
            ProduceFriction(1, 1);
            if (NormalAttack1Timer >= 80 && Step == 0)
            {
                NormalAttack1Timer = 0;
                Step = 1;
            }
            else if (NormalAttack1Timer >= 16 && Step >= 1 && Step <= 2)
            {
                NormalAttack1Timer = 0;
                Step += 1;
                #pragma region ���ͧ�������
                //�X��
                if (Step == 3)
                {
                    Velocity_X += Ahead(7);
                    //��¦�]�w
                    Attacks.AttackReset_Normal(
                        &(Attacks.AttackObjects["Normal2"]), this, Enemy,
                        Matchstick_UpAttack_Damage,
                        2, 12, Rect.X + 147, Rect.X - 7, Rect.Y + 25, 0, 0,
                        220, 30, "PunchHit", Sounds.NormalHit, Camera);
                }
                #pragma endregion
            }
            else if (NormalAttack1Timer >= 40 && Step == 3)
            {
                NormalAttack1Timer = 0;
                Step = 4;
            }
            #pragma endregion

            #pragma region ��O���ʧ@
            if (NormalAttack1Timer < 100 && Step >= 4)
            {
                //��O���ʧ@
                CanToNormalAttack1;
                CanToSkill1;
                CanToJump;
                CanToRush;
                CanToDownAttack;
                CanToUpSkill;
            }
            else if (NormalAttack1Timer >= 100 && Step >= 4)
            {
                //���`����
                GotoStandby(GPP);
            }
            #pragma endregion

        }
    }

    void Matchstick::GotoDownAttack(GPH)
    {
        if (SP >= Matchstick_DownAttack_Cost)
        {
            GainSP(-Matchstick_DownAttack_Cost);
            Action = "�U��";
            Step = 0;
            NormalAttack1Timer = 0;
        }
    }
    void Matchstick::OnDownAttack(GPH)
    {
        if (Action == "�U��")
        {
            NormalAttack1Timer += TIMER_TICK_MILLIDECOND;

            #pragma region �ʧ@�D��
            //�B�z�����O
            ProduceFriction(1, 1);
            if (NormalAttack1Timer >= 110 && Step == 0)
            {
                NormalAttack1Timer = 0;
                Step = 1;
            }
            else if (NormalAttack1Timer >= 16 && Step >= 1 && Step <= 3)
            {
                NormalAttack1Timer = 0;
                Step += 1;
                #pragma region ���ͧ�������
                //�X��
                if (Step >= 4)
                {
                    Velocity_X += Ahead(3.5);
                    Attacks.AttackReset_Normal(
                        &(Attacks.AttackObjects["Normal1"]), this, Enemy,
                        Matchstick_DownAttack_Damage,
                        2, 3, Rect.X + 111, Rect.X, Rect.Y + 52, 0, 0,
                        200, 30, "PunchHit", Sounds.NormalHit, Camera);
                    Attacks.AttackObjects["Normal1"].HitBreak = true;
                }
                #pragma endregion
            }
            else if (NormalAttack1Timer >= 40 && Step == 4)
            {
                NormalAttack1Timer = 0;
                Step = 5;
            }
            #pragma endregion

            #pragma region ��O���ʧ@
            if (NormalAttack1Timer < 100 && Step >= 5)
            {
                //��O���ʧ@
                CanToNormalAttack1;
                CanToSkill1;
                CanToJump;
                CanToRush;
                CanToUpSkill;
            }
            else if (NormalAttack1Timer >= 100 && Step >= 5)
            {
                //���`����
                GotoStandby(GPP);
            }
            #pragma endregion

        }
    }

    void Matchstick::GotoRushAttack(GPH)
    {
        if (SP >= Matchstick_RushAttack_Cost)
        {
            GainSP(-Matchstick_RushAttack_Cost);
            if (Velocity_Y > 0 && OnGround == false)
                Velocity_Y = 0;
            RushTimer = 0;
            IsRushAttack = false;
            Throughing = false;
            Invincible = false;
            Velocity_X = 0;
            Acceleration_X = 0;
            Action = "�Ĩ봶";
            Step = 0;
            NormalAttack1Timer = 0;
        }
    }
    void Matchstick::OnRushAttack(GPH)
    {
        if (Action == "�Ĩ봶")
        {

            NormalAttack1Timer += TIMER_TICK_MILLIDECOND;

            #pragma region �ʧ@�D��
            if (NormalAttack1Timer <= 140 && Step == 0)
            {
                Velocity_Y = 0;
                Acceleration_X = Ahead(1.2);
                if (abs(Velocity_X) > 12)
                {
                    Velocity_X = Ahead(12);
                }
                #pragma region ��s���������m
                if (IsRight)
                    Attacks.AttackObjects["Normal6"].Rect.X = Rect.X + 60;
                else
                    Attacks.AttackObjects["Normal6"].Rect.X = Rect.X - 10;
                Attacks.AttackObjects["Normal6"].Rect.Y = Rect.Y + 35;
                if (Attacks.AttackObjects["Normal6"].IsHited&&Attacks.AttackObjects["Normal6"].ComboTimer > TIMER_TICK_MILLIDECOND * 2)
                {
                    Attacks.AttackObjects["Normal6"].ComboTimer = 0;
                    Attacks.AttackObjects["Normal6"].IsHited = false;
                }
                #pragma endregion

                #pragma region ���ͧ�������
                if (IsRushAttack == false)
                {
                    IsRushAttack = true;
                    //��¦�]�w
                    Attacks.AttackReset_Normal(
                        &(Attacks.AttackObjects["Normal6"]), this, Enemy,
                        Matchstick_RushAttack_Damage,
                        8.5, 1, Rect.X + 98, 0, 0, 0, 0,
                        50, 100, "PunchHit", Sounds.NormalHit, Camera);
                    //�B�~�]�w
                    Attacks.AttackObjects["Normal6"].CanCombo = true;//�i�s��
                    Attacks.AttackObjects["Normal6"].HitNoon = false;
                }
                #pragma endregion
            }
            #pragma endregion

            #pragma region ��O���ʧ@
            if (NormalAttack1Timer > 140 && Step == 0)
            {
                Acceleration_X = 0;
                Velocity_X = 0;
                #pragma region �P�_���Ӧ^����Ӱʧ@
                if (OnGround)
                    GotoStandby(GPP);
                else
                    GotoDrop(GPP);
                #pragma endregion
            }
            #pragma endregion

        }
    }

    void Matchstick::GotoAirUpAttack(GPH)
    {
        if (SP >= Matchstick_AirUpAttack_Cost)
        {
            GainSP(-Matchstick_AirUpAttack_Cost);
            Action = "�ŤW��";
            Step = 0;
            if (Velocity_Y > 0)
                Velocity_Y = 0;
            NormalAttack1Timer = 0;
        }
    }
    void Matchstick::OnAirUpAttack(GPH)
    {
        if (Action == "�ŤW��")
        {
            #pragma region ���k����
            if (CanControl&&Button_now.button_Right == false && CanControl&&Button_now.button_Left == false)
            {
                ProduceFriction(0.15, 1);
            }
            else if (CanControl&&Button_now.button_Right == true)
            {
                IsRight = true;
                RunAhead(0.5, RunSpeed / 2);
            }
            else if (CanControl&&Button_now.button_Left == true)
            {
                IsRight = false;
                RunAhead(0.5, RunSpeed / 2);
            }
            #pragma endregion

            #pragma region �ʧ@�D��
            NormalAttack1Timer += TIMER_TICK_MILLIDECOND;
            if (NormalAttack1Timer >= 100 && Step == 0)
            {
                Step = 1;
                if (Velocity_Y > 1)
                    Velocity_Y = 1;
            }
            if (NormalAttack1Timer >= 16 && Step >= 1 && Step <= 3)
            {
                NormalAttack1Timer = 0;
                Step += 1;
                Velocity_Y = -6;

                #pragma region ���ͧ�������
                if (Step == 2)
                {
                    //��¦�]�w
                    Attacks.AttackReset_Normal(
                        &(Attacks.AttackObjects["Normal5"]), this, Enemy,
                        Matchstick_AirUpAttack_Damage,
                        2.5, 12, Rect.X + 20, Rect.X, Rect.Y, Velocity_X / 4, 0,
                        250, 30, "PunchHit", Sounds.NormalHit, Camera);
                }
                #pragma endregion

            }
            else if (NormalAttack1Timer >= 16 && Step >= 4 && Step <= 6)
            {
                if (Velocity_Y > 2)
                    Velocity_Y = 2;
                NormalAttack1Timer = 0;
                Step += 1;
            }
            #pragma endregion

            #pragma region ��O���ʧ@
            if (NormalAttack1Timer < 100 && Step >= 7)
            {
                if (Velocity_Y > 1)
                    Velocity_Y = 1;
                //��O���i��ʧ@
                CanToSkill1;
                CanToRush;
                CanToJump;
                CanToAirAttack1;
                CanToAirDownAttack;
                CanToFastDrop;
            }
            else if (NormalAttack1Timer >= 100 && Step >= 7)
            {
                //���`����
                if (OnGround)
                    GotoStandby(GPP);
                else
                    GotoDrop(GPP);
            }
            #pragma endregion
        }
    }

    void Matchstick::GotoAirDownAttack(GPH)
    {
        if (SP >= Matchstick_AirDownAttack_Cost)
        {
            GainSP(-Matchstick_AirDownAttack_Cost);
            Action = "�ŤU��";
            Step = 0;
            if (Velocity_Y > 0)
                Velocity_Y = 0;
            NormalAttack1Timer = 0;
        }
    }
    void Matchstick::OnAirDownAttack(GPH)
    {
        if (Action == "�ŤU��")
        {
            NormalAttack1Timer += TIMER_TICK_MILLIDECOND;

            #pragma region ���k����
            if (CanControl&&Button_now.button_Right == false && CanControl&&Button_now.button_Left == false)
            {
                ProduceFriction(0.15, 1);
            }
            else if (CanControl&&Button_now.button_Right == true)
            {
                IsRight = true;
                RunAhead(0.5, RunSpeed / 2);
            }
            else if (CanControl&&Button_now.button_Left == true)
            {
                IsRight = false;
                RunAhead(0.5, RunSpeed / 2);
            }
            #pragma endregion

            #pragma region �ʧ@�D��
            if (NormalAttack1Timer >= 75 && Step == 0)
            {
                if (Velocity_Y > 1)
                    Velocity_Y = 1;
                Step = 1;
            }
            if (NormalAttack1Timer >= 8 && Step >= 1 && Step <= 3)
            {
                NormalAttack1Timer = 0;
                Step += 1;
            }
            else if (NormalAttack1Timer >= 20 && Step >= 4 && Step <= 6)
            {
                NormalAttack1Timer = 0;
                Step += 1;
                #pragma region ���ͧ�������
                if (Step == 5)
                {
                    //��¦�]�w
                    Attacks.AttackReset_Normal(
                        &(Attacks.AttackObjects["Normal4"]), this, Enemy,
                        Matchstick_AirDownAttack_Damage,
                        2.5, -16, Rect.X + 90, Rect.X, Rect.Y + 20, Velocity_X / 2, Velocity_Y / 3,
                        200, 30, "PunchHit", Sounds.NormalHit, Camera);
                }
                #pragma endregion
            }
            #pragma endregion

            #pragma region ��O���ʧ@
            if (NormalAttack1Timer > 50 && NormalAttack1Timer < 120 && Step >= 7)
            {
                if (Velocity_Y > 1)
                    Velocity_Y = 1;
                //��O���i��ʧ@
                CanToSkill1;
                CanToRush;
                CanToJump;
                CanToFastDrop;
            }
            else if (NormalAttack1Timer >= 120 && Step >= 7)
            {
                //���`����
                if (OnGround)
                    GotoStandby(GPP);
                else
                    GotoDrop(GPP);
            }
            #pragma endregion
        }
    }

    void Matchstick::GotoUpSkill(GPH)
    {
        if (SP >= Matchstick_UpSkill_Cost)
        {
            GainSP(-Matchstick_UpSkill_Cost);
            Action = "�W�S��";
            Step = 0;
            NormalAttack1Timer = 0;
        }
    }
    void Matchstick::OnUpSkill(GPH)
    {
        if (Action == "�W�S��")
        {
            NormalAttack1Timer += TIMER_TICK_MILLIDECOND;

            #pragma region �ʧ@�D��
            //�B�z�����O
            ProduceFriction(1, 1);
            if (NormalAttack1Timer >= 150 && Step == 0)
            {
                NormalAttack1Timer = 0;
                Step = 1;
            }
            else if (NormalAttack1Timer >= 16 && Step >= 1 && Step <= 2)
            {
                NormalAttack1Timer = 0;
                Step += 1;

                #pragma region ���ͧ�������
                //�X��
                if (Step == 3)
                {
                    PlaySounds(Sounds.Fire1, false);
                    //��¦�]�w
                    Attacks.AttackReset_Shot(&(Attacks.AttackObjects["UpSkill_" + IntToString(UpSkillCurrent)]), this, Enemy,
                        Matchstick_UpSkill_Damage,
                        1, 5,
                        Rect.X, Rect.X, Rect.Y + 17, 0, -9,
                        50, 400, 5,
                        true, true, true,
                        "PunchHit", Sounds.NormalHit, Camera);
                    //�B�~�]�w
                    Attacks.AttackObjects["UpSkill_" + IntToString(UpSkillCurrent)].Drawable = true;
                    Attacks.AttackObjects["UpSkill_" + IntToString(UpSkillCurrent)].HitBreak = false;
                    Attacks.AttackObjects["UpSkill_" + IntToString(UpSkillCurrent)].HitNoon = false;
                    Attacks.AttackObjects["UpSkill_" + IntToString(UpSkillCurrent)].CanCombo = true;
                    UpSkillCurrent = 0;
                }
                #pragma endregion
            }
            #pragma endregion

            #pragma region ��O���ʧ@
            if (NormalAttack1Timer >= 40 && NormalAttack1Timer < 100 && Step >= 3)
            {
                //��O���ʧ@
                CanToNormalAttack1;
                CanToSkill1;
                CanToJump;
                CanToRush;
                CanToDownAttack;
            }
            else if (NormalAttack1Timer >= 100 && Step >= 3)
            {
                //���`����
                GotoStandby(GPP);
            }
            #pragma endregion

        }
    }

    void Matchstick::GotoDownSkill(GPH)
    {
    }
    void Matchstick::OnDownSkill(GPH)
    {
    }

    void Matchstick::GotoRushSkill(GPH)
    {
        if (SP >= Matchstick_RushSkill_Cost)
        {
            GainSP(-Matchstick_RushSkill_Cost);
            if (Velocity_Y > 0 && OnGround == false)
                Velocity_Y = 0;
            RushTimer = 0;
            IsRushAttack = false;
            Throughing = true;
            Invincible = false;
            Velocity_X = 0;
            Acceleration_X = 0;
            Action = "�Ĩ�S��";
            Step = 0;
            NormalAttack1Timer = 0;
        }
    }
    void Matchstick::OnRushSkill(GPH)
    {
        if (Action == "�Ĩ�S��")
        {

            NormalAttack1Timer += TIMER_TICK_MILLIDECOND;

            #pragma region �ʧ@�D��
            if (NormalAttack1Timer <= 150 && Step == 0)
            {
                Velocity_Y = -4;
                Velocity_X = Ahead(2.5);
            }
            else if (NormalAttack1Timer > 150 && Step == 0)
            {
                Step = 1;
                NormalAttack1Timer = 0;
            }
            if (NormalAttack1Timer <= 200 && Step == 1)
            {
                Velocity_Y = 0;
                Acceleration_X = Ahead(4);
                if (abs(Velocity_X) > 15)
                {
                    Velocity_X = Ahead(15);
                }
                #pragma region ��s���������m
                if (IsRight)
                    Attacks.AttackObjects["RushSkill"].Rect.X = Rect.X - 47;
                else
                    Attacks.AttackObjects["RushSkill"].Rect.X = Rect.X - 15;
                Attacks.AttackObjects["RushSkill"].Rect.Y = Rect.Y + 0;

                if (Attacks.AttackObjects["RushSkill"].IsHited&&Attacks.AttackObjects["RushSkill"].ComboTimer > TIMER_TICK_MILLIDECOND * 4)
                {
                    Attacks.AttackObjects["RushSkill"].ComboTimer = 0;
                    Attacks.AttackObjects["RushSkill"].IsHited = false;
                }

                #pragma endregion

                #pragma region ���ͧ�������
                if (IsRushAttack == false)
                {
                    IsRushAttack = true;
                    PlaySounds(Sounds.Fire1, false);
                    //��¦�]�w
                    Attacks.AttackReset_Shot(&(Attacks.AttackObjects["RushSkill"]), this, Enemy,
                        Matchstick_RushSkill_Damage,
                        12, 5,
                        Rect.X - 47, Rect.X - 15, Rect.Y, 0, 0,
                        250, 200, 5,
                        true, true, true,
                        "PunchHit", Sounds.NormalHit, Camera);

                    //�B�~�]�w
                    Attacks.AttackObjects["RushSkill"].Drawable = true;
                    Attacks.AttackObjects["RushSkill"].HitBreak = false;
                    Attacks.AttackObjects["RushSkill"].HitNoon = false;
                    Attacks.AttackObjects["RushSkill"].CanCombo = true;
                }
                #pragma endregion
            }

            #pragma endregion

            #pragma region ��O���ʧ@
            if ((NormalAttack1Timer > 200) && Step == 1)
            {
                Throughing = false;
                Acceleration_X = 0;
                Velocity_X /= 2;
                #pragma region �P�_���Ӧ^����Ӱʧ@
                if (OnGround)
                    GotoStandby(GPP);
                else
                    GotoDrop(GPP);
                #pragma endregion
            }
            #pragma endregion

        }
    }

    void Matchstick::GotoAirUpSkill(GPH)
    {
    }
    void Matchstick::OnAirUpSkill(GPH)
    {
    }

    void Matchstick::GotoAirDownSkill(GPH)
    {
    }
    void Matchstick::OnAirDownSkill(GPH)
    {
    }

    void Matchstick::GotoUltimateSkill(GPH)
    {
        if (SP > (SP_Max / 3))
        {
            UltraSkillcostSP = SP - (SP_Max / 3);
            SP = 0;
            Action = "�j��";
            Step = 0;
            NormalAttack1Timer = 0;
            UltraSkillTimer1 = 0;
        }
    }
    void Matchstick::OnUltimateSkill(GPH)
    {
        if (Action == "�j��")
        {

            NormalAttack1Timer += TIMER_TICK_MILLIDECOND;
            UltraSkillTimer1 += TIMER_TICK_MILLIDECOND;
            #pragma region �ʧ@�D��
            //�B�z�����O
            ProduceFriction(1, 1);
            if (NormalAttack1Timer >= 300 && Step == 0)
            {
                PlaySounds(Sounds.CutIn, false);
                NeedCutIn = true;
                NormalAttack1Timer = 0;
                Step = 1;
                Effects.BootEffect(&Effects.Content["Matchstick_US"], Camera, 800, 800, 0, 0, 0, false, true);
                Effects.BootEffect(&Effects.Content["OraOraFire"], Camera, Rect.X + 60, Rect.X - 60, Rect.Y, 0, 0, false, IsRight);
                Effects.Content["OraOraFire"].loop = true;
            }
            if (Step >= 1 && Step <= 5 && NormalAttack1Timer >= 40)
            {
                if (IsRight)
                    Effects.Content["OraOraFire"].Rect.X = Rect.X + 60;
                else
                    Effects.Content["OraOraFire"].Rect.X = Rect.X - 60;
                Effects.Content["OraOraFire"].Rect.Y = Rect.Y;
                Effects.Content["OraOraFire"].visable = true;
                NormalAttack1Timer = 0;
                Step += 1;
                if (Step > 5)
                {
                    Step = 1;
                }
                #pragma region ���ͧ�������
                Attacks.AttackReset_Normal(
                    &(Attacks.AttackObjects["Normal7"]), this, Enemy,
                    Matchstick_UltimateSkill_Damage1*(1 + (UltraSkillcostSP / SP_Max)),
                    0, 0.75, Rect.X + 60, Rect.X - 60, Rect.Y, 0, 0,
                    100, 30, "PunchHit", Sounds.NormalHit2, Camera);
                #pragma endregion
            }
            if (UltraSkillTimer1 >= 1200 && Step < 6)
            {
                Step = 6;
                Attacks.AttackReset_Normal(
                    &(Attacks.AttackObjects["Normal7"]), this, Enemy,
                    Matchstick_UltimateSkill_Damage2*(1 + (UltraSkillcostSP / SP_Max)),
                    15, 10, Rect.X + 60, Rect.X - 60, Rect.Y, 0, 0,
                    200, 30, "PunchHit", Sounds.Stoned, Camera);
                Attacks.AttackObjects["Normal7"].CanHitFly = true;
                Attacks.AttackObjects["Normal7"].HitBreak = false;
                Effects.Content["OraOraFire"].visable = false;
                Effects.Content["OraOraFire"].loop = false;
            }

            if (Step == 6 && UltraSkillTimer1 > 1700)
            {
                GotoStandby(GPP);
            }

            #pragma endregion


        }
    }
    #pragma endregion

    #pragma region Rina
    Rina::Rina(int number) :BattlePlayer()
    {

        Restvalues(number);


    }
    Rina::~Rina()
    {

    }

    void Rina::Restvalues(int number)
    {
        //��O���ܼ�
        HP_Max = Rina_HP_Max;//�̤j�ͩR��
        SP_Max = Rina_SP_Max;//�̤j��O
        recovery = 0;
        Rush_cost = Rina_Rush_Cost;//�Ĩ���Ӷq
        StandbySPincrements = Rina_StandbySPincrements;
        RunningSPincrements = Rina_RunningSPincrements;
        RunSpeed = Rina_RunSpeed;
        ChargeSPincrements = Rina_ChargeSPincrements;
        //�{���ܼ�
        SetName("Rina");
        PlayerNumber = number;//���a�s��
        if (number == 1)
        {
            IsRight = true;
        }
        else if (number == 2)
        {
            IsRight = false;
        }
        HP = HP_Max;//��e�ͩR
        SP = SP_Max / 2;//��e��O
        CanControl = false;//�i�H����
        Invincible = false;//�L�Ī��A
        Action = "�ݾ�";//�ʧ@���A
        Step = 0;//��e�B�J��
        visable = true;//�O�_�i��
        CanPixelCollision = true;//�O�_�ϥι����I���A�Ҧ��ʧ@���γ��|�M��
        InSideCamera = true;//�O�_�������Y�v�T
        Velocity_X = 0;//X�t��
        Velocity_Y = 0;//Y�t��
        Acceleration_X = 0;//X�[�t��
        Acceleration_Y = 0;//Y�[�t��
        Throughing = false;
        HitFly = false;
        BreakPoint = 0;
        Acceleration_gravity = 0.5;

    }

    //Ū�ɦb��
    void Rina::AutoLoadBitmaps(GPH)
    {
        //���ħP�w��BitRect
        BodyPicture.LoadTexture(color);


        InsertAction("�ݾ�", 1, color);
        InsertAction("����", 7, color);
        InsertAction("���D", 4, color);
        InsertAction("���m", 0, color);
        InsertAction("�Ĩ�", 2, color);
        InsertAction("���m����", 0, color);
        InsertAction("����", 2, color);
        InsertAction("�m��", 4, color);
        InsertAction("����1", 4, color);
        InsertAction("����2", 4, color);
        InsertAction("����3", 6, color);
        InsertAction("�U�S��", 4, color);
        InsertAction("�Ĩ봶", 2, color);
        InsertAction("�S��", 5, color);
        InsertAction("�W�S��", 4, color);
        InsertAction("�W��", 5, color);
        InsertAction("�ŤU��", 2, color);
        InsertAction("�U��", 5, color);
        InsertAction("�j��", 2, color);

        //LoadEffects
        Effects.AutoLoadEffections(color);
        //LoadAttacks
        AutoLoadAttacks(GPP);
        AnimationUpdate(Camera);
    }

    //���U��������
    void Rina::AutoLoadAttacks(GPH)
    {

        Attacks.InsertAttacks(GetName(), "Normal1", 0, 5, 16, 0, color, Camera);
        Attacks.InsertAttacks(GetName(), "Normal2", 0, 5, 16, 0, color, Camera);
        Attacks.InsertAttacks(GetName(), "Normal3", 0, 5, 16, 0, color, Camera);
        Attacks.InsertAttacks(GetName(), "flashblade", 1, 5, 8, 0, 16, color, Camera);//�h�@�ӰѼƬO�㦳�s����
        Attacks.InsertAttacks(GetName(), "Bigflashblade", 0, 5, 8, 0, color, Camera);//�h�@�ӰѼƬO�㦳�s����
        Attacks.InsertAttacks(GetName(), "flashblade_H", 1, 5, 8, 0, 4, color, Camera);//�h�@�ӰѼƬO�㦳�s����
        Attacks.InsertAttacks(GetName(), "Counterattact", 4, 5, 20, 0, color, Camera);
    }

    //���U�ʧ@�b��
    void Rina::OnUpdate(GPH)
    {

        InputJudge(KeyState_now, KeyState_last);
        CheckHit(GPP);
        OnStandby(GPP);
        OnRunning(GPP);
        OnRush(GPP);
        OnJump(GPP);
        OnGuard(GPP);
        OnCharge(GPP);
        OnHit(GPP);
        OnHitGuard(GPP);
        OnNormalAttack1(GPP);
        OnNormalAttack2(GPP);
        OnNormalAttack3(GPP);
        OnSkill1(GPP);
        OnAirAttack1(GPP);
        OnAirAttack2(GPP);
        OnAirDownAttack(GPP);
        OnAirUpAttack(GPP);
        OnDownAttack(GPP);
        OnDownSkill(GPP);
        OnUpAttack(GPP);
        OnRushAttack(GPP);
        OnRushSkill(GPP);
        OnUpSkill(GPP);
        OnUltimateSkill(GPP);
        //��s�Ҧ�Effect���ʧ@
        map<string, BitmapAnimation>::iterator Iter_Effect;
        for (Iter_Effect = Effects.Content.begin(); Iter_Effect != Effects.Content.end(); Iter_Effect++)
            Effects.EffectAutoUpdate(&(Iter_Effect->second), (int)(((Iter_Effect->second).PreAutoFrequence)), (Iter_Effect->second).loop, Camera);

        //��s�Ҧ�Attacks���ʧ@
        map<string, AttackObj>::iterator Iter_Attack;
        for (Iter_Attack = Attacks.AttackObjects.begin(); Iter_Attack != Attacks.AttackObjects.end(); Iter_Attack++)
            Attacks.AttackAutoUpdate(&(Iter_Attack->second), GetName(), (int)(((Iter_Attack->second).PreAutoFrequence)), (Iter_Attack->second).Replay, Camera);


        this->PhysicalMovement(GPP);
        AnimationUpdate(Camera);

        //����
        ProduceBreakPoint(GPP);
        ProduceRecovery(GPP);
        CheckPerfectBlock(GPP);

        #pragma region �ҥ~���p

        #pragma region �U�S��
        if (useDownSkill)
        {
            DownSkillTimer2 += TIMER_TICK_MILLIDECOND;
            if (DownSkillTimer2 > 50)
            {
                PlaySounds(Sounds.light2, false);
                DownSkillTimer2 = 0;
                Attacks.AttackReset_Shot(&(Attacks.AttackObjects["flashblade_" + IntToString(DownSkillCurrent)]), this, Enemy,
                    Matchstick_UpSkill_Damage,
                    0, 0,
                    DownSkillXpoint + 60, DownSkillXpoint + 60, DownSkillYpoint - 150, 0, 2,
                    20, 750, 5,
                    true, true, true,
                    "PunchHit", Sounds.SliceHit, Camera);
                Attacks.AttackObjects["flashblade_" + IntToString(DownSkillCurrent)].HitNoon = false;
                Attacks.AttackObjects["flashblade_" + IntToString(DownSkillCurrent)].CanBeDisappear = false;
                Attacks.AttackObjects["flashblade_" + IntToString(DownSkillCurrent)].CanCrackOther = false;
                Attacks.AttackObjects["flashblade_" + IntToString(DownSkillCurrent)].UseRectCollision = true;
                //�B�~�]�w
                Attacks.AttackObjects["flashblade_" + IntToString(DownSkillCurrent)].GravityEffect = true;
                Attacks.AttackObjects["flashblade_" + IntToString(DownSkillCurrent)].Acceleration_gravity = 0.5;
                double Positions[] = { 0,30,-30,10,0,-60,80,-40,80,-10,-70,-25,10,-80,0,80 };
                if (DownSkillCurrent == 0)
                    Attacks.AttackObjects["flashblade_" + IntToString(DownSkillCurrent)].Rect.X += Positions[0];
                else if (DownSkillCurrent % 16 == 1)
                    Attacks.AttackObjects["flashblade_" + IntToString(DownSkillCurrent)].Rect.X += Positions[1];
                else if (DownSkillCurrent % 16 == 2)
                    Attacks.AttackObjects["flashblade_" + IntToString(DownSkillCurrent)].Rect.X += Positions[2];
                else if (DownSkillCurrent % 16 == 3)
                    Attacks.AttackObjects["flashblade_" + IntToString(DownSkillCurrent)].Rect.X += Positions[3];
                else if (DownSkillCurrent % 16 == 4)
                    Attacks.AttackObjects["flashblade_" + IntToString(DownSkillCurrent)].Rect.X += Positions[4];
                else if (DownSkillCurrent % 16 == 5)
                    Attacks.AttackObjects["flashblade_" + IntToString(DownSkillCurrent)].Rect.X += Positions[5];
                else if (DownSkillCurrent % 16 == 6)
                    Attacks.AttackObjects["flashblade_" + IntToString(DownSkillCurrent)].Rect.X += Positions[6];
                else if (DownSkillCurrent % 16 == 7)
                    Attacks.AttackObjects["flashblade_" + IntToString(DownSkillCurrent)].Rect.X += Positions[7];
                else if (DownSkillCurrent % 16 == 8)
                    Attacks.AttackObjects["flashblade_" + IntToString(DownSkillCurrent)].Rect.X += Positions[8];
                else if (DownSkillCurrent % 16 == 9)
                    Attacks.AttackObjects["flashblade_" + IntToString(DownSkillCurrent)].Rect.X += Positions[9];
                else if (DownSkillCurrent % 16 == 10)
                    Attacks.AttackObjects["flashblade_" + IntToString(DownSkillCurrent)].Rect.X += Positions[10];
                else if (DownSkillCurrent % 16 == 11)
                    Attacks.AttackObjects["flashblade_" + IntToString(DownSkillCurrent)].Rect.X += Positions[11];
                else if (DownSkillCurrent % 16 == 12)
                    Attacks.AttackObjects["flashblade_" + IntToString(DownSkillCurrent)].Rect.X += Positions[12];
                else if (DownSkillCurrent % 16 == 13)
                    Attacks.AttackObjects["flashblade_" + IntToString(DownSkillCurrent)].Rect.X += Positions[13];
                else if (DownSkillCurrent % 16 == 14)
                    Attacks.AttackObjects["flashblade_" + IntToString(DownSkillCurrent)].Rect.X += Positions[14];
                else if (DownSkillCurrent % 16 == 15)
                {
                    Attacks.AttackObjects["flashblade_" + IntToString(DownSkillCurrent)].Rect.X += Positions[15];
                    useDownSkill = false;
                    DownSkillCurrent = 0;
                }


                DownSkillCurrent += 1;
            }
            #pragma endregion




        }
        #pragma endregion



    }

    void Rina::GotoRush(GPH)
    {
        if (SP >= Rush_cost)
        {
            GainSP(-Rush_cost);
            Action = "�Ĩ�";
            Step = 0;
            RushTimer = 0;
        }
    }
    void Rina::OnRush(GPH)
    {
        if (Action == "�Ĩ�")
        {
            #pragma region �Ĩ�D�{��
            RushTimer += TIMER_TICK_MILLIDECOND;
            if (Step == 1)
                Velocity_Y = 0;
            if (RushTimer < 40 && Step == 0)
            {
                Velocity_X = Ahead(2.5);
                Velocity_Y = -2;
            }
            if (RushTimer >= 40 && Step == 0)
            {
                RushTimer = 0;
                Step = 1;
                Effects.BootEffect(&Effects.Content["Airboost"], Camera, Rect.X, Rect.X + 30, Rect.Y - 30, 0, 0, false, IsRight);
                Throughing = true;
                PlaySounds(Sounds.Rush, false);
                if (IsRight)
                {
                    Velocity_X = 38;
                    Acceleration_X = -3.5;
                    Velocity_Y = 2;
                    Invincible = true;
                }
                else
                {
                    Velocity_X = -38;
                    Acceleration_X = +3.5;
                    Velocity_Y = 2;
                    Invincible = true;
                }
            }
            else if (RushTimer <= 16 && Step == 1)//�٨�
            {
                CanToRushAttack;
                CanToRushSkill;

            }
            else if (RushTimer >= 16 && Step >= 1)//�٨�
            {
                Step = 2;
                CanToRushAttack;
                CanToRushSkill;

            }
            if (RushTimer >= 40 && RushTimer <= 80 && Step == 2)
            {
                if (IsRight&&Velocity_X < 0)
                    Velocity_X = 0;
                else if (IsRight == false && Velocity_X > 0)
                    Velocity_X = 0;
                CanToRushAttack;
                CanToRushSkill;

            }

            #pragma endregion

            //���`����
            if (RushTimer > 80 && Step == 2)
            {
                RushTimer = 0;
                Throughing = false;
                Invincible = false;
                Velocity_X = 0;
                Acceleration_X = 0;

                #pragma region �^���S��
                Effects.Content["AirBoost"].Step = 0;
                Effects.Content["AirBoost"].visable = false;
                Effects.Content["AirBoost"].OnUpdate("Effects", Camera);
                #pragma endregion

                #pragma region �P�_���Ӧ^����Ӱʧ@
                if (OnGround)
                    GotoStandby(GPP);
                else
                    GotoDrop(GPP);
                #pragma endregion

            }



        }
    }

    void Rina::GotoRunning(GPH)
    {
        Action = "����";
        Step = 0;
        RunningTimer = 0;
    }
    void Rina::OnRunning(GPH)
    {
        if (Action == "����")
        {

            AddSP(RunningSPincrements);
            RunningTimer += TIMER_TICK_MILLIDECOND;
            #pragma region ���k����
            if (CanControl&&IsRight&&OnGround && (Button_now.button_Right == true || Button_now.button_Left == true))
            {
                if (Button_now.button_Left == true)
                    IsRight = false;
                if (RunningTimer >= 40)
                {
                    RunningTimer = 0;
                    LoopStep(7);
                }

                RunAhead(0.8, RunSpeed);
            }
            else if (CanControl&&IsRight == false && OnGround && (Button_now.button_Right == true || Button_now.button_Left == true))
            {
                if (Button_now.button_Right == true)
                    IsRight = true;
                if (RunningTimer >= 40)
                {
                    RunningTimer = 0;
                    LoopStep(7);
                }
                RunAhead(0.8, RunSpeed);
            }
            #pragma endregion

            #pragma region ��O���ʧ@
            CanToCharge;
            CanToGuard;
            CanToJump;
            CanToNormalAttack1;
            CanToRush;
            CanToSkill1;
            CanToUpAttack;
            CanToUpSkill;

            //���`����(���k��})
            if (Button_now.button_Right == false && Button_now.button_Left == false)
                CanToStandby;
            #pragma endregion

        }
    }

    void Rina::GotoJump(GPH)
    {
        if (OnGround)
        {
            JumpTimer2 = 0;
            Action = "���D";
            Step = 0;
            RushTimer = 0;
            JumpTimer = 0;
        }
        else
        {
            if (SP >= 10)
            {
                JumpTimer2 = 0;
                GainSP(-10);
                Action = "���D";
                RushTimer = 0;
                Step = 3;
                JumpTimer = 0;
                Velocity_Y = -12;
                OnGround = false;
                PlayEffect(this, "Airboost2", Camera, Rect.X - 30, Rect.X - 35, Rect.Y + 80);
                PlaySounds(Sounds.Jump, false);
            }
        }
    }
    void Rina::OnJump(GPH)
    {
        if (Action == "���D")
        {
            JumpTimer += TIMER_TICK_MILLIDECOND;
            #pragma region ���D�D�{��
            if (JumpTimer >= 10 && Step < 2)
            {
                ProduceFriction(0.15, 1);
                Step += 1;
                JumpTimer = 0;
            }
            else if (JumpTimer >= 20 && Step == 2)
            {
                Step = 3;
                JumpTimer = 0;
                Velocity_Y = -12;
                OnGround = false;
                PlayEffect(this, "Airboost2", Camera, Rect.X - 30, Rect.X - 35, Rect.Y + 80);
                PlaySounds(Sounds.Jump, false);
            }
            else if (Step >= 3 && Velocity_Y < 0)
            {
                if (CanControl&&Button_now.button_Jump == true && Velocity_Y < 2 && JumpTimer < 120)
                    Velocity_Y -= 0.25;
            }
            else if (Velocity_Y >= 0 && Step >= 3)
            {
                JumpTimer = 0;
                Step = 4;
            }
            #pragma endregion

            #pragma region �_����
            if (Step >= 3)
            {
                #pragma region �Ť�����
                if (CanControl&&Button_now.button_Right == false && CanControl&&Button_now.button_Left == false)
                {
                    ProduceFriction(0.15, 1);
                }
                else if (CanControl&&Button_now.button_Right == true)
                {
                    IsRight = true;
                    RunAhead(0.5, RunSpeed / 2);
                }
                else if (CanControl&&Button_now.button_Left == true)
                {
                    IsRight = false;
                    RunAhead(0.5, RunSpeed / 2);
                }
                #pragma endregion

                #pragma region ��O���ʧ@

                CanToAirAttack1;
                CanToRush;
                CanToSkill1;
                CanToAirDownAttack;
                CanToAirUpAttack;
                CanToJump;
                CanToFastDrop;
                //���`���a
                if (OnGround)
                    CanToStandby;

                #pragma endregion
            }
            #pragma endregion       
        }
    }

    void Rina::GotoCharge(GPH)
    {
        Action = "�m��";
        Step = 0;
        ChargeTimer = 0;
        //�ҰʯS��
        PlayEffect(this, "SPCharge", Camera, Rect.X - 35, Rect.X - 30, Rect.Y - 45);
    }
    void Rina::OnCharge(GPH)
    {
        if (Action == "�m��")
        {
            ProduceFriction(1, 1);
            ChargeTimer2 += TIMER_TICK_MILLIDECOND;
            ChargeTimer += TIMER_TICK_MILLIDECOND;

            if (ChargeTimer >= 50 && Step == 0)
            {
                Step = 1;
                ChargeTimer = 0;
            }
            else if (ChargeTimer >= 16 && Step >= 1 && Step < 3)
            {
                Step += 1;
                ChargeTimer = 0;
                if (Step == 3)
                {
                    ChargeTimer2 = 0;
                    Chargecount = 0;
                    PlaySounds(Sounds.SPCharge, false);
                }
            }
            else if (ChargeTimer2 >= 10 && Step >= 3)
            {
                Chargecount += 1;
                if (Chargecount < 10)
                {
                    SP += ChargeSPincrements / 10;
                    if (SP > SP_Max)
                        SP = SP_Max;
                }
                if (Step == 3)
                {
                    Step = 4;
                }
                else
                {
                    Step = 3;
                }
                ChargeTimer2 = 0;
            }
            else if (ChargeTimer >= 90 && Step >= 3)//���`����
            {
                ChargeTimer = 0;
                if (Button_now.button_Guard == true)
                {
                    GotoGuard(GPP);
                }
                else
                {
                    GotoStandby(GPP);
                }
            }


        }
    }

    void Rina::GotoNormalAttack1(GPH)
    {
        if (SP >= Rina_NormalAttack1_Cost)
        {
            GainSP(-Rina_NormalAttack1_Cost);
            Action = "����1";
            Step = 0;
            NormalAttack1Timer = 0;
        }
    }
    void Rina::OnNormalAttack1(GPH)
    {
        if (Action == "����1")
        {
            NormalAttack1Timer += TIMER_TICK_MILLIDECOND;

            #pragma region �ʧ@�D��
            //�B�z�����O
            ProduceFriction(1, 1);
            if (NormalAttack1Timer >= 16 && Step <= 2)
            {
                NormalAttack1Timer = 0;
                Step += 1;

                #pragma region ���ͧ�������
                //�X��
                if (Step >= 3)
                {
                    Velocity_X += Ahead(4);
                    Attacks.AttackReset_Normal(
                        &(Attacks.AttackObjects["Normal1"]), this, Enemy,
                        Rina_NormalAttack1_Damage,
                        2, 2, Rect.X + 108, Rect.X - 2, Rect.Y + 52, 0, 0,
                        150, 30, "PunchHit", Sounds.NormalHit, Camera);

                }
                #pragma endregion


            }
            else if (NormalAttack1Timer >= 40 && Step == 3)
            {
                NormalAttack1Timer = 0;
                Step = 4;
            }
            #pragma endregion

            #pragma region ��O���ʧ@
            if (NormalAttack1Timer < 100 && Step >= 4)
            {
                //��O���ʧ@
                CanToNormalAttack2;
                CanToSkill1;
                CanToJump;
                CanToRush;
                CanToUpAttack;
                CanToDownAttack;
                CanToUpSkill;
            }
            else if (NormalAttack1Timer >= 100 && Step >= 4)
            {
                //���`����
                GotoStandby(GPP);
            }
            #pragma endregion
        }
    }

    void Rina::GotoNormalAttack2(GPH)
    {
        if (SP >= Rina_NormalAttack2_Cost)
        {
            GainSP(-Rina_NormalAttack2_Cost);
            Action = "����2";
            Step = 0;
            NormalAttack1Timer = 0;
        }
    }
    void Rina::OnNormalAttack2(GPH)
    {
        if (Action == "����2")
        {
            NormalAttack1Timer += TIMER_TICK_MILLIDECOND;
            #pragma region �ʧ@�D��
            //�B�z�����O
            ProduceFriction(1, 1);
            if (NormalAttack1Timer >= 20 && Step >= 0 && Step < 2)
            {
                NormalAttack1Timer = 0;
                Step += 1;
            }
            if (NormalAttack1Timer >= 12 && Step >= 2 && Step < 3)
            {
                NormalAttack1Timer = 0;
                Step += 1;
                if (Step == 3)
                {
                    Velocity_X += Ahead(4);
                    #pragma region ���ͧ�������
                    //�X��
                    Attacks.AttackReset_Normal(
                        &(Attacks.AttackObjects["Normal1"]), this, Enemy,
                        Rina_NormalAttack2_Damage,
                        3.5, 2, Rect.X + 127, Rect.X - 15, Rect.Y + 52, 0, 0,
                        120, 30, "PunchHit", Sounds.NormalHit, Camera);
                    #pragma endregion
                }
            }
            else if (NormalAttack1Timer >= 40 && Step == 3)
            {
                NormalAttack1Timer = 0;
                Step = 4;
            }
            #pragma endregion

            #pragma region ��O���ʧ@
            if (NormalAttack1Timer < 100 && Step >= 4)
            {
                //��O���ʧ@
                CanToNormalAttack3;
                CanToSkill1;
                CanToJump;
                CanToRush;
                CanToUpAttack;
                CanToDownAttack;
                CanToUpSkill;

            }
            else if (NormalAttack1Timer >= 100 && Step >= 4)
            {
                //���`����
                GotoStandby(GPP);
            }
            #pragma endregion

        }
    }

    void Rina::GotoNormalAttack3(GPH)
    {
        if (SP >= Rina_NormalAttack3_Cost)
        {
            GainSP(-Rina_NormalAttack3_Cost);
            Velocity_X += Ahead(4);
            Action = "����3";
            Step = 0;
            NormalAttack1Timer = 0;
        }
    }
    void Rina::OnNormalAttack3(GPH)
    {
        if (Action == "����3")
        {
            NormalAttack1Timer += TIMER_TICK_MILLIDECOND;
            #pragma region �ʧ@�D��
            ProduceFriction(0.25, 0.5);
            if (NormalAttack1Timer >= 40 && Step == 0)
            {
                Step += 1;
                NormalAttack1Timer = 0;
            }
            if (NormalAttack1Timer >= 24 && Step <= 4 && Step >= 1)
            {
                Step += 1;
                NormalAttack1Timer = 0;
                if (Step == 4)
                {
                    Velocity_Y -= 4;
                    #pragma region ���ͧ�������
                    //�򥻳]�w
                    Attacks.AttackReset_Normal(
                        &(Attacks.AttackObjects["Normal1"]), this, Enemy,
                        Rina_NormalAttack3_Damage,
                        12, 7.5, Rect.X + 112, Rect.X - 5, Rect.Y + 67, 0, 0,
                        200, 100, "PunchHit", Sounds.NormalHit, Camera);
                    //�B�~�]�w
                    Attacks.AttackObjects["Normal1"].CanHitFly = true;
                    #pragma endregion
                }
            }
            else if (NormalAttack1Timer >= 30 && Step == 5)
            {
                NormalAttack1Timer = 0;
                Step = 6;
            }
            #pragma endregion

            #pragma region ��O���ʧ@
            if (NormalAttack1Timer < 100 && Step >= 6)
            {
                CanToJump;
                CanToRush;
            }
            else if (NormalAttack1Timer >= 100 && Step >= 6)
            {
                //���`����
                GotoStandby(GPP);
            }
            #pragma endregion

        }
    }

    void Rina::GotoSkill1(GPH)
    {
        if (SP >= Rina_Skill1_Cost)
        {
            GainSP(-Rina_Skill1_Cost);
            if (Velocity_Y > 0 && OnGround == false)
                Velocity_Y = 0;
            Action = "�S��";
            Step = 0;
            Shot1Timer = 0;
            Velocity_X = Ahead(30);
            Throughing = true;
            if (Button_now.button_Right)
                IsRight = true;
            else if (Button_now.button_Left)
                IsRight = false;
        }
    }
    void Rina::OnSkill1(GPH)
    {
        if (Action == "�S��")
        {

            Shot1Timer += TIMER_TICK_MILLIDECOND;

            #pragma region �ʧ@�D��
            ProduceFriction(3, 1);

            if (Shot1Timer >= 30 && Step == 0)
            {
                Shot1Timer = 0;
                Step = 1;
            }
            else if (Shot1Timer >= 30 && abs(Velocity_X) < 1 && (Step == 1 || Step == 2))
            {
                if (Button_now.button_Right)
                    IsRight = true;
                else if (Button_now.button_Left)
                    IsRight = false;

                if (Shot1Current >= 4)
                    Shot1Current = 0;
                Shot1Timer = 0;
                Step = 3;
                #pragma region ���ͧ�������
                //�X��
                PlaySounds(Sounds.light1, false);
                Attacks.AttackReset_Shot(&(Attacks.AttackObjects["flashblade_H_" + IntToString(Shot1Current)]), this, Enemy,
                    Rina_DownSkill_Damage,
                    2, 3.5,
                    Rect.X + 75, Rect.X + 10, Rect.Y + 60, Ahead(6), 0,
                    120, 1000, 2,
                    true, true, true,
                    "PunchHit", Sounds.SliceHit, Camera);
                Shot1Current += 1;
                (Attacks.AttackObjects["flashblade_H_" + IntToString(Shot1Current)]).HitNoon = false;
                #pragma endregion
            }
            if (Shot1Timer >= 16 && Step >= 3 && Step < 5)
            {
                Step += 1;
                Shot1Timer = 0;
            }
            #pragma endregion

            #pragma region ��O���ʧ@
            if (Shot1Timer < 100 && Step >= 5)
            {
                Throughing = false;
                //��O���i��ʧ@
                if (OnGround)
                {

                    CanToNormalAttack1;
                    CanToUpAttack;
                    CanToDownAttack;
                    CanToUpSkill;
                    CanToSkill1;
                }
                else
                {

                    CanToAirUpAttack;
                    CanToAirDownAttack;
                    CanToAirAttack1;
                    CanToFastDrop;
                    CanToSkill1;
                }

                CanToRush;
                CanToJump;
            }
            else if (Shot1Timer >= 100 && Step >= 5)
            {
                Throughing = false;
                //���`����
                if (OnGround)
                    GotoStandby(GPP);
                else
                    GotoDrop(GPP);
            }
            #pragma endregion

        }
    }

    void Rina::GotoAirAttack1(GPH)
    {

    }
    void Rina::OnAirAttack1(GPH)
    {
        if (Action == "�Ŵ�1")
        {


        }
    }

    void Rina::GotoAirAttack2(GPH)
    {

    }
    void Rina::OnAirAttack2(GPH)
    {
        if (Action == "�Ŵ�2")
        {


        }
    }

    void Rina::GotoUpAttack(GPH)
    {
        if (SP >= Rina_UpAttack_Cost)
        {
            GainSP(-Rina_UpAttack_Cost);
            Action = "�W��";
            Step = 0;
            NormalAttack1Timer = 0;
        }
    }
    void Rina::OnUpAttack(GPH)
    {
        if (Action == "�W��")
        {
            NormalAttack1Timer += TIMER_TICK_MILLIDECOND;

            #pragma region �ʧ@�D��
            //�B�z�����O
            ProduceFriction(1, 1);
            if (NormalAttack1Timer >= 60 && Step == 0)
            {
                NormalAttack1Timer = 0;
                Step = 1;
            }
            else if (NormalAttack1Timer >= 16 && Step >= 1 && Step <= 3)
            {
                NormalAttack1Timer = 0;
                Step += 1;
                if (Step == 2)
                {
                    Velocity_Y = -10;
                }
                #pragma region ���ͧ�������
                //�X��
                if (Step == 3)
                {
                    PlayEffect(this, "Airboost2", Camera, Rect.X - 15, Rect.X - 50, Rect.Y + 90);
                    Velocity_X += Ahead(8);
                    //��¦�]�w
                    Attacks.AttackReset_Normal(
                        &(Attacks.AttackObjects["Normal2"]), this, Enemy,
                        Rina_UpAttack_Damage,
                        5, 11, Rect.X + 147, Rect.X - 7, Rect.Y + 40, 0, 0,
                        220, 30, "PunchHit", Sounds.NormalHit, Camera);

                }
                #pragma endregion
            }
            else if (NormalAttack1Timer >= 40 && Step == 4)
            {

                NormalAttack1Timer = 0;
                Step = 5;
            }
            #pragma endregion

            #pragma region ��O���ʧ@
            if (NormalAttack1Timer < 100 && Step >= 5)
            {
                //��O���ʧ@
                CanToSkill1;
                CanToAirDownAttack;
                CanToJump;
                CanToRush;
            }
            else if (NormalAttack1Timer >= 100 && Step >= 5)
            {
                //���`����
                GotoStandby(GPP);
            }
            #pragma endregion

        }
    }

    void Rina::GotoDownAttack(GPH)
    {
        if (SP >= Rina_DownAttack_Cost)
        {
            GainSP(-Rina_DownAttack_Cost);
            Action = "�U��";
            Step = 0;
            NormalAttack1Timer = 0;
            Velocity_X = Ahead(-12);
            Velocity_Y = -3;
        }
    }
    void Rina::OnDownAttack(GPH)
    {
        if (Action == "�U��")
        {
            NormalAttack1Timer += TIMER_TICK_MILLIDECOND;



            #pragma region �ʧ@�D��
            //�B�z�����O
            if (Step == 0)
                ProduceFriction(0.5, 0.5);
            else if (Step == 1)
                ProduceFriction(0.3, 0.5);
            else if (Step >= 2)
                ProduceFriction(1, 1);




            if (NormalAttack1Timer >= 50 && Step == 0)
            {
                NormalAttack1Timer = 0;
                Step = 1;
            }
            else if (NormalAttack1Timer >= 150 && Step == 1)
            {
                NormalAttack1Timer = 0;
                Step = 2;
                Velocity_X = Ahead(35);
            }
            else if (NormalAttack1Timer >= 25 && Step == 2)
            {
                NormalAttack1Timer = 0;
                Step = 3;
            }
            else if (NormalAttack1Timer >= 16 && Step >= 3 && Step <= 4)
            {
                Velocity_X = Ahead(3);
                NormalAttack1Timer = 0;
                Step += 1;
                #pragma region ���ͧ�������
                //�X��
                if (Step == 4)
                {
                    Attacks.AttackReset_Normal(
                        &(Attacks.AttackObjects["Normal1"]), this, Enemy,
                        Rina_DownAttack_Damage,
                        2, 3, Rect.X + 90, Rect.X + 20, Rect.Y + 65, 0, 0,
                        200, 30, "PunchHit", Sounds.NormalHit, Camera);
                    Attacks.AttackObjects["Normal1"].HitBreak = true;
                    Attacks.AttackObjects["Normal1"].Drawable = false;
                }
                #pragma endregion
            }
            #pragma endregion

            #pragma region ��O���ʧ@
            if (NormalAttack1Timer < 100 && Step >= 5)
            {
                //��O���ʧ@
                CanToNormalAttack1;
                CanToSkill1;
                CanToJump;
                CanToRush;
                CanToUpSkill;
            }
            else if (NormalAttack1Timer >= 100 && Step >= 5)
            {
                //���`����
                GotoStandby(GPP);
            }
            #pragma endregion

        }
    }

    void Rina::GotoRushAttack(GPH)
    {
        if (SP >= Rina_RushAttack_Cost)
        {
            GainSP(-Rina_RushAttack_Cost);
            if (Velocity_Y > 0 && OnGround == false)
                Velocity_Y = 0;
            RushTimer = 0;
            IsRushAttack = false;
            Throughing = false;
            Invincible = false;
            Acceleration_X = 0;
            Action = "�Ĩ봶";
            Step = 0;
            NormalAttack1Timer = 0;
        }
    }
    void Rina::OnRushAttack(GPH)
    {
        if (Action == "�Ĩ봶")
        {

            NormalAttack1Timer += TIMER_TICK_MILLIDECOND;
            ProduceFriction(0.25, 0.5);
            #pragma region �ʧ@�D��
            if (NormalAttack1Timer <= 110 && Step >= 0)
            {

                if (abs(Velocity_X) > 12)
                {
                    Velocity_X = Ahead(12);
                }

                if (NormalAttack1Timer >= 25)
                    Step = 1;
                if (NormalAttack1Timer >= 50)
                    Step = 2;


                #pragma region ��s���������m
                if (IsRight)
                    Attacks.AttackObjects["Normal1"].Rect.X = Rect.X + 90;
                else
                    Attacks.AttackObjects["Normal1"].Rect.X = Rect.X;
                Attacks.AttackObjects["Normal1"].Rect.Y = Rect.Y + 55;
                if (Attacks.AttackObjects["Normal1"].IsHited && (Attacks.AttackObjects["Normal1"].ComboTimer > TIMER_TICK_MILLIDECOND * 4))
                {
                    Attacks.AttackObjects["Normal1"].ComboTimer = 0;
                    Attacks.AttackObjects["Normal1"].IsHited = false;
                }
                #pragma endregion

                #pragma region ���ͧ�������
                if (IsRushAttack == false)
                {
                    IsRushAttack = true;
                    //��¦�]�w
                    Attacks.AttackReset_Normal(
                        &(Attacks.AttackObjects["Normal1"]), this, Enemy,
                        Matchstick_RushAttack_Damage,
                        9.5, 0, Rect.X + 98, 0, 0, 0, 0,
                        100, 100, "PunchHit", Sounds.NormalHit, Camera);
                    //�B�~�]�w
                    Attacks.AttackObjects["Normal1"].CanCombo = true;//�i�s��
                    Attacks.AttackObjects["Normal1"].HitNoon = false;
                    Attacks.AttackObjects["Normal1"].Drawable = false;
                }
                #pragma endregion
            }
            #pragma endregion

            #pragma region ��O���ʧ@
            if (NormalAttack1Timer > 110 && Step >= 0)
            {
                Acceleration_X = 0;
                Velocity_X = 0;
                #pragma region �P�_���Ӧ^����Ӱʧ@
                if (OnGround)
                    GotoStandby(GPP);
                else
                    GotoDrop(GPP);
                #pragma endregion
            }
            #pragma endregion

        }
    }

    void Rina::GotoAirUpAttack(GPH)
    {

    }
    void Rina::OnAirUpAttack(GPH)
    {
        if (Action == "�ŤW��")
        {

        }
    }

    void Rina::GotoAirDownAttack(GPH)
    {
        if (SP >= Rina_AirDownAttack_Cost)
        {
            GainSP(-Rina_AirDownAttack_Cost);
            Action = "�ŤU��";
            Step = 0;
            Velocity_Y = -9;
            Velocity_X = Ahead(-4.5);
            NormalAttack1Timer = 0;
        }
    }
    void Rina::OnAirDownAttack(GPH)
    {
        if (Action == "�ŤU��")
        {
            NormalAttack1Timer += TIMER_TICK_MILLIDECOND;

            #pragma region �ʧ@�D��
            if (NormalAttack1Timer < 150 && Step == 0)
            {
                ProduceFriction(0.25, 1);
            }
            else if (NormalAttack1Timer >= 150 && Step == 0)
            {
                Velocity_X = Ahead(7.25);
                Velocity_Y = 20;
                Step = 1;
                NormalAttack1Timer = 0;
                Attacks.AttackReset_Normal(
                    &(Attacks.AttackObjects["Normal3"]), this, Enemy,
                    Rina_AirDownAttack_Damage,
                    2.5, -18, Rect.X + 90, Rect.X, Rect.Y + 20, 0, 0,
                    200, 30, "PunchHit", Sounds.NormalHit2, Camera);
            }
            else if (Rect.Y < GroundPosition && Step == 1)
            {
                Attacks.AttackObjects["Normal3"].Rect.X = Rect.X + Ahead(30);
                Attacks.AttackObjects["Normal3"].Rect.Y = Rect.Y + 110;
                Attacks.AttackObjects["Normal3"].AliveTimer = 0;
            }
            else if (Rect.Y >= GroundPosition && Step == 1)
            {
                NormalAttack1Timer = 0;
                Step = 2;
            }
            #pragma endregion
            #pragma region ��O���ʧ@
            if (NormalAttack1Timer < 100 && Step >= 2)
            {
                //��O���ʧ@
                CanToNormalAttack1;
                CanToSkill1;
                CanToJump;
                CanToRush;
                CanToUpSkill;
                CanToAirUpAttack;
            }
            else if (NormalAttack1Timer >= 100 && Step >= 2)
            {
                //���`����
                GotoStandby(GPP);
            }
            #pragma endregion

        }
    }

    void Rina::GotoUpSkill(GPH)
    {
        if (SP >= Rina_UpSkill_Cost)
        {
            GainSP(-Rina_UpSkill_Cost);
            Action = "�W�S��";
            Step = 0;
            Shot1Timer = 0;
            Velocity_X = -Ahead(12);
            Velocity_Y = -6;
            if (Button_now.button_Right)
                IsRight = true;
            else if (Button_now.button_Left)
                IsRight = false;
        }
    }
    void Rina::OnUpSkill(GPH)
    {
        if (Action == "�W�S��")
        {

            Shot1Timer += TIMER_TICK_MILLIDECOND;

            #pragma region �ʧ@�D��
            ProduceFriction(0.25, 0.5);

            if (Shot1Timer >= 30 && Step == 0)
            {
                Shot1Timer = 0;
                Step = 1;
            }
            if (Shot1Timer >= 80 && Step == 1)
            {

                if (Shot1Current >= 4)
                    Shot1Current = 0;
                Shot1Timer = 0;
                Step = 2;
                #pragma region ���ͧ�������
                //�X��
                PlaySounds(Sounds.light1, false);
                Attacks.AttackReset_Shot(&(Attacks.AttackObjects["flashblade_H_" + IntToString(Shot1Current)]), this, Enemy,
                    Rina_DownSkill_Damage,
                    2, 3.5,
                    Rect.X + 75, Rect.X + 10, Rect.Y + 60, Ahead(6), 0,
                    120, 1000, 2,
                    true, true, true,
                    "PunchHit", Sounds.SliceHit, Camera);
                Shot1Current += 1;
                (Attacks.AttackObjects["flashblade_H_" + IntToString(Shot1Current)]).HitNoon = false;
                #pragma endregion
            }
            if (Shot1Timer >= 16 && Step >= 2 && Step < 4)
            {
                Step += 1;
                Shot1Timer = 0;
            }
            #pragma endregion

            #pragma region ��O���ʧ@
            if (Shot1Timer < 100 && Step >= 4)
            {
                Throughing = false;
                //��O���i��ʧ@
                if (OnGround)
                {

                    CanToNormalAttack1;
                    CanToUpAttack;
                    CanToDownAttack;
                    CanToUpSkill;
                    CanToSkill1;
                }
                else
                {

                    CanToAirUpAttack;
                    CanToAirDownAttack;
                    CanToAirAttack1;
                    CanToFastDrop;
                    CanToSkill1;
                }

                CanToRush;
                CanToJump;
            }
            else if (Shot1Timer >= 100 && Step >= 4)
            {
                Throughing = false;
                //���`����
                if (OnGround)
                    GotoStandby(GPP);
                else
                    GotoDrop(GPP);
            }
            #pragma endregion

        }
    }

    void Rina::GotoDownSkill(GPH)
    {
        if (SP >= Rina_DownSkill_Cost&&useDownSkill == false)
        {
            GainSP(-Rina_DownSkill_Cost);
            Action = "�U�S��";
            Step = 0;
            NormalAttack1Timer = 0;
        }
    }
    void Rina::OnDownSkill(GPH)
    {
        if (Action == "�U�S��")
        {
            NormalAttack1Timer += TIMER_TICK_MILLIDECOND;
            DownSkillTimer += TIMER_TICK_MILLIDECOND;
            #pragma region �ʧ@�D��
            //�B�z�����O
            ProduceFriction(1, 1);
            if (NormalAttack1Timer >= 24 && Step >= 0 && Step <= 3)
            {
                NormalAttack1Timer = 0;
                Step += 1;
                DownSkillTimer = 0;
            }
            #pragma endregion
            //�X��
            if (Step >= 4 && DownSkillTimer >= 30)
            {
                DownSkillTimer = 0;
                if (DownSkillCurrent >= 8)
                    DownSkillCurrent = 0;
                DownSkillTimer2 = 0;
                useDownSkill = true;
                DownSkillXpoint = Enemy->Rect.X;
                DownSkillYpoint = Enemy->Rect.Y;
            }
            #pragma region ��O���ʧ@
            if (NormalAttack1Timer >= 20 && NormalAttack1Timer < 150 && Step >= 4)
            {
                //��O���ʧ@
                CanToNormalAttack1;
                CanToSkill1;
                CanToJump;
                CanToRush;
                CanToDownAttack;
            }
            else if (NormalAttack1Timer >= 150 && Step >= 4)
            {
                //���`����
                GotoStandby(GPP);
            }
            #pragma endregion

        }
    }

    void Rina::GotoRushSkill(GPH)
    {
        if (SP >= Rina_RushSkill_Cost)
        {

        }
    }
    void Rina::OnRushSkill(GPH)
    {
        if (Action == "�Ĩ�S��")
        {



        }
    }

    void Rina::GotoAirUpSkill(GPH)
    {
    }
    void Rina::OnAirUpSkill(GPH)
    {
    }

    void Rina::GotoAirDownSkill(GPH)
    {
    }
    void Rina::OnAirDownSkill(GPH)
    {
    }

    void Rina::GotoUltimateSkill(GPH)
    {
        if (SP > (SP_Max / 3))
        {
            UltraSkillcostSP = SP - (SP_Max / 3);
            SP = 0;
            Action = "�j��";
            Step = 0;
            NormalAttack1Timer = 0;
            UltraSkillTimer1 = 0;
        }
    }
    void Rina::OnUltimateSkill(GPH)
    {
        if (Action == "�j��")
        {

            NormalAttack1Timer += TIMER_TICK_MILLIDECOND;
            UltraSkillTimer1 += TIMER_TICK_MILLIDECOND;
            #pragma region �ʧ@�D��
            //�B�z�����O
            ProduceFriction(1, 1);
            if (NormalAttack1Timer >= 300 && Step == 0)
            {
                PlaySounds(Sounds.CutIn, false);
                NeedCutIn = true;
                NormalAttack1Timer = 0;
                Step = 1;
                Effects.BootEffect(&Effects.Content["Rina_US"], Camera, 800, 800, 0, 0, 0, false, true);
            }
            if (Step == 1 && NormalAttack1Timer >= 20)
            {
                Step = 2;
                Attacks.AttackReset_Normal(
                    &(Attacks.AttackObjects["Bigflashblade"]), this, Enemy,
                    Rina_UltimateSkill_Damage,
                    5, 20, Enemy->Rect.X - 100, Enemy->Rect.X, -700, Ahead(3), 8,
                    200, 1500, "PunchHit", Sounds.NormalHit, Camera);
                Attacks.AttackObjects["Bigflashblade"].HitBreak = true;
                Attacks.AttackObjects["Bigflashblade"].HitNoon = false;
                Attacks.AttackObjects["Bigflashblade"].Drawable = true;
                Attacks.AttackObjects["Bigflashblade"].GravityEffect = true;
                Attacks.AttackObjects["Bigflashblade"].Acceleration_Y = 1;
            }
            if (UltraSkillTimer1 >= 500 && Step == 2)
            {
                GotoStandby(GPP);
            }

            #pragma endregion



        }
    }
    #pragma endregion

}
