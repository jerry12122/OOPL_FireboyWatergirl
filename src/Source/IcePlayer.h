#pragma once
#include "RedPlayer.h"
namespace game_framework {
    /////////////////////////////////////////////////////////////////////////////
    // 這個class是冰人的Class
    /////////////////////////////////////////////////////////////////////////////

    class IcePlayer
    {
    public:
        void SetMovingDown(bool flag);    // 設定是否正在往下移動
        void SetMovingLeft(bool flag);    // 設定是否正在往左移動
        void SetMovingRight(bool flag); // 設定是否正在往右移動
        void SetMovingUp(bool flag);    // 設定是否正在往上移動
        void SetButton(bool flag);
        void SetButton2(bool flag);
        void SetButton3(bool flag);
        void SetMood(bool flag);
        void MoodY(int MY);
        IcePlayer();
        int GetX1();
        int GetY1();
        int GetX2();
        int GetY2();
        void Initialize(int stages);                // 設定玩家為初始值
        void LoadBitmap();                // 載入圖形
        void OnMove();                    // 移動玩家
        void OnMove1();
        void OnShow();                    // 將玩家圖形貼到畫面
        void SetXY(int nx, int ny);        // 設定玩家左上角座標
        void SetFloor(int y);
        void SetVelocity(int);
        bool isLeftRightEmpty(int x, int y, int value);
        int getCoordX(int x, int y);
        int getCoordY(int x, int y);
        void setfloor();
        bool isOnButton;
        bool frontBox(int x, int y);
        bool onBox(int x, int y);
        void setFront(bool a);
        void setOnBox(bool a);
        bool butin();
        int map[60][80];
        int x_edge[800];
        int y_edge[600];
    protected:
        CAnimation animation, animation1;        // 玩家的動畫
        CMovingBitmap bit;
        CGameMap gamemap;
        int x, y;                    // 玩家左上角座標
        bool setFloorEnable;
        int floor;
        int velocity;                // 目前的速度(點/次)
        int initial_velocity;        // 初始速度
        bool rising;                // true表上升、false表下降        
        bool isMovingDown;            // 是否正在往下移動
        bool isMovingLeft;            // 是否正在往左移動
        bool isMovingRight;            // 是否正在往右移動
        bool isMovingUp;            // 是否正在往上移動
        bool isFrontBox;
        bool isOnBox;
        bool isButton;
        bool isButton2;
        bool isButton3;
        bool isMood;
        bool isBox;
        int stage;
    };
}