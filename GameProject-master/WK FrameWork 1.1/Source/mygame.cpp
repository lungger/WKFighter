//GameFramework����
#pragma region Game Framework Introduction
/*
* mygame.cpp: ���ɮ��x�C��������class��implementation
* Copyright (C) 2002-2008 Woei-Kae Chen <wkc@csie.ntut.edu.tw>
*
* This file is part of game, a free game development framework for windows.
*
* game is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* game is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*
* History:
*   2002-03-04 V3.1
*          Add codes to demostrate the use of CMovingBitmap::ShowBitmap(CMovingBitmap &).
*	 2004-03-02 V4.0
*      1. Add CGameStateInit, CGameStateRun, and CGameStateOver to
*         demonstrate the use of states.
*      2. Demo the use of CInteger in CGameStateRun.
*   2005-09-13
*      Rewrite the codes for CBall and CEraser.
*   2005-09-20 V4.2Beta1.
*   2005-09-29 V4.2Beta2.
*      1. Add codes to display IDC_GAMECURSOR in GameStateRun.
*   2006-02-08 V4.2
*      1. Revise sample screens to display in English only.
*      2. Add code in CGameStateInit to demo the use of PostQuitMessage().
*      3. Rename OnInitialUpdate() -> OnInit().
*      4. Fix the bug that OnBeginState() of GameStateInit is not called.
*      5. Replace AUDIO_CANYON as AUDIO_NTUT.
*      6. Add help bitmap to CGameStateRun.
*   2006-09-09 V4.3
*      1. Rename Move() and Show() as OnMove and OnShow() to emphasize that they are
*         event driven.
*   2006-12-30
*      1. Bug fix: fix a memory leak problem by replacing PostQuitMessage(0) as
*         PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE,0,0).
*   2008-02-15 V4.4
*      1. Add namespace game_framework.
*      2. Replace the demonstration of animation as a new bouncing ball.
*      3. Use ShowInitProgress(percent) to display loading progress.
*   2010-03-23 V4.6
*      1. Demo MP3 support: use lake.mp3 to replace lake.wav.
*/
#pragma endregion 

//�禡�w�ޤJ
#pragma region LibraryImport
#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include <windows.h>
#include <sstream>
#include <list>
#include <vector>
#include "audio.h"
#include "gamelib.h"
#include "mygame.h"
#include "Keycode.h"
#include "KeyBoardState.h"
#include "WKBitmap.h"
#include "BatllePlayer.h"
#include "CollisionSensor.h"
#include "TypeConverter.h"
#include  "WKAudio.h"
#include <memory>

#pragma endregion 

//�R�W�Ŷ��ޤJ
#pragma region NamespaceImport
using namespace std;
using namespace CollisionSensor_namespace;
using namespace TypeConverter_namespace;
using namespace WKAudio_namespace;
#pragma endregion 

namespace game_framework
{
	//���C�������ܼ�

	//�޿�
	int GameAction = 0;//�C������
	bool DebugMode = true;//�O�_�ҥ�Debug�Ҧ�

	//���
	CameraPosition Camera;//�C�����Y
	const COLORREF TransparentColor = RGB(100, 120, 0);//�z����]�w

	//�n��
	const Audio_ID Sounds;//���ĸ귽�s�X

	//��L
	const Keycode Keys;//��L�r�媫��
	KeyBoardState KeyState_now;//��e����L���A
	KeyBoardState KeyState_last;//�e�@��������L���A

	//�o�Ǩ禡�����u�Ƶ{���s�g��(�Ĳv�ä��|�]������)
#pragma region RENEWAL Fuction And Objects
	void ExitGame()
	{
		PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE, 0, 0);
	}
	//�Ĳv�ܮt�ɶq���n�ϥ�
	void Showtext(char *mes, int X, int Y, int fontsize, COLORREF BK, COLORREF FC, int WorkingLayer, int TargetLayer)
	{
		if (WorkingLayer == TargetLayer)
		{
			CDC *pDC = CDDraw::GetBackCDC();			// ���o Back Plain �� CDC 
			CFont f, *fp;
			f.CreatePointFont(fontsize * 10, "Times New Roman");	// ���� font f; 160���16 point���r
			fp = pDC->SelectObject(&f);					// ��� font f
			pDC->SetBkColor(BK);
			pDC->SetTextColor(FC);
			pDC->TextOut(X, Y, mes);
			pDC->SelectObject(fp);						// �� font f (�d�U���n�|�F��)
			CDDraw::ReleaseBackCDC();					// �� Back Plain �� CDC
		}
	}
#pragma endregion 

	//�{���}�l
#pragma region Program Initialize
	CGameStateInit::CGameStateInit(CGame *g) : CGameState(g)
	{
	}
	void CGameStateInit::OnBeginState()
	{

	}
#pragma endregion 

	//�C���}�YŪ���e��
#pragma region Game Loading Progress
	void CGameStateInit::OnInit()
	{
		//Ū���}�l
		ShowInitProgress(0);	// �@�}�l��loading�i�׬�0%
		// �i�JCGameStaterRun::OnInit()
		//Ū���Ҧ�����--Debug�Ҧ�Ū���ɮ�Begin
		DebugmodeLoading();
		//Ū���Ҧ�����--Debug�Ҧ�Ū���ɮ�End
	}
	void CGameStateRun::OnInit()// Ū���ɮ�
	{

		for (int i = 0; i <= 40; i += 1)
		{
			ShowInitProgress(i);
			Sleep(4);
		}
		//Ū���Ҧ�����--Begin

		//Ū���Ҧ�����--End
		ShowInitProgress(40);
		for (int i = 40; i <= 50; i += 1)
		{
			ShowInitProgress(i);
			Sleep(3);
		}
		ShowInitProgress(50);	// ���ӫe�@�Ӫ��A���i�סA���B�i�׵���33%
		for (int i = 50; i <= 75; i += 1)
		{
			ShowInitProgress(i);
			Sleep(1);
		}
		//Ū���Ҧ�����--Begin
		LoadSounds(Sounds.Ding, "Content\\Sounds\\ding.wav");
		//Ū���Ҧ�����--End
		ShowInitProgress(75);
		// ��OnInit�ʧ@�|����CGameStaterOver::OnInit()�A�ҥH�i���٨S��100%
		//
	}
	void CGameStateOver::OnInit()
	{
		for (int i = 75; i <= 100; i += 1)
		{
			ShowInitProgress(i);
			Sleep(4);
		}
		ShowInitProgress(0);	// ���ӫe�@�Ӫ��A���i�סA���B�i�׵���66%
		for (int i = 0; i <= 100; i += 1)
		{
			ShowInitProgress(i);
			Sleep(1);
		}
		ShowInitProgress(100);
		PlaySounds(Sounds.Ding, false);
		Sleep(500);				// ��C�A�H�K�ݲM���i�סA��ڹC���ЧR����Sleep
	}
#pragma endregion 

	//�C���}�Y�e��
#pragma region Game start screen
	void CGameStateInit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		KeyState_now.UpdateState_Down(nChar);
	}
	void CGameStateInit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		KeyState_now.UpdateState_Up(nChar);
	}
	void CGameStateInit::OnShow()
	{
		DebugmodeOnShow();
	}
	void CGameStateInit::OnMove()
	{
		if (KeyState_now.Space == true && KeyState_last.Space == false)
		{
			GotoGameState(GAME_STATE_RUN);
		}
		DebugmodeOnMove();
		KeyState_last = KeyState_now;
	}
#pragma endregion 

	//�C���i��e��
#pragma region GameRunning
//���F�}�Y�H�~���C���D��(�N�HGameAction�����C������)
	CGameStateRun::CGameStateRun(CGame *g) : CGameState(g)
	{

	}
	CGameStateRun::~CGameStateRun()
	{

	}
	void CGameStateRun::OnBeginState()
	{

	}

	//GameState LogicUpdate
	void CGameStateRun::OnMove()
	{
		// �p�G�Ʊ�ק�cursor���˦��A�h�N�U���{����commment�����Y�i
		// SetCursor(AfxGetApp()->LoadCursor(IDC_GAMECURSOR));


	}
	//GameState ShowBitmaps
	void CGameStateRun::OnShow()
	{
		//  �`�N�GShow�̭��d�U���n���ʥ��󪫥󪺮y�СA���ʮy�Ъ��u�@����Move���~��A
		//        �_�h��������sø�Ϯ�(OnDraw)�A����N�|���ʡA�ݰ_�ӷ|�ܩǡC���ӳN�y
		//        ���AMove�t�dMVC����Model�AShow�t�dView�A��View�������Model�C

	}


	void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		KeyState_now.UpdateState_Down(nChar);
	}
	void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		KeyState_now.UpdateState_Up(nChar);
	}

	//�ƹ��B�z�ƥ�
#pragma region MouseState
	void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // �B�z�ƹ����ʧ@
	{

	}
	void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
	{

	}
	void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
	{
		// �S�ơC�p�G�ݭn�B�z�ƹ����ʪ��ܡA�gcode�b�o��
	}
	void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // �B�z�ƹ����ʧ@
	{

	}
	void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
	{

	}
#pragma endregion 

#pragma endregion 

	//Game End-�C�������e��==�h�^�}�Y�e��
#pragma region GameOverState
	CGameStateOver::CGameStateOver(CGame *g) : CGameState(g)
	{
	}
	void CGameStateOver::OnMove()
	{
		GotoGameState(GAME_STATE_INIT);
	}
	void CGameStateOver::OnBeginState()
	{

	}
	void CGameStateOver::OnShow()
	{

	}
#pragma endregion 

	//�����Ҧ����ե�
#pragma region DebugValueable
	BitmapPicture DebugPicture1 = BitmapPicture("Content\\Bitmaps\\BG.bmp", true);
	BitmapPicture DebugPicture2 = BitmapPicture(true);
	BitmapAnimation DebugPicture3 = BitmapAnimation("ball", true);
	BitmapPicture DebugPicture4 = BitmapPicture("RES\\level1.bmp", true);
	vector <BitmapPicture> DebugPicture5;

	void CGameStateInit::DebugmodeLoading()
	{
		if (DebugMode)
		{
			int xy[20][2] = { {100, 100}, {100, 200}, {100, 300}, {100, 400}, {100, 500}, {100, 600}, {100, 700}, {100, 800}, {200, 850}, {300, 850},
			{400, 850}, {500, 850}, {600, 850}, {700, 850}, {800, 850}, {900, 850}, {1000, 850}, {1100, 850}, {1150, 800}, {1150, 700} };
			DebugPicture1.LoadTexture(true, TransparentColor);
			DebugPicture1.Rect.X = 300;
			DebugPicture1.Rect.Y = 300;
			DebugPicture2.LoadTexture("Content\\Bitmaps\\����H_�a������2_4.bmp", true, TransparentColor);
			DebugPicture3.AutoLoadBitmaps("ball", 4, true, TransparentColor);
			DebugPicture4.LoadTexture(false, TransparentColor);
			DebugPicture3.Rect.X = 200;
			DebugPicture3.Rect.Y = 100;
			for (int i = 0; i < 20; i++)
			{
				DebugPicture5.push_back(BitmapPicture("RES\\ball.bmp", true));
				DebugPicture5[i].LoadTexture(true, TransparentColor);
				(DebugPicture5[i]).Rect.X = xy[i][0];
				(DebugPicture5[i]).Rect.Y = xy[i][1];
			}

		}
	}
	void CGameStateInit::DebugmodeOnShow()
	{
		if (DebugMode)
		{
			for (int i = 0; i < 10; i += 1)
			{
				DebugPicture1.visable = false;
				DebugPicture2.visable = false;
				DebugPicture3.DisplayBitmap->Draw(i, 4);
				DebugPicture3.AutoPlay(1000);
				DebugPicture1.Draw(i, 3);
				DebugPicture2.Draw(i, 5);
				DebugPicture4.Draw(i, 0);
				for (int j = 0; j < (int)DebugPicture5.size(); j++)
					(DebugPicture5[j]).Draw(i, 5);

				//Showtext("DebugTesting...", 50, 200, 20, RGB(100, 120, 0), RGB(255, 255, 255), i, 2);

				//if (PixelCollision(DebugPicture3.DisplayBitmap, &DebugPicture4, 3))
				//{
				//    Showtext("LAYERTesting...True", 50, 200, 40, RGB(0, 50, 0), RGB(255, 255, 255), i, 1);
			   // }
				//else
			   //{
				//    Showtext("LAYERTesting...false", 50, 200, 40, RGB(0, 50, 0), RGB(255, 255, 255), i, 1);
				//}

			}
		}
	}
	void CGameStateInit::DebugmodeOnMove()
	{
		if (DebugMode)
		{

			DebugPicture1.OnUpdate(Camera);
			DebugPicture3.OnUpdate(Camera);
			DebugPicture2.OnUpdate(Camera);
			DebugPicture4.OnUpdate(Camera);
			for (int i = 0; i < (int)DebugPicture5.size(); i++)
				(DebugPicture5[i]).OnUpdate(Camera);

			bool fuck = false;
			BitmapPicture*test = &(DebugPicture5[0]);
			for (int i = 0; i < (int)DebugPicture5.size(); i++)
				if (BitmapPicture_HitRectangle(*DebugPicture3.DisplayBitmap, (DebugPicture5[i])))
				{



					(DebugPicture5[i]).visable = false;
					DebugPicture5.erase(DebugPicture5.begin()+i);
					i -= 1;

				}
			if (KeyState_now.Right == true)
			{
				DebugPicture3.DisplayBitmap->Rect.X_int += 5;
				if (PixelCollision(DebugPicture3.DisplayBitmap, &DebugPicture4, 1))
				{

				}
				else
				{
					if (DebugPicture3.Rect.X_int > (SIZE_X - 100 - DebugPicture3.Rect.Width))
					{
						Camera.X += 5;
						DebugPicture3.DisplayBitmap->Rect.X_int -= 5;
					}
					else
					{
						DebugPicture3.Rect.X += 5;
					}
				}
				DebugPicture3.DisplayBitmap->Rect.X_int -= 5;
			}
			if (KeyState_now.Left == true)
			{
				DebugPicture3.DisplayBitmap->Rect.X_int -= 5;
				if (PixelCollision(DebugPicture3.DisplayBitmap, &DebugPicture4, 1))
				{

				}
				else
				{
					if (DebugPicture3.Rect.X_int < 100)
					{
						Camera.X -= 5;
						DebugPicture3.DisplayBitmap->Rect.X_int += 5;
					}
					else
					{
						DebugPicture3.Rect.X -= 5;
					}
				}
				DebugPicture3.DisplayBitmap->Rect.X_int += 5;
			}
			if (KeyState_now.Up == true)
			{
				DebugPicture3.DisplayBitmap->Rect.Y_int -= 5;
				if (PixelCollision(DebugPicture3.DisplayBitmap, &DebugPicture4, 1))
				{

				}
				else
				{
					if (DebugPicture3.Rect.Y_int < 100)
					{
						Camera.Y -= 5;
						DebugPicture3.DisplayBitmap->Rect.Y_int += 5;
					}
					else
					{
						DebugPicture3.Rect.Y -= 5;
					}
				}
				DebugPicture3.DisplayBitmap->Rect.Y_int += 5;
			}
			if (KeyState_now.Down == true)
			{
				DebugPicture3.DisplayBitmap->Rect.Y_int += 5;
				if (PixelCollision(DebugPicture3.DisplayBitmap, &DebugPicture4, 1))
				{

				}
				else
				{
					if (DebugPicture3.Rect.Y_int > SIZE_Y - 100 - DebugPicture3.Rect.Height)
					{
						Camera.Y += 5;
						DebugPicture3.DisplayBitmap->Rect.Y_int -= 5;
					}
					else
					{
						DebugPicture3.Rect.Y += 5;
					}
				}
				DebugPicture3.DisplayBitmap->Rect.Y_int -= 5;
			}
		}
	}
#pragma endregion 

}