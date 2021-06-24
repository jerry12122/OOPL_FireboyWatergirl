/*
 * mygame.cpp: 本檔案儲遊戲本身的class的implementation
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
// 這個class為遊戲的遊戲開頭畫面物件
/////////////////////////////////////////////////////////////////////////////

CGameStateInit::CGameStateInit(CGame *g)
: CGameState(g)
{
}

void CGameStateInit::OnInit()
{
	//
	// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
	//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
	//
	ShowInitProgress(0);	// 一開始的loading進度為0%
	//
	// 開始載入資料
	//
	logo.LoadBitmap(IDB_GAME_MENU);
	//Sleep(300);				// 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
	//
	// 此OnInit動作會接到CGameStaterRun::OnInit()，所以進度還沒到100%
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
		PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE, 0, 0);	// 關閉遊戲
	/*
		GotoGameState(GAME_STATE_RUN);						// 切換至GAME_STATE_RUN
	else if (nChar == KEY_ESC)								// Demo 關閉遊戲的方法
		*/
}

void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point)
{
	if ((point.x > 303 && point.x < 485) && (point.y > 311 && point.y < 375))
	{
		GotoGameState(GAME_STATE_MENU);
	}
	
		// 切換至GAME_STATE_RUN
}

void CGameStateInit::OnShow()
{
	//
	// 貼上logo
	//
	logo.SetTopLeft(0, 0);
	logo.ShowBitmap();
	//
	// Demo螢幕字型的使用，不過開發時請盡量避免直接使用字型，改用CMovingBitmap比較好
	//
	/*
	CDC *pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC 
	CFont f,*fp;
	f.CreatePointFont(160,"Times New Roman");	// 產生 font f; 160表示16 point的字
	fp=pDC->SelectObject(&f);					// 選用 font f
	pDC->SetBkColor(RGB(0,0,0));
	pDC->SetTextColor(RGB(255,255,0));
	pDC->TextOut(120,220,"Please click mouse or press SPACE to begin.");
	pDC->TextOut(5,395,"Press Ctrl-F to switch in between window mode and full screen mode.");
	if (ENABLE_GAME_PAUSE)
		pDC->TextOut(5,425,"Press Ctrl-Q to pause the Game.");
	pDC->TextOut(5,455,"Press Alt-F4 or ESC to Quit.");
	pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
	CDDraw::ReleaseBackCDC();
	*/
	// 放掉 Back Plain 的 CDC
}								

/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的結束狀態(Game Over)
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
		GotoGameState(GAME_STATE_RUN);
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
	// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
	//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
	//
	ShowInitProgress(66);	// 接個前一個狀態的進度，此處進度視為66%
	//
	// 開始載入資料
	//
	gameover.LoadBitmap(GAMEOVER, RGB(255, 255, 255));
	//Sleep(300);				// 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
	//
	// 最終進度為100%
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
		GotoGameState(GAME_STATE_RUN);
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
	// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
	//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
	//
	ShowInitProgress(66);	// 接個前一個狀態的進度，此處進度視為66%
	//
	// 開始載入資料
	//
	bg.LoadBitmap(IDB_MENU, RGB(255, 255, 255));

	//Sleep(300);				// 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
	//
	// 最終進度為100%
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
		GotoGameState(GAME_STATE_INIT);
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
	// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
	//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
	//
	ShowInitProgress(66);	// 接個前一個狀態的進度，此處進度視為66%
	//
	// 開始載入資料
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
	//Sleep(300);				// 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
	//
	// 最終進度為100%
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
// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
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
	delete[] diamond1;
	delete[] diamond2;
	delete[] Lake1;
	delete[] Lake2;
	delete[] Lake3;
	delete[] mood;
	delete[] button;
}

void CGameStateRun::OnBeginState()
{
	const int BALL_GAP = 90;
	const int BALL_XY_OFFSET = 45;
	const int BALL_PER_ROW = 7;
	const int HITS_LEFT = 0;
	const int HITS_LAKE = 1;
	const int HITS_DOOR = 1;
	const int HITS_LEFT_X = 590;
	const int HITS_LEFT_Y = 0;
	const int BACKGROUND_X = 60;
	const int ANIMATION_SPEED = 15;
	const int STAGE = 1;
	const int diamond1_position[3][2] = { {405,535},{140,260},{223,41} };
	for (int i = 0; i < NUMRED; i++) {				// 設定球的起始座標
		diamond1[i].SetXY(diamond1_position[i][0], diamond1_position[i][1]);
		diamond1[i].SetIsAlive(true);
	}
	const int diamond2_position[4][2] = { {570,535},{470,290},{475,87},{35,109} };
	for (int i = 0; i < NUMICE; i++) {				// 設定球的起始座標
		diamond2[i].SetXY(diamond2_position[i][0], diamond2_position[i][1]);
		diamond2[i].SetIsAlive(true);
	}
	const int Lake1_position[1][2] = { {360,579} };
	for (int i = 0; i < LAKERED; i++) {				// 設定球的起始座標
		Lake1[i].SetXY(Lake1_position[i][0], Lake1_position[i][1]);

	}
	const int Lake2_position[1][2] = { {530,579}};
	for (int i = 0; i < LAKEICE; i++) {				// 設定球的起始座標
		Lake2[i].SetXY(Lake2_position[i][0], Lake2_position[i][1]);
	}
	const int Lake3_position[1][2] = { {460,455} };
	for (int i = 0; i < LAKEICE; i++) {				// 設定球的起始座標
		Lake3[i].SetXY(Lake3_position[i][0], Lake3_position[i][1]);
	}
	const int mood_position[2][2] = { {260,380},{20,310} };
	for (int i = 0; i < NUMMOD; i++) {				// 設定球的起始座標
		mood[i].SetXY(mood_position[i][0], mood_position[i][1]);
		mood[i].SetIsAlive(true);
	}
	
	gamemap.ReadFile();
	player1.Initialize();
	player2.Initialize();
	player1.SetXY(42, 542);
	reddoor.SetIsAlive(true);
	reddoor.SetXY(690, 60);
	icedoor.SetIsAlive(true);
	icedoor.SetXY(600, 60);
	box.init();
	box.SetXY(500, 160);
	const int button_position[3][2] = { {270,295},{710,230} ,{600,215} };
	for (int i = 0; i < NUMBUT; i++) {				// 設定球的起始座標
		button[i].SetXY(button_position[i][0], button_position[i][1]);
		button[i].SetIsAlive(true);
	}

	background.SetTopLeft(0,0);				// 設定背景的起始座標
	help.SetTopLeft(0, SIZE_Y - help.Height());			// 設定說明圖的起始座標
	hits_left.SetInteger(HITS_LEFT);


	hits_lake.SetInteger(HITS_LAKE);
	hits_door.SetInteger(HITS_DOOR);
	hits_left.SetTopLeft(HITS_LEFT_X,HITS_LEFT_Y);		// 指定剩下撞擊數的座標
	CAudio::Instance()->Play(AUDIO_LAKE, true);			// 撥放 WAVE
	CAudio::Instance()->Play(AUDIO_DING, false);		// 撥放 WAVE
	CAudio::Instance()->Play(AUDIO_NTUT, true);			// 撥放 MIDI
}

void CGameStateRun::OnMove()							// 移動遊戲元素
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
	player1.OnMove();
	player2.OnMove();
	player1.OnMove1();
	button[2].OnMove();
	reddoor.OnMove();
	icedoor.OnMove();
	box.OnMove();
	//
	// 判斷擦子是否碰到球
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
			// 若剩餘碰撞次數為0，則跳到Game Over狀態
			//
			if (hits_lake.GetInteger() <= 0) {
				CAudio::Instance()->Stop(AUDIO_LAKE);	// 停止 WAVE
				CAudio::Instance()->Stop(AUDIO_NTUT);	// 停止 MIDI
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
			// 若剩餘碰撞次數為0，則跳到Game Over狀態
			//
			if (hits_lake.GetInteger() <= 0) {
				CAudio::Instance()->Stop(AUDIO_LAKE);	// 停止 WAVE
				CAudio::Instance()->Stop(AUDIO_NTUT);	// 停止 MIDI
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
			// 若剩餘碰撞次數為0，則跳到Game Over狀態
			//
			if (hits_lake.GetInteger() <= 0) {
				CAudio::Instance()->Stop(AUDIO_LAKE);	// 停止 WAVE
				CAudio::Instance()->Stop(AUDIO_NTUT);	// 停止 MIDI
				GotoGameState(GAME_STATE_OVER);
			}
		}
	}
	if (box.HitEraser(&player1)||box.HitEraser(&player2)) {
		box.SetMovingLeft(true);
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
	}
	if ((mood[0].IsAlive()) && (mood[0].HitPlayer(&player1))) {
		mood[0].SetIsAlive(false);
		mood[1].SetIsAlive(false);
		player1.SetMood(true);
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
		player1.SetButton(true);
	}
	if (button[2].IsAlive() && ((button[2].HitPlayer(&player2)) || button[2].HitPlayer(&player1))) {
		button[2].SetIsAlive(false);
		button[1].SetIsAlive(false);
		player1.SetButton(true);
	}
	if (!((button[0].IsAlive()) && (button[2].IsAlive())) && !(button[0].HitPlayer(&player1)) && !(button[0].HitPlayer(&player2)) && !(button[2].HitPlayer(&player1)) && !(button[2].HitPlayer(&player2))) {
		button[1].SetIsAlive(true);
		player1.SetButton(false);

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

void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
{
	//
	// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
	//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
	//
	ShowInitProgress(33);	// 接個前一個狀態的進度，此處進度視為33%
	//
	// 開始載入資料
	//
	int i;
	for (i = 0; i < NUMRED; i++)	
		diamond1[i].LoadBitmap();								// 載入第i個球的圖形
	for (i = 0; i < NUMICE; i++) {
		diamond2[i].LoadBitmap();
	}
	for (i = 0; i < LAKERED; i++)
		Lake1[i].LoadBitmap();								// 載入第i個球的圖形
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
	background.LoadBitmap(IDB_MAP1);					// 載入背景的圖形
	//
	// 完成部分Loading動作，提高進度
	//
	ShowInitProgress(50);
	Sleep(300); // 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
	//
	// 繼續載入其他資料
	//
	help.LoadBitmap(IDB_HELP,RGB(255,255,255));				// 載入說明的圖形
	hits_left.LoadBitmap();

	CAudio::Instance()->Load(AUDIO_DING,  ".\\sounds\\ding.wav");	// 載入編號0的聲音ding.wav
	CAudio::Instance()->Load(AUDIO_LAKE,  ".\\sounds\\lake.mp3");	// 載入編號1的聲音lake.mp3
	CAudio::Instance()->Load(AUDIO_NTUT,  ".\\sounds\\ntut.mid");	// 載入編號2的聲音ntut.mid
	//
	// 此OnInit動作會接到CGameStaterOver::OnInit()，所以進度還沒到100%
	//




}


void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const char KEY_LEFT  = 0x25; // keyboard左箭頭
	const char KEY_UP    = 0x26; // keyboard上箭頭
	const char KEY_RIGHT = 0x27; // keyboard右箭頭
	const char KEY_DOWN  = 0x28; // keyboard下箭頭
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
	const char KEY_LEFT  = 0x25; // keyboard左箭頭
	const char KEY_UP    = 0x26; // keyboard上箭頭
	const char KEY_RIGHT = 0x27; // keyboard右箭頭
	const char KEY_DOWN  = 0x28; // keyboard下箭頭
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

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{

}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{

}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
	// 沒事。如果需要處理滑鼠移動的話，寫code在這裡
}

void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{

}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{

}

void CGameStateRun::OnShow()
{
	//
	//  注意：Show裡面千萬不要移動任何物件的座標，移動座標的工作應由Move做才對，
	//        否則當視窗重新繪圖時(OnDraw)，物件就會移動，看起來會很怪。換個術語
	//        說，Move負責MVC中的Model，Show負責View，而View不應更動Model。
	//
	//
	//  貼上背景圖、撞擊數、球、擦子、彈跳的球
	//
	background.ShowBitmap();			// 貼上背景圖
	gamemap.OnShow();
	help.ShowBitmap();					// 貼上說明圖
	hits_left.ShowBitmap();

	for (int i=0; i < NUMRED; i++)
		diamond1[i].OnShow();				// 貼上第i號球
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
		Lake1[i].OnShow();				// 貼上第i號球
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