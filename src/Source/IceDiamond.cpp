#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "IcePlayer.h"
#include "IceDiamond.h"

namespace game_framework {
    IceDiamond::IceDiamond()
    {
        is_alive = true;
        x = y = 0;
    }

    bool IceDiamond::HitPlayer(IcePlayer *player)
    {
        return HitRectangle(player->GetX1(), player->GetY1(),
            player->GetX2(), player->GetY2());
    }

    bool IceDiamond::HitRectangle(int tx1, int ty1, int tx2, int ty2)
    {
        int x1 = x;                // ���a�����W��x�y��
        int y1 = y;                // ���a�����W��y�y��
        int x2 = x1 + bmp.Width();    // ���a���k�U��x�y��
        int y2 = y1 + bmp.Height();    // ���a���k�U��y�y��
        return (tx2 >= x1 && tx1 <= x2 && ty2 >= y1 && ty1 <= y2);
    }

    bool IceDiamond::IsAlive()
    {
        return is_alive;
    }

    void IceDiamond::LoadBitmap()
    {
        bmp.LoadBitmap(ICE_DIAMOND, RGB(255, 255, 255));            // ���J�ϧ�
    }
    void IceDiamond::OnMove()
    {
        if (!is_alive)
            return;
    }
    
    void IceDiamond::SetIsAlive(bool alive)
    {
        is_alive = alive;
    }

    void IceDiamond::SetXY(int nx, int ny)
    {
        x = nx; y = ny;
    }

    void IceDiamond::OnShow()
    {
        if (is_alive) {
            bmp.SetTopLeft(x, y);
            bmp.ShowBitmap();
        }
    }
}