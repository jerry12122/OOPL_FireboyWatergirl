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


namespace game_framework {
/////////////////////////////////////////////////////////////////////////////
// �o��class���C�����C���}�Y�e������
/////////////////////////////////////////////////////////////////////////////

CGameStateInit::CGameStateInit(CGame *g)
: CGameState(g)
{
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
// �o��class���C�����������A(Game Over)
/////////////////////////////////////////////////////////////////////////////

CGameStateOver::CGameStateOver(CGame *g)
: CGameState(g)
{
}

void CGameStateOver::OnMove()
{
	counter--;
	if (counter < 0)
		GotoGameState(GAME_STATE_INIT);
}

void CGameStateOver::OnBeginState()
{
	counter = 30 * 5; // 5 seconds
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
	Sleep(300);				// ��C�A�H�K�ݲM���i�סA��ڹC���ЧR����Sleep
	//
	// �̲׶i�׬�100%
	//
	ShowInitProgress(100);
}

void CGameStateOver::OnShow()
{
	CDC *pDC = CDDraw::GetBackCDC();			// ���o Back Plain �� CDC 
	CFont f,*fp;
	f.CreatePointFont(160,"Times New Roman");	// ���� font f; 160���16 point���r
	fp=pDC->SelectObject(&f);					// ��� font f
	pDC->SetBkColor(RGB(0,0,0));
	pDC->SetTextColor(RGB(255,255,0));
	char str[80];								// Demo �Ʀr��r�ꪺ�ഫ
	sprintf(str, "Game Over ! (%d)", counter / 30);
	pDC->TextOut(240,210,str);
	pDC->SelectObject(fp);						// �� font f (�d�U���n�|�F��)
	CDDraw::ReleaseBackCDC();					// �� Back Plain �� CDC
	
}

/////////////////////////////////////////////////////////////////////////////
// �o��class���C�����C�����檫��A�D�n���C���{�����b�o��
/////////////////////////////////////////////////////////////////////////////





CGameStateRun::CGameStateRun(CGame *g)
: CGameState(g), NUMRED(3),NUMICE(4), LAKERED(3), LAKEICE(3)
{
	diamond1 = new RedDiamond[NUMRED];
	diamond2 = new IceDiamond[NUMICE];
	Lake1 = new RedLake[LAKERED];
	Lake2 = new IceLake[LAKEICE];
	
	//reddoor = new RedDoor();
}

CGameStateRun::~CGameStateRun()
{
	delete [] diamond1;
	delete[] diamond2;
	delete[] Lake1;
	delete[] Lake2;
}

void CGameStateRun::OnBeginState()
{
	const int BALL_GAP = 90;
	const int BALL_XY_OFFSET = 45;
	const int BALL_PER_ROW = 7;
	const int HITS_LEFT = 0;
	const int HITS_LAKE = 1;
	const int HITS_LEFT_X = 590;
	const int HITS_LEFT_Y = 0;
	const int BACKGROUND_X = 60;
	const int ANIMATION_SPEED = 15;
	const int diamond1_position[3][2] = { {405,535},{140,260},{223,41} };
	for (int i = 0; i < NUMRED; i++) {				// �]�w�y���_�l�y��
		diamond1[i].SetXY(diamond1_position[i][0], diamond1_position[i][1]);
		diamond1[i].SetIsAlive(true);
	}
	const int diamond2_position[4][2] = { {570,535},{470,290},{475,87},{35,109} };
	for (int i = 0; i < NUMICE; i++) {				// �]�w�y���_�l�y��
		diamond2[i].SetXY(diamond2_position[i][0], diamond2_position[i][1]);
		diamond2[i].SetIsAlive(true);
	}
	const int Lake1_position[3][2] = { {330,573},{125,408},{270,122} };
	for (int i = 0; i < LAKERED; i++) {				// �]�w�y���_�l�y��
		Lake1[i].SetXY(Lake1_position[i][0], Lake1_position[i][1]);
		Lake1[i].SetIsAlive(true);
	}
	const int Lake2_position[3][2] = { {530,573},{448,326},{465,122} };
	for (int i = 0; i < LAKEICE; i++) {				// �]�w�y���_�l�y��
		Lake2[i].SetXY(Lake2_position[i][0], Lake2_position[i][1]);
		Lake2[i].SetIsAlive(true);
	}
	player1.Initialize();
	player2.Initialize();

	background.SetTopLeft(0,0);				// �]�w�I�����_�l�y��
	help.SetTopLeft(0, SIZE_Y - help.Height());			// �]�w�����Ϫ��_�l�y��
	hits_left.SetInteger(HITS_LEFT);
	hits_lake.SetInteger(HITS_LAKE);
	hits_left.SetTopLeft(HITS_LEFT_X,HITS_LEFT_Y);		// ���w�ѤU�����ƪ��y��
	CAudio::Instance()->Play(AUDIO_LAKE, true);			// ���� WAVE
	CAudio::Instance()->Play(AUDIO_DING, false);		// ���� WAVE
	CAudio::Instance()->Play(AUDIO_NTUT, true);			// ���� MIDI
}

void CGameStateRun::OnMove()							// ���ʹC������
{
	//
	// �p�G�Ʊ�ק�cursor���˦��A�h�N�U���{����commment�����Y�i
	//
	// SetCursor(AfxGetApp()->LoadCursor(IDC_GAMECURSOR));
	//
	// ���ʭI���Ϫ��y��
	//
	/*
		if (background.Top() > SIZE_Y)
		background.SetTopLeft(60 ,-background.Height());
	background.SetTopLeft(background.Left(),background.Top()+1);
	*/

	//
	// ���ʲy
	//
	int i;
	for (i = 0; i < NUMRED; i++)
		diamond1[i].OnMove();
	for (i = 0; i < NUMICE; i++)
	{
		diamond2[i].OnMove();
	}
	//
	// �������l
	//

	player1.OnMove();
	player2.OnMove();

	//
	// �P�_���l�O�_�I��y
	//

	for (i = 0; i < NUMRED; i++)
		if (diamond1[i].IsAlive() && diamond1[i].HitPlayer(&player1)) {
			diamond1[i].SetIsAlive(false);
			CAudio::Instance()->Play(AUDIO_DING);
			hits_left.Add(1);
		}
	for (i = 0; i < NUMICE; i++)
	{
		if (diamond2[i].IsAlive() && diamond2[i].HitPlayer(&player2)) {
			diamond2[i].SetIsAlive(false);
			CAudio::Instance()->Play(AUDIO_DING);
			hits_left.Add(1);
		}
	}
	for (i = 0; i < LAKERED; i++)
		if (Lake1[i].IsAlive() && Lake1[i].HitPlayer(&player2)) {
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
	for (i = 0; i < LAKEICE; i++)
	{
		if (Lake2[i].IsAlive() && Lake2[i].HitPlayer(&player1)) {
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

	player1.LoadBitmap();
	player2.LoadBitmap();
	reddoor.LoadBitmap();
	background.LoadBitmap(IDB_MAP1);					// ���J�I�����ϧ�
	//
	// ��������Loading�ʧ@�A�����i��
	//
	ShowInitProgress(50);
	Sleep(300); // ��C�A�H�K�ݲM���i�סA��ڹC���ЧR����Sleep
	//
	// �~����J��L���
	//
	help.LoadBitmap(IDB_HELP,RGB(255,255,255));				// ���J�������ϧ�
	hits_left.LoadBitmap();
	CAudio::Instance()->Load(AUDIO_DING,  ".\\sounds\\ding.wav");	// ���J�s��0���n��ding.wav
	CAudio::Instance()->Load(AUDIO_LAKE,  ".\\sounds\\lake.mp3");	// ���J�s��1���n��lake.mp3
	CAudio::Instance()->Load(AUDIO_NTUT,  ".\\sounds\\ntut.mid");	// ���J�s��2���n��ntut.mid
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
	//  �`�N�GShow�̭��d�U���n���ʥ��󪫥󪺮y�СA���ʮy�Ъ��u�@����Move���~��A
	//        �_�h��������sø�Ϯ�(OnDraw)�A����N�|���ʡA�ݰ_�ӷ|�ܩǡC���ӳN�y
	//        ���AMove�t�dMVC����Model�AShow�t�dView�A��View�������Model�C
	//
	//
	//  �K�W�I���ϡB�����ơB�y�B���l�B�u�����y
	//
	background.ShowBitmap();			// �K�W�I����
	help.ShowBitmap();					// �K�W������
	hits_left.ShowBitmap();
	for (int i=0; i < NUMRED; i++)
		diamond1[i].OnShow();				// �K�W��i���y
	for (int i = 0; i < NUMICE; i++)
	{
		diamond2[i].OnShow();
	}
	player1.OnShow();
	player2.OnShow();
	for (int i = 0; i < LAKERED; i++)
		Lake1[i].OnShow();				// �K�W��i���y
	for (int i = 0; i < LAKEICE; i++)
	{
		Lake2[i].OnShow();
	}
	//reddoor.OnShow();
	//
	//  �K�W���W�Υk�U��������
	//


}
}