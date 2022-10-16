#include "RedPlayer.h"
#pragma once
namespace game_framework {
    /////////////////////////////////////////////////////////////////////////////
    // 這個class是藍水的Class
    /////////////////////////////////////////////////////////////////////////////
    class IceLake
    {
    public:
        IceLake();
        bool HitPlayer(RedPlayer *player);                        // 是否碰到玩家
        void LoadBitmap();                                        // 載入圖形
        void OnMove();                                            // 移動
        void OnShow();                                            // 將圖形貼到畫面
        void SetXY(int nx, int ny);    
        bool hack;                                                // 設定密技啟動布林
    protected:
        CMovingBitmap LAKE;            
        int x, y;                    // 座標
    private:
        bool HitRectangle(int tx1, int ty1, int tx2, int ty2);    // 是否碰到參數範圍的矩形
    };
}