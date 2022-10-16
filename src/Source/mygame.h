/*
 * mygame.h: ���ɮ��x�C��������class��interface
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

	enum AUDIO_ID {				// �w�q�U�ح��Ī��s��
		AUDIO_DING,				// 0
		AUDIO_LAKE,				// 1
		AUDIO_NTUT				// 2
	};

	/////////////////////////////////////////////////////////////////////////////
	// �o��class���C�����C���}�Y�e������
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateInit : public CGameState {
	public:
		CGameStateInit(CGame *g);
		void OnInit();  								// �C������Ȥιϧγ]�w
		void OnBeginState();							// �]�w�C�������һݪ��ܼ�
		void OnKeyUp(UINT, UINT, UINT); 				// �B�z��LUp���ʧ@
		void OnLButtonDown(UINT nFlags, CPoint point);  // �B�z�ƹ����ʧ@
	protected:
		void OnShow();									// ��ܳo�Ӫ��A���C���e��
	private:
		CMovingBitmap logo,intro,intro2;				
		bool intro_bool;
	};

	/////////////////////////////////////////////////////////////////////////////
	// �o��class���C���Ĥ@�������A(Game Run 1)
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateRun : public CGameState {
	public:
		CGameStateRun(CGame *g);
		~CGameStateRun();
		CGameMap gamemap;
		void OnBeginState();							// �]�w�C�������һݪ��ܼ�
		void OnInit();  								// �C������Ȥιϧγ]�w
		void OnKeyDown(UINT, UINT, UINT);
		void OnKeyUp(UINT, UINT, UINT);
	protected:
		void OnMove();									// ���ʹC������
		void OnShow();									// ��ܳo�Ӫ��A���C���e��
	private:
		bool JUMP, UP;
		
		const int		NUMRED;		// ���p���`��
		const int		NUMICE;		// �B�p���`��
		const int		LAKERED;	// �������`��
		const int		LAKEICE;	// �Ť����`��
		const int		LAKEGREEN;	// ������`��
		const int		NUMMOD;		// �Ա쪺�`��
		const int		NUMBUT;		// ���s���`��
		CMovingBitmap	background;	// �I����

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
	// �o��class���C���ĤG�������A(Game Run 2)
	/////////////////////////////////////////////////////////////////////////////
	class CGameStateRun2 : public CGameState {
	public:
		CGameStateRun2(CGame *g);
		~CGameStateRun2();
		CGameMap gamemap;
		void OnBeginState();							// �]�w�C�������һݪ��ܼ�
		void OnInit();  								// �C������Ȥιϧγ]�w
		void OnKeyDown(UINT, UINT, UINT);
		void OnKeyUp(UINT, UINT, UINT);
	protected:
		void OnMove();									// ���ʹC������
		void OnShow();									// ��ܳo�Ӫ��A���C���e��
	private:
		bool JUMP, UP;

		const int		NUMRED;		  // ���p���`��
		const int		NUMICE;		  // �B�p���`��
		const int		LAKERED;	  // �������`��
		const int		LAKEICE;	  // �Ť����`��
		const int		LAKEGREEN;	  // ������`��
		const int		NUMMOD;		  // �Ա쪺�`��
		const int		NUMBUT;		  // ���s���`��
		const int		NUMBUT1;		
		CMovingBitmap	background;	// �I����

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
	// �o��class���C�����������A(Game Over)
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateOver : public CGameState {
	public:
		CGameStateOver(CGame *g);
		void OnLButtonDown(UINT nFlags, CPoint point);
		void OnBeginState();							// �]�w�C�������һݪ��ܼ�
		void OnInit();
	protected:
		void OnMove();									// ���ʹC������
		void OnShow();									// ��ܳo�Ӫ��A���C���e��
	private:
		int counter;	
		CMovingBitmap gameover;
	};
	/////////////////////////////////////////////////////////////////////////////
	// �o��class���C��Ĺ�����A(Game Win)
	/////////////////////////////////////////////////////////////////////////////
	class CGameStateWin : public CGameState {
	public:
		CGameStateWin(CGame *g);
		void OnLButtonDown(UINT nFlags, CPoint point);
		void OnBeginState();							// �]�w�C�������һݪ��ܼ�
		void OnInit();
	protected:
		void OnMove();									// ���ʹC������
		void OnShow();									// ��ܳo�Ӫ��A���C���e��
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
	// �o��class���C�����������A(Game Menu)
	/////////////////////////////////////////////////////////////////////////////
	class CGameStateMenu : public CGameState {
	public:
		CGameStateMenu(CGame *g);
		void OnLButtonDown(UINT nFlags, CPoint point);
		void OnBeginState();							// �]�w�C�������һݪ��ܼ�
		void OnInit();
	protected:
		void OnMove();									// ���ʹC������
		void OnShow();									// ��ܳo�Ӫ��A���C���e��
	private:
		int counter;	
		CMovingBitmap bg;
	};
	
}