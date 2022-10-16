#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "RedPlayer.h"
#include "RedDiamond.h"

namespace game_framework {
    /////////////////////////////////////////////////////////////////////////////
    // RedDiamond class
    /////////////////////////////////////////////////////////////////////////////
    RedDiamond::RedDiamond()
    {
        is_alive = true;
        x = y = 0;
    }

    bool RedDiamond::HitPlayer(RedPlayer *player)
    {
        return HitRectangle(player->GetX1(), player->GetY1(),
            player->GetX2(), player->GetY2());
    }

    bool RedDiamond::HitRectangle(int tx1, int ty1, int tx2, int ty2)
    {
        int x1 = x ;                // �y�����W��x�y��
        int y1 = y ;                // �y�����W��y�y��
        int x2 = x1 + bmp.Width();    // �y���k�U��x�y��
        int y2 = y1 + bmp.Height();    // �y���k�U��y�y��
        return (tx2 >= x1 && tx1 <= x2 && ty2 >= y1 && ty1 <= y2);
    }

    bool RedDiamond::IsAlive()
    {
        return is_alive;
    }

    void RedDiamond::LoadBitmap()
    {
        bmp.LoadBitmap(FIRE_DIAMOND, RGB(255, 255, 255));        
    }
    void RedDiamond::OnMove()
    {
    }

    void RedDiamond::SetIsAlive(bool alive)
    {
        is_alive = alive;
    }

    void RedDiamond::SetXY(int nx, int ny)
    {
        x = nx; y = ny;
    }

    void RedDiamond::OnShow()
    {
        if (is_alive) {
            bmp.SetTopLeft(x , y );
            bmp.ShowBitmap();
        }
    }
}