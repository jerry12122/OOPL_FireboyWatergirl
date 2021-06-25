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

#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "mygame.h"
#include <iostream>     // std::cout
#include <fstream> 
#include <string.h>
#include <conio.h>
#include <time.h>
#include <atomic>
#include <chrono>
#include <thread>
#include <stdio.h>
#include <sstream>
namespace game_framework {
/////////////////////////////////////////////////////////////////////////////
// �o��class���C�����C���}�Y�e������
/////////////////////////////////////////////////////////////////////////////
static int stage = 0;
static int count[2][7] = { {3,4,1,1,1,2,3},
					{8,8,2,2,2,1,2}};

static int	stage1_diamond1[3][2] = { {405,535},{140,260},{223,41} },
			stage1_diamond2[4][2] = { {570,535},{470,290},{475,87},{35,109} },
			stage1_Lake1_position[1][2] = { {360,579} },
			stage1_Lake2_position[1][2] = { {530,579} },
			stage1_Lake3_position[1][2] = { {460,455} },
			stage1_mood_position[2][2] = { {260,380},{20,310} },
			stage1_button_position[3][2] = { {270,295},{710,230} ,{600,215} };
static int	stage2_diamond1[8][2] = { {161,550},{247,550},{484,487} ,{576,487}, {304,373},{576,373},{376,243} ,{366,67} },
			stage2_diamond2[8][2] = { {484,550},{576,550},{161,487} ,{247,487}, {202,373},{484,373},{419,243} ,{409,67} },
			stage2_Lake1_position[2][2] = { {125,579} ,{454,517} },
			stage2_Lake2_position[2][2] = { {453,579}, {125,517} },
			stage2_Lake3_position[2][2] = { {164,310},{474,310} },
			stage2_mood_position[2][2] = { {260,380} ,{300,300}  },
			stage2_button_position[3][2] = { {140,390},{400,330},{600,390}},
			stage2_button_position1[3][2] = { {200,100},{450,110},{560,100} };
//NUMRED,NUMICE, LAKERED, LAKEICE, LAKEGREEN, NUMMOD, NUMBUT
CGameStateInit::CGameStateInit(CGame *g)
: CGameState(g)
{
	intro_bool = false;
}

void CGameStateInit::OnInit()
{
	//
	// ��ϫܦh�ɡAOnInit���J�Ҧ����ϭn��ܦh�ɶ��C���קK���C�����H
	//     �������@�СA�C���|�X�{�uLoading ...�v�A���Loading���i�סC
	//
	ShowInitProgress(0);	// �@�}�l��loading�i�׬�0%
	//
	// �}�l���J���
	//
	logo.LoadBitmap(IDB_GAME_MENU);
	intro.LoadBitmap(IDB_INTRO);
	//intro.L
	//Sleep(300);				// ��C�A�H�K�ݲM���i�סA��ڹC���ЧR����Sleep
	//
	// ��OnInit�ʧ@�|����CGameStaterRun::OnInit()�A�ҥH�i���٨S��100%
	//


}
void CGameStateInit::OnBeginState()
{
}

void CGameStateInit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const char KEY_ESC = 27;
	//const char KEY_SPACE = ' ';
	if (nChar == KEY_ESC)
		PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE, 0, 0);	// �����C��
	/*
		GotoGameState(GAME_STATE_RUN);						// ������GAME_STATE_RUN
	else if (nChar == KEY_ESC)								// Demo �����C������k
		*/
}

void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point)
{
	if ((point.x > 303 && point.x < 485) && (point.y > 311 && point.y < 375))
	{
		GotoGameState(GAME_STATE_MENU);
	}
	if ((point.x > 10 && point.x < 82) && (point.y > 475 && point.y < 555))
	{
		intro_bool = true;
	}
	if ((point.x > 165 && point.x < 257) && (point.y > 382 && point.y < 421))
	{
		intro_bool = false;
		GotoGameState(GAME_STATE_RUN);
	}
	
		// ������GAME_STATE_RUN
}

void CGameStateInit::OnShow()
{
	//
	// �K�Wlogo
	//
	logo.SetTopLeft(0, 0);
	logo.ShowBitmap();
	intro.SetTopLeft(118, 135);
	if (intro_bool)
	{
		intro.ShowBitmap();
	}

	//
	// Demo�ù��r�����ϥΡA���L�}�o�ɽкɶq�קK�����ϥΦr���A���CMovingBitmap����n
	//
	/*
	CDC *pDC = CDDraw::GetBackCDC();			// ���o Back Plain �� CDC 
	CFont f,*fp;
	f.CreatePointFont(160,"Times New Roman");	// ���� font f; 160���16 point���r
	fp=pDC->SelectObject(&f);					// ��� font f
	pDC->SetBkColor(RGB(0,0,0));
	pDC->SetTextColor(RGB(255,255,0));
	pDC->TextOut(120,220,"Please click mouse or press SPACE to begin.");
	pDC->TextOut(5,395,"Press Ctrl-F to switch in between window mode and full screen mode.");
	if (ENABLE_GAME_PAUSE)
		pDC->TextOut(5,425,"Press Ctrl-Q to pause the Game.");
	pDC->TextOut(5,455,"Press Alt-F4 or ESC to Quit.");
	pDC->SelectObject(fp);						// �� font f (�d�U���n�|�F��)
	CDDraw::ReleaseBackCDC();
	*/
	// �� Back Plain �� CDC
}								

/////////////////////////////////////////////////////////////////////////////
// �o��class���C����������A(Game Over)
/////////////////////////////////////////////////////////////////////////////

CGameStateOver::CGameStateOver(CGame *g)
: CGameState(g)
{
}
void CGameStateOver::OnLButtonDown(UINT nFlags, CPoint point)
{
	if ((point.x > 254 && point.x < 367) && (point.y > 337 && point.y < 376))
	{
		GotoGameState(GAME_STATE_MENU);
	}
	if ((point.x > 444 && point.x < 556) && (point.y > 337 && point.y < 376))
	{
		if (stage == 0)
		{
			GotoGameState(GAME_STATE_RUN);
		}
		
		if (stage == 1)
		{
			GotoGameState(GAME_STATE_RUN2);
		}
	}
}
void CGameStateOver::OnMove()
{

}
void CGameStateOver::OnBeginState()
{

}
void CGameStateOver::OnInit()
{
	//
	// ��ϫܦh�ɡAOnInit���J�Ҧ����ϭn��ܦh�ɶ��C���קK���C�����H
	//     �������@�СA�C���|�X�{�uLoading ...�v�A���Loading���i�סC
	//
	ShowInitProgress(66);	// ���ӫe�@�Ӫ��A���i�סA���B�i�׵���66%
	//
	// �}�l���J���
	//
	gameover.LoadBitmap(GAMEOVER, RGB(255, 255, 255));
	//Sleep(300);				// ��C�A�H�K�ݲM���i�סA��ڹC���ЧR����Sleep
	//
	// �̲׶i�׬�100%
	//
	ShowInitProgress(100);
}
void CGameStateOver::OnShow()
{
	gameover.SetTopLeft(118, 138);
	gameover.ShowBitmap();

}
////////////////////////////////////////////////////
CGameStateMenu::CGameStateMenu(CGame *g)
	: CGameState(g)
{
}
void CGameStateMenu::OnLButtonDown(UINT nFlags, CPoint point)
{
	if ((point.x > 39 && point.x < 210) && (point.y > 492 && point.y < 588))
	{
		GotoGameState(GAME_STATE_INIT);
	}
	if ((point.x > 378 && point.x < 422) && (point.y > 492 && point.y < 542))
	{
		stage = 0;
		GotoGameState(GAME_STATE_RUN);
	}
	if ((point.x > 409 && point.x < 455) && (point.y > 437 && point.y < 487))
	{
		stage = 1;
		GotoGameState(GAME_STATE_RUN2);
	}
}
void CGameStateMenu::OnMove()
{

}
void CGameStateMenu::OnBeginState()
{

}
void CGameStateMenu::OnInit()
{
	//
	// ��ϫܦh�ɡAOnInit���J�Ҧ����ϭn��ܦh�ɶ��C���קK���C�����H
	//     �������@�СA�C���|�X�{�uLoading ...�v�A���Loading���i�סC
	//
	ShowInitProgress(66);	// ���ӫe�@�Ӫ��A���i�סA���B�i�׵���66%
	//
	// �}�l���J���
	//
	bg.LoadBitmap(IDB_MENU, RGB(255, 255, 255));

	//Sleep(300);				// ��C�A�H�K�ݲM���i�סA��ڹC���ЧR����Sleep
	//
	// �̲׶i�׬�100%
	//
	ShowInitProgress(100);
}
void CGameStateMenu::OnShow()
{
	bg.SetTopLeft(0, 0);
	bg.ShowBitmap();

}
/////////////////////////////////////////////////////
CGameStateWin::CGameStateWin(CGame *g)
	: CGameState(g)
{
}
void CGameStateWin::OnLButtonDown(UINT nFlags, CPoint point)
{
	if ((point.x > 320 && point.x < 510) && (point.y > 350 && point.y < 404))
	{
		GotoGameState(GAME_STATE_MENU);
	}
}
void CGameStateWin::OnMove()
{

}
void CGameStateWin::OnBeginState()
{

}
void CGameStateWin::OnInit()
{
	//
	// ��ϫܦh�ɡAOnInit���J�Ҧ����ϭn��ܦh�ɶ��C���קK���C�����H
	//     �������@�СA�C���|�X�{�uLoading ...�v�A���Loading���i�סC
	//
	ShowInitProgress(66);	// ���ӫe�@�Ӫ��A���i�סA���B�i�׵���66%
	//
	// �}�l���J���
	//
	gamewinspace.LoadBitmap(Win, RGB(255, 255, 255));
	alarm.LoadBitmap(Alarm, RGB(255, 255, 255));
	boygirl.LoadBitmap(BOYGIRL, RGB(255, 255, 255));
	dim.LoadBitmap(DIM, RGB(255, 255, 255));
	good.LoadBitmap(GOOD, RGB(255, 255, 255));
	bad.LoadBitmap(BAD, RGB(255, 255, 255));
	conti.LoadBitmap(CONTI, RGB(255, 255, 255));
	next.LoadBitmap(NEXT, RGB(255, 255, 255));
	gold.LoadBitmap(GOLD, RGB(255, 255, 255));
	//Sleep(300);				// ��C�A�H�K�ݲM���i�סA��ڹC���ЧR����Sleep
	//
	// �̲׶i�׬�100%
	//
	ShowInitProgress(100);
}
void CGameStateWin::OnShow()
{
	gamewinspace.SetTopLeft(130, 138);
	gamewinspace.ShowBitmap();
	alarm.SetTopLeft(270, 280);
	alarm.ShowBitmap();
	boygirl.SetTopLeft(270, 180);
	boygirl.ShowBitmap();
	dim.SetTopLeft(270, 240);
	dim.ShowBitmap();
	next.SetTopLeft(380, 231);
	next.ShowBitmap();
	gold.SetTopLeft(480, 231);
	gold.ShowBitmap();
	conti.SetTopLeft(320, 350);
	conti.ShowBitmap();
}
/////////////////////////////////////////////////////////////////////////////
// �o��class���C�����C�����檫��A�D�n���C���{�����b�o��
/////////////////////////////////////////////////////////////////////////////

CGameStateRun::CGameStateRun(CGame *g)
: CGameState(g), NUMRED(3),NUMICE(4), LAKERED(1), LAKEICE(1), LAKEGREEN(1), NUMMOD(2), NUMBUT(3)
{
	diamond1 = new RedDiamond[NUMRED];
	diamond2 = new IceDiamond[NUMICE];
	Lake1 = new RedLake[LAKERED];
	Lake2 = new IceLake[LAKEICE];
	Lake3 = new Greenlake[LAKEGREEN];
	mood = new Mood[NUMMOD];
	button = new Button[NUMBUT];
}

CGameStateRun::~CGameStateRun()
{
	if (diamond1 != NULL)
		delete[] diamond1;
	if (diamond2 != NULL)
		delete[] diamond2;
	if (Lake1 != NULL)
		delete[] Lake1;
	if (Lake2 != NULL)
		delete[] Lake2;
	if (Lake3 != NULL)
		delete[] Lake3;
	if (mood != NULL)
		delete[] mood;
	if (button != NULL)
		delete[] button;
}

void CGameStateRun::OnBeginState()
{
	const int HITS_LEFT = 0;
	const int HITS_LAKE = 1;
	const int HITS_DOOR = 1;
	const int HITS_LEFT_X = 590;
	const int HITS_LEFT_Y = 0;
	//const int STAGE = 1;
	gamemap.ReadFile(stage+1);
	for (int i = 0; i < NUMRED; i++) {				// �]�w�y���_�l�y��
		diamond1[i].SetXY(stage1_diamond1[i][0], stage1_diamond1[i][1]);
		diamond1[i].SetIsAlive(true);
	}
	for (int i = 0; i < NUMICE; i++) {				// �]�w�y���_�l�y��
		diamond2[i].SetXY(stage1_diamond2[i][0], stage1_diamond2[i][1]);
		diamond2[i].SetIsAlive(true);
	}
	for (int i = 0; i < LAKERED; i++) {				// �]�w�y���_�l�y��
		Lake1[i].SetXY(stage1_Lake1_position[i][0], stage1_Lake1_position[i][1]);
	}
	for (int i = 0; i < LAKEICE; i++) {				// �]�w�y���_�l�y��
		Lake2[i].SetXY(stage1_Lake2_position[i][0], stage1_Lake2_position[i][1]);
	}
	for (int i = 0; i < LAKEICE; i++) {				// �]�w�y���_�l�y��
		Lake3[i].SetXY(stage1_Lake3_position[i][0], stage1_Lake3_position[i][1]);
	}
	for (int i = 0; i < NUMMOD; i++) {				// �]�w�y���_�l�y��
		mood[i].SetXY(stage1_mood_position[i][0], stage1_mood_position[i][1]);
		mood[i].SetIsAlive(true);
	}
	for (int i = 0; i < NUMBUT; i++) {				// �]�w�y���_�l�y��
		button[i].SetXY(stage1_button_position[i][0], stage1_button_position[i][1]);
		button[i].SetIsAlive(true);
	}
	player1.Initialize(stage+1);
	player2.Initialize(stage+1);
	player1.SetXY(42, 542);
	player2.SetXY(42, 462);
	player2.SetXY(42, 462);
	reddoor.SetIsAlive(true);
	reddoor.SetXY(690, 60);
	icedoor.SetIsAlive(true);
	icedoor.SetXY(600, 60);
	box.init();
	box.SetXY(500, 160);

	background.SetTopLeft(0,0);				// �]�w�I�����_�l�y��
		// �]�w�����Ϫ��_�l�y��
	hits_left.SetInteger(HITS_LEFT);


	hits_lake.SetInteger(HITS_LAKE);
	hits_door.SetInteger(HITS_DOOR);
	hits_left.SetTopLeft(HITS_LEFT_X,HITS_LEFT_Y);		// ���w�ѤU�����ƪ��y��
	CAudio::Instance()->Play(AUDIO_LAKE, true);			// ���� WAVE
	CAudio::Instance()->Play(AUDIO_DING, false);		// ���� WAVE
	CAudio::Instance()->Play(AUDIO_NTUT, true);			// ���� MIDI
}

void CGameStateRun::OnMove()							// ���ʹC������
{
	int i;
	for (i = 0; i < NUMRED; i++)
		diamond1[i].OnMove();
	for (i = 0; i < NUMICE; i++)
	{
		diamond2[i].OnMove();
	}
	mood[0].OnMove();
	mood[1].OnMove1();
	button[0].OnMove();
	button[1].OnMove1();
	player1.MoodY(button[1].ReY());
	player2.MoodY(button[1].ReY());
	player1.OnMove();
	player2.OnMove();
	player1.OnMove1();
	player2.OnMove1();
	button[2].OnMove();
	reddoor.OnMove();
	icedoor.OnMove();
	box.OnMove();
	//
	// �P�_���l�O�_�I��y
	//

	for (i = 0; i < NUMRED; i++) {
		if (diamond1[i].IsAlive() && diamond1[i].HitPlayer(&player1)) {
			diamond1[i].SetIsAlive(false);
			CAudio::Instance()->Play(AUDIO_DING);
			hits_left.Add(1);
		}
	}
	for (i = 0; i < NUMICE; i++)
	{
		if (diamond2[i].IsAlive() && diamond2[i].HitPlayer(&player2)) {
			diamond2[i].SetIsAlive(false);
			CAudio::Instance()->Play(AUDIO_DING);
			hits_left.Add(1);
		}
	}
	for (i = 0; i < LAKERED; i++) {
		if ( Lake1[i].HitPlayer(&player2) && Lake1[i].hack == false) {
			CAudio::Instance()->Play(AUDIO_DING);
			hits_lake.Add(-1);
			//
			// �Y�Ѿl�I�����Ƭ�0�A�h����Game Over���A
			//
			if (hits_lake.GetInteger() <= 0) {
				CAudio::Instance()->Stop(AUDIO_LAKE);	// ���� WAVE
				CAudio::Instance()->Stop(AUDIO_NTUT);	// ���� MIDI
				GotoGameState(GAME_STATE_OVER);
			}
		}
	}
	for (i = 0; i < LAKEICE; i++)
	{
		if ( Lake2[i].HitPlayer(&player1)&& Lake2[i].hack==false) {
			CAudio::Instance()->Play(AUDIO_DING);
			hits_lake.Add(-1);
			//
			// �Y�Ѿl�I�����Ƭ�0�A�h����Game Over���A
			//
			if (hits_lake.GetInteger() <= 0) {
				CAudio::Instance()->Stop(AUDIO_LAKE);	// ���� WAVE
				CAudio::Instance()->Stop(AUDIO_NTUT);	// ���� MIDI
				GotoGameState(GAME_STATE_OVER);
			}
		}
	}
	for (i = 0; i < LAKEGREEN; i++)
	{
		if (Lake3[i].HitPlayer(&player1) && Lake3[i].hack == false) {
			CAudio::Instance()->Play(AUDIO_DING);
			hits_lake.Add(-1);
			//
			// �Y�Ѿl�I�����Ƭ�0�A�h����Game Over���A
			//
			if (hits_lake.GetInteger() <= 0) {
				CAudio::Instance()->Stop(AUDIO_LAKE);	// ���� WAVE
				CAudio::Instance()->Stop(AUDIO_NTUT);	// ���� MIDI
				GotoGameState(GAME_STATE_OVER);
			}
		}
	}
	if (box.HitEraser(&player1)||box.HitEraser(&player2)) {
		//player2.SetFloor(box.GetX1(), box.GetY1());
		//player1.SetFloor(box.GetX1(), box.GetY1());
		
		box.SetMovingLeft(true);
	}

	player1.setFront(player1.frontBox(box.GetX1(), box.GetY1()));
	player2.setFront(player2.frontBox(box.GetX1(), box.GetY1()));
	player1.setOnBox(player1.onBox(box.GetX1(), box.GetY1()));
	player2.setOnBox(player2.onBox(box.GetX1(), box.GetY1()));

	/*
	if (box.OnBox(player1.GetX1(), player1.GetX2(), player1.GetY1(), player1.GetY2())) {
		player1.SetFloor(box.GetY1() - 40);
	}
	if (box.OnBox(player2.GetX1(), player2.GetX2(), player2.GetY1(), player2.GetY2())) {
		player2.SetFloor(box.GetY1() - 40);
	}
	*/
	if (reddoor.IsAlive() && (reddoor.HitPlayer(&player1))) {
		reddoor.SetIsAlive(false);
	}
	if (!(reddoor.IsAlive()) && !(reddoor.HitPlayer(&player1))) {
		reddoor.SetIsAlive(true);
	}
	if (icedoor.IsAlive() && icedoor.HitPlayer(&player2)) {
		icedoor.SetIsAlive(false);
	}
	if (!(icedoor.IsAlive()) && !(icedoor.HitPlayer(&player2))) {
		icedoor.SetIsAlive(true);
	}
	if ((mood[0].IsAlive()) && (mood[0].HitPlayer(&player2))) {
		mood[0].SetIsAlive(false);
		mood[1].SetIsAlive(false);
		player1.SetMood(true);
		player2.SetMood(true);
	}
	if ((mood[0].IsAlive()) && (mood[0].HitPlayer(&player1))) {
		mood[0].SetIsAlive(false);
		mood[1].SetIsAlive(false);
		player1.SetMood(true);
		player2.SetMood(true);
	}
	/*if (!(mood[0].IsAlive()) && (mood[0].HitHitPlayer(&player2))) {
		mood[0].SetIsAlive(true);
		mood[1].SetIsAlive(true);
		player1.SetMood(false);
		player2.SetMood(false);
	}
	if (!(mood[0].IsAlive()) && (mood[0].HitHitPlayer(&player1))) {
		mood[0].SetIsAlive(true);
		mood[1].SetIsAlive(true);
		player1.SetMood(false);
		player2.SetMood(false);
	}*/
	if (button[0].IsAlive() && ((button[0].HitPlayer(&player2)) || button[0].HitPlayer(&player1))) {
		button[0].SetIsAlive(false);
		button[1].SetIsAlive(false);
		player1.SetButton(true);
		player2.SetButton(true);
	}
	if (button[2].IsAlive() && ((button[2].HitPlayer(&player2)) || button[2].HitPlayer(&player1))) {
		button[2].SetIsAlive(false);
		button[1].SetIsAlive(false);
		player1.SetButton(true);
		player2.SetButton(true);
	}
	if (!((button[0].IsAlive()) && (button[2].IsAlive())) && !(button[0].HitPlayer(&player1)) && !(button[0].HitPlayer(&player2)) && !(button[2].HitPlayer(&player1)) && !(button[2].HitPlayer(&player2))) {
		button[1].SetIsAlive(true);
		player1.SetButton(false);
		player2.SetButton(false);

	}
	if (!(button[0].IsAlive()) && !(button[0].HitPlayer(&player1)) && !(button[0].HitPlayer(&player2))) {
		button[0].SetIsAlive(true);
	}
	if (!(button[2].IsAlive()) && !(button[2].HitPlayer(&player1)) && !(button[2].HitPlayer(&player2))) {
		button[2].SetIsAlive(true);
	}
	
	if (!(icedoor.IsAlive()) && !(reddoor.IsAlive())) {
		GotoGameState(GAME_STATE_WIN);
	}
}

void CGameStateRun::OnInit()  								// �C������Ȥιϧγ]�w
{
	//
	// ��ϫܦh�ɡAOnInit���J�Ҧ����ϭn��ܦh�ɶ��C���קK���C�����H
	//     �������@�СA�C���|�X�{�uLoading ...�v�A���Loading���i�סC
	//
	ShowInitProgress(33);	// ���ӫe�@�Ӫ��A���i�סA���B�i�׵���33%
	//
	// �}�l���J���
	//
	int i;
	for (i = 0; i < NUMRED; i++)	
		diamond1[i].LoadBitmap();								// ���J��i�Ӳy���ϧ�
	for (i = 0; i < NUMICE; i++) {
		diamond2[i].LoadBitmap();
	}
	for (i = 0; i < LAKERED; i++)
		Lake1[i].LoadBitmap();								// ���J��i�Ӳy���ϧ�
	for (i = 0; i < LAKEICE; i++) {
		Lake2[i].LoadBitmap();
	}
	for (i = 0; i < LAKEGREEN; i++) {
		Lake3[i].LoadBitmap();
	}
	gamemap.LoadBitmap();
	player1.LoadBitmap();
	player2.LoadBitmap();
	reddoor.LoadBitmap();
	icedoor.LoadBitmap();
	for (i = 0; i < NUMMOD; i++) {
		mood[i].LoadBitmap();
	}
	for (i = 0; i < NUMBUT; i++) {
		button[i].LoadBitmap();
	}
	box.LoadBitmap();
	background.LoadBitmap(IDB_MAP1);					// ���J�I�����ϧ�
	//
	// ��������Loading�ʧ@�A�����i��
	//
	ShowInitProgress(50);
	Sleep(300); // ��C�A�H�K�ݲM���i�סA��ڹC���ЧR����Sleep
	//
	// �~����J��L���
	//
			// ���J�������ϧ�
	hits_left.LoadBitmap();

	CAudio::Instance()->Load(AUDIO_DING,  ".\\sounds\\ding.wav");	// ���J�s��0���n��ding.wav
	CAudio::Instance()->Load(AUDIO_LAKE,  ".\\sounds\\lake.mp3");	// ���J�s��1���n��lake.mp3
	CAudio::Instance()->Load(AUDIO_NTUT,  ".\\sounds\\LevelMusic.mp3");	// ���J�s��2���n��ntut.mid
	//
	// ��OnInit�ʧ@�|����CGameStaterOver::OnInit()�A�ҥH�i���٨S��100%
	//
}


void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const char KEY_LEFT  = 0x25; // keyboard���b�Y
	const char KEY_UP    = 0x26; // keyboard�W�b�Y
	const char KEY_RIGHT = 0x27; // keyboard�k�b�Y
	const char KEY_DOWN  = 0x28; // keyboard�U�b�Y
	const char KEY_A = 'A';
	const char KEY_W = 'W';
	const char KEY_D = 'D';
	const char KEY_S = 'S';
	const char KEY_P = 'P';

	if (nChar == KEY_LEFT)
	{

		player1.SetMovingLeft(true);

	}
	if (nChar == KEY_RIGHT) {

		player1.SetMovingRight(true);
	}
	if (nChar == KEY_UP)
	{
		player1.SetMovingUp(true);
	}
	if (nChar == KEY_DOWN)
	{
		player1.SetMovingDown(true);
	}
	if (nChar == KEY_A)
	{
		player2.SetMovingLeft(true);		
	}
	if (nChar == KEY_D) {

		player2.SetMovingRight(true);
	}
	if (nChar == KEY_W)
	{

		player2.SetMovingUp(true);
	}
	if (nChar == KEY_S)
	{

		player2.SetMovingDown(true);
	}
	if (nChar == KEY_P)
	{
		for (int i = 0; i < LAKERED; i++) {
			Lake1[i].hack = true;
		}
		for (int i = 0; i < LAKEICE; i++) {
			Lake2[i].hack= true;
		}
		for (int i = 0; i < LAKEGREEN; i++) {
			Lake3[i].hack = true;
		}
		hits_left.Add(10000);
	}
	//gamemap.OnKeyDown(nChar);
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const char KEY_LEFT  = 0x25; // keyboard���b�Y
	const char KEY_UP    = 0x26; // keyboard�W�b�Y
	const char KEY_RIGHT = 0x27; // keyboard�k�b�Y
	const char KEY_DOWN  = 0x28; // keyboard�U�b�Y
	const char KEY_A = 'A';
	const char KEY_W = 'W';
	const char KEY_D = 'D';
	const char KEY_S = 'S';
	if (nChar == KEY_LEFT)
	{

		player1.SetMovingLeft(false);
	}
	if (nChar == KEY_RIGHT) {

		player1.SetMovingRight(false);
	}
	if (nChar == KEY_UP)
	{

		player1.SetMovingUp(false);
	}
	if (nChar == KEY_DOWN)
	{

		player1.SetMovingDown(false);
	}
	if (nChar == KEY_A)
	{

		player2.SetMovingLeft(false);

	}
	if (nChar == KEY_D) {

		player2.SetMovingRight(false);
	}
	if (nChar == KEY_W)
	{

		player2.SetMovingUp(false);
	}
	if (nChar == KEY_S)
	{
		player2.SetMovingDown(false);
	}
}

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

void CGameStateRun::OnShow()
{
	//
	//  �`�N�GShow�̭��d�U���n���ʥ�󪫥󪺮y�СA���ʮy�Ъ��u�@����Move���~��A
	//        �_�h��������sø�Ϯ�(OnDraw)�A����N�|���ʡA�ݰ_�ӷ|�ܩǡC���ӳN�y
	//        ���AMove�t�dMVC����Model�AShow�t�dView�A��View�������Model�C
	//
	//
	//  �K�W�I���ϡB�����ơB�y�B���l�B�u�����y
	//
	background.ShowBitmap();			// �K�W�I����
	gamemap.OnShow();
					// �K�W������
	hits_left.ShowBitmap();

	for (int i=0; i < NUMRED; i++)
		diamond1[i].OnShow();				// �K�W��i���y
	for (int i = 0; i < NUMICE; i++)
	{
		diamond2[i].OnShow();
	}
	
	reddoor.OnShow();
	icedoor.OnShow();
	mood[0].OnShow();
	mood[1].OnShow1();
	button[0].OnShow();
	button[1].OnShow1();
	button[2].OnShow();
	box.OnShow();
	for (int i = 0; i < LAKERED; i++)
	{
		Lake1[i].OnShow();				// �K�W��i���y
	}
	for (int i = 0; i < LAKEICE; i++)
	{
		Lake2[i].OnShow();
	}
	for (int i = 0; i < LAKEGREEN; i++)
	{
		Lake3[i].OnShow();
	}
	player1.OnShow();
	player2.OnShow();
}
CGameStateRun2::CGameStateRun2(CGame *g)
	: CGameState(g), NUMRED(8), NUMICE(8), LAKERED(2), LAKEICE(2), LAKEGREEN(2), NUMMOD(0), NUMBUT(3), NUMBUT1(3)
{
	diamond1 = new RedDiamond[NUMRED];
	diamond2 = new IceDiamond[NUMICE];
	Lake1 = new RedLake[LAKERED];
	Lake2 = new IceLake[LAKEICE];
	Lake3 = new Greenlake[LAKEGREEN];
	mood = new Mood[NUMMOD];
	button = new Button[NUMBUT];
	button1 = new Button[NUMBUT1];
}

CGameStateRun2::~CGameStateRun2()
{
	if (diamond1 != NULL)
		delete[] diamond1;
	if (diamond2 != NULL)
		delete[] diamond2;
	if (Lake1 != NULL)
		delete[] Lake1;
	if (Lake2 != NULL)
		delete[] Lake2;
	if (Lake3 != NULL)
		delete[] Lake3;
	if (mood != NULL)
		delete[] mood;
	if (button != NULL)
		delete[] button;
	if (button1 != NULL)
		delete[] button1;
}

void CGameStateRun2::OnBeginState()
{
	//const int HITS_LEFT = 0;
	const int HITS_LAKE = 1;
	const int HITS_DOOR = 1;
	const int HITS_LEFT_X = 590;
	const int HITS_LEFT_Y = 0;
	//const int STAGE = 1;
	gamemap.ReadFile(stage+1);
	for (int i = 0; i < NUMRED; i++) {				// �]�w�y���_�l�y��
		diamond1[i].SetXY(stage2_diamond1[i][0], stage2_diamond1[i][1]);
		diamond1[i].SetIsAlive(true);
	}
	for (int i = 0; i < NUMICE; i++) {				// �]�w�y���_�l�y��
		diamond2[i].SetXY(stage2_diamond2[i][0], stage2_diamond2[i][1]);
		diamond2[i].SetIsAlive(true);
	}
	for (int i = 0; i < LAKERED; i++) {				// �]�w�y���_�l�y��
		Lake1[i].SetXY(stage2_Lake1_position[i][0], stage2_Lake1_position[i][1]);
	}
	for (int i = 0; i < LAKEICE; i++) {				// �]�w�y���_�l�y��
		Lake2[i].SetXY(stage2_Lake2_position[i][0], stage2_Lake2_position[i][1]);
	}
	for (int i = 0; i < LAKEICE; i++) {				// �]�w�y���_�l�y��
		Lake3[i].SetXY(stage2_Lake3_position[i][0], stage2_Lake3_position[i][1]);
	}
	for (int i = 0; i < NUMMOD; i++) {				// �]�w�y���_�l�y��
		mood[i].SetXY(stage2_mood_position[i][0], stage2_mood_position[i][1]);
		mood[i].SetIsAlive(true);
	}
	for (int i = 0; i < NUMBUT; i++) {				// �]�w�y���_�l�y��
		button[i].SetXY(stage2_button_position[i][0], stage2_button_position[i][1]);
		button[i].SetIsAlive(true);
	}
	for (int i = 0; i < NUMBUT1; i++) {				// �]�w�y���_�l�y��
		button1[i].SetXY(stage2_button_position1[i][0], stage2_button_position1[i][1]);
		button1[i].SetIsAlive(true);
	}
	player1.Initialize(stage+1);
	player2.Initialize(stage+1);
	player1.SetXY(28, 542);
	player2.SetXY(80, 542);
	reddoor.SetIsAlive(true);
	reddoor.SetXY(34, 52);
	icedoor.SetIsAlive(true);
	icedoor.SetXY(106, 52);

	background.SetTopLeft(0, 0);				// �]�w�I�����_�l�y��
		// �]�w�����Ϫ��_�l�y��
	//hits_left.SetInteger(HITS_LEFT);


	hits_lake.SetInteger(HITS_LAKE);
	hits_door.SetInteger(HITS_DOOR);
	hits_left.SetTopLeft(HITS_LEFT_X, HITS_LEFT_Y);		// ���w�ѤU�����ƪ��y��
	CAudio::Instance()->Play(AUDIO_LAKE, true);			// ���� WAVE
	CAudio::Instance()->Play(AUDIO_DING, false);		// ���� WAVE
	CAudio::Instance()->Play(AUDIO_NTUT, true);			// ���� MIDI
}

void CGameStateRun2::OnMove()							// ���ʹC������
{
	int i;
	for (i = 0; i < NUMRED; i++)
		diamond1[i].OnMove();
	for (i = 0; i < NUMICE; i++)
	{
		diamond2[i].OnMove();
	}
	mood[0].OnMove();
	mood[1].OnMove1();
	button[0].OnMove();
	button[1].OnMove2();
	button[2].OnMove();
	button1[0].OnMove();
	button1[1].OnMove3();
	button1[2].OnMove();
	player1.MoodY(button[1].ReY());
	player2.MoodY(button[1].ReY());
	player1.OnMove();
	player2.OnMove();
	player1.OnMove1();
	player2.OnMove1();
	reddoor.OnMove();
	icedoor.OnMove();
	//
	// �P�_���l�O�_�I��y
	//

	for (i = 0; i < NUMRED; i++) {
		if (diamond1[i].IsAlive() && diamond1[i].HitPlayer(&player1)) {
			diamond1[i].SetIsAlive(false);
			CAudio::Instance()->Play(AUDIO_DING);
			hits_left.Add(1);
		}
	}
	for (i = 0; i < NUMICE; i++)
	{
		if (diamond2[i].IsAlive() && diamond2[i].HitPlayer(&player2)) {
			diamond2[i].SetIsAlive(false);
			CAudio::Instance()->Play(AUDIO_DING);
			hits_left.Add(1);
		}
	}
	for (i = 0; i < LAKERED; i++) {
		if (Lake1[i].HitPlayer(&player2) && Lake1[i].hack == false) {
			CAudio::Instance()->Play(AUDIO_DING);
			hits_lake.Add(-1);
			//
			// �Y�Ѿl�I�����Ƭ�0�A�h����Game Over���A
			//
			if (hits_lake.GetInteger() <= 0) {
				CAudio::Instance()->Stop(AUDIO_LAKE);	// ���� WAVE
				CAudio::Instance()->Stop(AUDIO_NTUT);	// ���� MIDI
				GotoGameState(GAME_STATE_OVER);
			}
		}
	}
	for (i = 0; i < LAKEICE; i++)
	{
		if (Lake2[i].HitPlayer(&player1) && Lake2[i].hack == false) {
			CAudio::Instance()->Play(AUDIO_DING);
			hits_lake.Add(-1);
			//
			// �Y�Ѿl�I�����Ƭ�0�A�h����Game Over���A
			//
			if (hits_lake.GetInteger() <= 0) {
				CAudio::Instance()->Stop(AUDIO_LAKE);	// ���� WAVE
				CAudio::Instance()->Stop(AUDIO_NTUT);	// ���� MIDI
				GotoGameState(GAME_STATE_OVER);
			}
		}
	}
	for (i = 0; i < LAKEGREEN; i++)
	{
		if (Lake3[i].HitPlayer(&player1) && Lake3[i].hack == false) {
			CAudio::Instance()->Play(AUDIO_DING);
			hits_lake.Add(-1);
			//
			// �Y�Ѿl�I�����Ƭ�0�A�h����Game Over���A
			//
			if (hits_lake.GetInteger() <= 0) {
				CAudio::Instance()->Stop(AUDIO_LAKE);	// ���� WAVE
				CAudio::Instance()->Stop(AUDIO_NTUT);	// ���� MIDI
				GotoGameState(GAME_STATE_OVER);
			}
		}
	}
	


	/*
	if (box.OnBox(player1.GetX1(), player1.GetX2(), player1.GetY1(), player1.GetY2())) {
		player1.SetFloor(box.GetY1() - 40);
	}
	if (box.OnBox(player2.GetX1(), player2.GetX2(), player2.GetY1(), player2.GetY2())) {
		player2.SetFloor(box.GetY1() - 40);
	}
	*/
	if (reddoor.IsAlive() && (reddoor.HitPlayer(&player1))) {
		reddoor.SetIsAlive(false);
	}
	if (!(reddoor.IsAlive()) && !(reddoor.HitPlayer(&player1))) {
		reddoor.SetIsAlive(true);
	}
	if (icedoor.IsAlive() && icedoor.HitPlayer(&player2)) {
		icedoor.SetIsAlive(false);
	}
	if (!(icedoor.IsAlive()) && !(icedoor.HitPlayer(&player2))) {
		icedoor.SetIsAlive(true);
	}
	if ((mood[0].IsAlive()) && (mood[0].HitPlayer(&player2))) {
		mood[0].SetIsAlive(false);
		mood[1].SetIsAlive(false);
		player1.SetMood(true);
		player2.SetMood(true);
	}
	if ((mood[0].IsAlive()) && (mood[0].HitPlayer(&player1))) {
		mood[0].SetIsAlive(false);
		mood[1].SetIsAlive(false);
		player1.SetMood(true);
		player2.SetMood(true);
	}
	/*if (!(mood[0].IsAlive()) && (mood[0].HitHitPlayer(&player2))) {
		mood[0].SetIsAlive(true);
		mood[1].SetIsAlive(true);
		player1.SetMood(false);
	}
	if (!(mood[0].IsAlive()) && (mood[0].HitHitPlayer(&player1))) {
		mood[0].SetIsAlive(true);
		mood[1].SetIsAlive(true);
		player1.SetMood(false);
	}*/
	if (button[0].IsAlive() && ((button[0].HitPlayer(&player2)) || button[0].HitPlayer(&player1))) {
		button[0].SetIsAlive(false);
		button[1].SetIsAlive(false);
	}
	if (button[2].IsAlive() && ((button[2].HitPlayer(&player2)) || button[2].HitPlayer(&player1))) {
		button[2].SetIsAlive(false);
		button[1].SetIsAlive(false);
	}
	if (!((button[0].IsAlive()) && (button[2].IsAlive())) && !(button[0].HitPlayer(&player1)) && !(button[0].HitPlayer(&player2)) && !(button[2].HitPlayer(&player1)) && !(button[2].HitPlayer(&player2))) {
		button[1].SetIsAlive(true);
	}
	if (!(button[0].IsAlive()) && !(button[0].HitPlayer(&player1)) && !(button[0].HitPlayer(&player2))) {
		button[0].SetIsAlive(true);
	}
	if (!(button[2].IsAlive()) && !(button[2].HitPlayer(&player1)) && !(button[2].HitPlayer(&player2))) {
		button[2].SetIsAlive(true);
	}

	if (button1[0].IsAlive() && ((button1[0].HitPlayer(&player2)) || button1[0].HitPlayer(&player1))) {
		button1[0].SetIsAlive(false);
		button1[1].SetIsAlive(false);
		player1.SetButton2(true);
		player2.SetButton2(true);
	}
	if (button1[2].IsAlive() && ((button1[2].HitPlayer(&player2)) || button1[2].HitPlayer(&player1))) {
		button1[2].SetIsAlive(false);
		button1[1].SetIsAlive(false);
		player1.SetButton2(true);
		player2.SetButton2(true);
	}
	if (!((button1[0].IsAlive()) && (button1[2].IsAlive())) && !(button1[0].HitPlayer(&player1)) && !(button1[0].HitPlayer(&player2)) && !(button1[2].HitPlayer(&player1)) && !(button1[2].HitPlayer(&player2))) {
		button1[1].SetIsAlive(true);
		player1.SetButton2(false);
		player2.SetButton2(false);
	}
	if (!(button1[0].IsAlive()) && !(button1[0].HitPlayer(&player1)) && !(button1[0].HitPlayer(&player2))) {
		button[0].SetIsAlive(true);
	}
	if (!(button1[2].IsAlive()) && !(button1[2].HitPlayer(&player1)) && !(button1[2].HitPlayer(&player2))) {
		button1[2].SetIsAlive(true);
	}

	if (!(icedoor.IsAlive()) && !(reddoor.IsAlive())) {
		GotoGameState(GAME_STATE_WIN);
	}
}

void CGameStateRun2::OnInit()  								// �C������Ȥιϧγ]�w
{
	//
	// ��ϫܦh�ɡAOnInit���J�Ҧ����ϭn��ܦh�ɶ��C���קK���C�����H
	//     �������@�СA�C���|�X�{�uLoading ...�v�A���Loading���i�סC
	//
	ShowInitProgress(33);	// ���ӫe�@�Ӫ��A���i�סA���B�i�׵���33%
	//
	// �}�l���J���
	//
	int i;
	for (i = 0; i < NUMRED; i++)
		diamond1[i].LoadBitmap();								// ���J��i�Ӳy���ϧ�
	for (i = 0; i < NUMICE; i++) {
		diamond2[i].LoadBitmap();
	}
	for (i = 0; i < LAKERED; i++)
		Lake1[i].LoadBitmap();								// ���J��i�Ӳy���ϧ�
	for (i = 0; i < LAKEICE; i++) {
		Lake2[i].LoadBitmap();
	}
	for (i = 0; i < LAKEGREEN; i++) {
		Lake3[i].LoadBitmap();
	}
	gamemap.LoadBitmap();
	player1.LoadBitmap();
	player2.LoadBitmap();
	reddoor.LoadBitmap();
	icedoor.LoadBitmap();
	for (i = 0; i < NUMMOD; i++) {
		mood[i].LoadBitmap();
	}
	for (i = 0; i < NUMBUT; i++) {
		button[i].LoadBitmap();
	}
	for (i = 0; i < NUMBUT1; i++) {
		button1[i].LoadBitmap();
	}
	background.LoadBitmap(IDB_MAP1);					// ���J�I�����ϧ�
	//
	// ��������Loading�ʧ@�A�����i��
	//
	ShowInitProgress(50);
	Sleep(300); // ��C�A�H�K�ݲM���i�סA��ڹC���ЧR����Sleep
	//
	// �~����J��L���
	//
			// ���J�������ϧ�
	//hits_left.LoadBitmap();

	//CAudio::Instance()->Load(AUDIO_DING, ".\\sounds\\ding.wav");	// ���J�s��0���n��ding.wav
	//CAudio::Instance()->Load(AUDIO_LAKE, ".\\sounds\\lake.mp3");	// ���J�s��1���n��lake.mp3
	//CAudio::Instance()->Load(AUDIO_NTUT, ".\\sounds\\LevelMusic.mp3");	// ���J�s��2���n��ntut.mid
	//
	// ��OnInit�ʧ@�|����CGameStaterOver::OnInit()�A�ҥH�i���٨S��100%
	//
}


void CGameStateRun2::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const char KEY_LEFT = 0x25; // keyboard���b�Y
	const char KEY_UP = 0x26; // keyboard�W�b�Y
	const char KEY_RIGHT = 0x27; // keyboard�k�b�Y
	const char KEY_DOWN = 0x28; // keyboard�U�b�Y
	const char KEY_A = 'A';
	const char KEY_W = 'W';
	const char KEY_D = 'D';
	const char KEY_S = 'S';
	const char KEY_P = 'P';

	if (nChar == KEY_LEFT)
	{

		player1.SetMovingLeft(true);

	}
	if (nChar == KEY_RIGHT) {

		player1.SetMovingRight(true);
	}
	if (nChar == KEY_UP)
	{
		player1.SetMovingUp(true);
	}
	if (nChar == KEY_DOWN)
	{
		player1.SetMovingDown(true);
	}
	if (nChar == KEY_A)
	{
		player2.SetMovingLeft(true);
	}
	if (nChar == KEY_D) {

		player2.SetMovingRight(true);
	}
	if (nChar == KEY_W)
	{

		player2.SetMovingUp(true);
	}
	if (nChar == KEY_S)
	{

		player2.SetMovingDown(true);
	}
	if (nChar == KEY_P)
	{
		for (int i = 0; i < LAKERED; i++) {
			Lake1[i].hack = true;
		}
		for (int i = 0; i < LAKEICE; i++) {
			Lake2[i].hack = true;
		}
		for (int i = 0; i < LAKEGREEN; i++) {
			Lake3[i].hack = true;
		}
		hits_left.Add(10000);
	}
	//gamemap.OnKeyDown(nChar);
}

void CGameStateRun2::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const char KEY_LEFT = 0x25; // keyboard���b�Y
	const char KEY_UP = 0x26; // keyboard�W�b�Y
	const char KEY_RIGHT = 0x27; // keyboard�k�b�Y
	const char KEY_DOWN = 0x28; // keyboard�U�b�Y
	const char KEY_A = 'A';
	const char KEY_W = 'W';
	const char KEY_D = 'D';
	const char KEY_S = 'S';
	if (nChar == KEY_LEFT)
	{

		player1.SetMovingLeft(false);
	}
	if (nChar == KEY_RIGHT) {

		player1.SetMovingRight(false);
	}
	if (nChar == KEY_UP)
	{

		player1.SetMovingUp(false);
	}
	if (nChar == KEY_DOWN)
	{

		player1.SetMovingDown(false);
	}
	if (nChar == KEY_A)
	{

		player2.SetMovingLeft(false);

	}
	if (nChar == KEY_D) {

		player2.SetMovingRight(false);
	}
	if (nChar == KEY_W)
	{

		player2.SetMovingUp(false);
	}
	if (nChar == KEY_S)
	{
		player2.SetMovingDown(false);
	}
}

void CGameStateRun2::OnLButtonDown(UINT nFlags, CPoint point)  // �B�z�ƹ����ʧ@
{

}

void CGameStateRun2::OnLButtonUp(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
{

}

void CGameStateRun2::OnMouseMove(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
{
	// �S�ơC�p�G�ݭn�B�z�ƹ����ʪ��ܡA�gcode�b�o��
}

void CGameStateRun2::OnRButtonDown(UINT nFlags, CPoint point)  // �B�z�ƹ����ʧ@
{

}

void CGameStateRun2::OnRButtonUp(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
{

}

void CGameStateRun2::OnShow()
{
	//
	//  �`�N�GShow�̭��d�U���n���ʥ�󪫥󪺮y�СA���ʮy�Ъ��u�@����Move���~��A
	//        �_�h��������sø�Ϯ�(OnDraw)�A����N�|���ʡA�ݰ_�ӷ|�ܩǡC���ӳN�y
	//        ���AMove�t�dMVC����Model�AShow�t�dView�A��View�������Model�C
	//
	//
	//  �K�W�I���ϡB�����ơB�y�B���l�B�u�����y
	//
	background.ShowBitmap();			// �K�W�I����
	gamemap.OnShow();
	
	// �K�W������
	//hits_left.ShowBitmap();

	for (int i = 0; i < NUMRED; i++)
		diamond1[i].OnShow();				// �K�W��i���y
	for (int i = 0; i < NUMICE; i++)
	{
		diamond2[i].OnShow();
	}
	
	reddoor.OnShow();
	icedoor.OnShow();
	for (int i = 0; i < NUMMOD; i++)
	{
		mood[i].OnShow();				// �K�W��i���y
	}
	button[0].OnShow();
	button[1].OnShow2();
	button[2].OnShow();
	button1[0].OnShow();
	button1[1].OnShow3();
	button1[2].OnShow();
	for (int i = 0; i < LAKERED; i++)
	{
		Lake1[i].OnShow();				// �K�W��i���y
	}
	for (int i = 0; i < LAKEICE; i++)
	{
		Lake2[i].OnShow();
	}
	for (int i = 0; i < LAKEGREEN; i++)
	{
		Lake3[i].OnShow();
	}
	player1.OnShow();
	player2.OnShow();
}
}
