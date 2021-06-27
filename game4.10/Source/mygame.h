/*
 * mygame.h: 本檔案儲遊戲本身的class的interface
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
 *	 2004-03-02 V4.0
 *      1. Add CGameStateInit, CGameStateRun, and CGameStateOver to
 *         demonstrate the use of states.
 *   2005-09-13
 *      Rewrite the codes for CBall and CEraser.
 *   2005-09-20 V4.2Beta1.
 *   2005-09-29 V4.2Beta2.
 *   2006-02-08 V4.2
 *      1. Rename OnInitialUpdate() -> OnInit().
 *      2. Replace AUDIO_CANYON as AUDIO_NTUT.
 *      3. Add help bitmap to CGameStateRun.
 *   2006-09-09 V4.3
 *      1. Rename Move() and Show() as OnMove and OnShow() to emphasize that they are
 *         event driven.
 *   2008-02-15 V4.4
 *      1. Add namespace game_framework.
 *      2. Replace the demonstration of animation as a new bouncing ball.
 *      3. Use ShowInitProgress(percent) to display loading progress.
*/

#include "RedDiamond.h"
#include "IceDiamond.h"
#include "IcePlayer.h"
#include "RedPlayer.h"
#include "Button.h"
#include "RedDoor.h"
#include "IceDoor.h"
#include "RedLake.h"
#include "IceLake.h"
#include "Mood.h"
#include "box.h"
#include "Greenlake.h"
#include <fstream> 
extern bool current_rank;

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// Constants
	/////////////////////////////////////////////////////////////////////////////

	enum AUDIO_ID {				// 定義各種音效的編號
		AUDIO_DING,				// 0
		AUDIO_LAKE,				// 1
		AUDIO_NTUT				// 2
	};

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的遊戲開頭畫面物件
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateInit : public CGameState {
	public:
		CGameStateInit(CGame *g);
		void OnInit();  								// 遊戲的初值及圖形設定
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnKeyUp(UINT, UINT, UINT); 				// 處理鍵盤Up的動作
		void OnLButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
	protected:
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		CMovingBitmap logo,intro,intro2;				
		bool intro_bool;
	};

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲第一關的狀態(Game Run 1)
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateRun : public CGameState {
	public:
		CGameStateRun(CGame *g);
		~CGameStateRun();
		CGameMap gamemap;
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnInit();  								// 遊戲的初值及圖形設定
		void OnKeyDown(UINT, UINT, UINT);
		void OnKeyUp(UINT, UINT, UINT);
	protected:
		void OnMove();									// 移動遊戲元素
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		bool JUMP, UP;
		
		const int		NUMRED;		// 火鑽的總數
		const int		NUMICE;		// 冰鑽的總數
		const int		LAKERED;	// 紅水的總數
		const int		LAKEICE;	// 藍水的總數
		const int		LAKEGREEN;	// 綠水的總數
		const int		NUMMOD;		// 拉桿的總數
		const int		NUMBUT;		// 按鈕的總數
		CMovingBitmap	background;	// 背景圖

		RedDiamond		*diamond1;	
		IceDiamond		*diamond2;
		CInteger		hits_left;
		CInteger		hits_lake;	
		CInteger		hits_door;
		RedPlayer		player1;
		IcePlayer		player2;
		RedLake			*Lake1;
		IceLake			*Lake2;
		Greenlake		*Lake3;
		RedDoor			reddoor;
		IceDoor			icedoor;
		Mood			*mood;
		box				box;
		Button			*button;
	};

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲第二關的狀態(Game Run 2)
	/////////////////////////////////////////////////////////////////////////////
	class CGameStateRun2 : public CGameState {
	public:
		CGameStateRun2(CGame *g);
		~CGameStateRun2();
		CGameMap gamemap;
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnInit();  								// 遊戲的初值及圖形設定
		void OnKeyDown(UINT, UINT, UINT);
		void OnKeyUp(UINT, UINT, UINT);
	protected:
		void OnMove();									// 移動遊戲元素
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		bool JUMP, UP;

		const int		NUMRED;		  // 火鑽的總數
		const int		NUMICE;		  // 冰鑽的總數
		const int		LAKERED;	  // 紅水的總數
		const int		LAKEICE;	  // 藍水的總數
		const int		LAKEGREEN;	  // 綠水的總數
		const int		NUMMOD;		  // 拉桿的總數
		const int		NUMBUT;		  // 按鈕的總數
		const int		NUMBUT1;		
		CMovingBitmap	background;	// 背景圖

		RedDiamond		*diamond1;	
		IceDiamond		*diamond2;
		CInteger		hits_left;
		CInteger		hits_lake;
		CInteger		hits_door;
		RedPlayer		player1;
		IcePlayer		player2;
		RedLake			*Lake1;
		IceLake			*Lake2;
		Greenlake		*Lake3;
		RedDoor			reddoor;
		IceDoor			icedoor;
		Mood			*mood;
		Button			*button;
		Button			*button1;
	};
	/////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的結束狀態(Game Over)
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateOver : public CGameState {
	public:
		CGameStateOver(CGame *g);
		void OnLButtonDown(UINT nFlags, CPoint point);
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnInit();
	protected:
		void OnMove();									// 移動遊戲元素
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		int counter;	
		CMovingBitmap gameover;
	};
	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲贏的狀態(Game Win)
	/////////////////////////////////////////////////////////////////////////////
	class CGameStateWin : public CGameState {
	public:
		CGameStateWin(CGame *g);
		void OnLButtonDown(UINT nFlags, CPoint point);
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnInit();
	protected:
		void OnMove();									// 移動遊戲元素
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		int counter;	
		CMovingBitmap gamewinspace;
		CMovingBitmap alarm;
		CMovingBitmap boygirl;
		CMovingBitmap dim;
		CMovingBitmap good;
		CMovingBitmap bad;
		CMovingBitmap next;
		CMovingBitmap gold;
		CMovingBitmap conti;
		CMovingBitmap fin1;
		CMovingBitmap fin2;
		CMovingBitmap fin3;
		CMovingBitmap fin4;
	};

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的選關狀態(Game Menu)
	/////////////////////////////////////////////////////////////////////////////
	class CGameStateMenu : public CGameState {
	public:
		CGameStateMenu(CGame *g);
		void OnLButtonDown(UINT nFlags, CPoint point);
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnInit();
	protected:
		void OnMove();									// 移動遊戲元素
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		int counter;	
		CMovingBitmap bg;
	};
	
}