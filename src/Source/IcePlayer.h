#pragma once
#include "RedPlayer.h"
namespace game_framework {
    /////////////////////////////////////////////////////////////////////////////
    // �o��class�O�B�H��Class
    /////////////////////////////////////////////////////////////////////////////

    class IcePlayer
    {
    public:
        void SetMovingDown(bool flag);    // �]�w�O�_���b���U����
        void SetMovingLeft(bool flag);    // �]�w�O�_���b��������
        void SetMovingRight(bool flag); // �]�w�O�_���b���k����
        void SetMovingUp(bool flag);    // �]�w�O�_���b���W����
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
        void Initialize(int stages);                // �]�w���a����l��
        void LoadBitmap();                // ���J�ϧ�
        void OnMove();                    // ���ʪ��a
        void OnMove1();
        void OnShow();                    // �N���a�ϧζK��e��
        void SetXY(int nx, int ny);        // �]�w���a���W���y��
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
        CAnimation animation, animation1;        // ���a���ʵe
        CMovingBitmap bit;
        CGameMap gamemap;
        int x, y;                    // ���a���W���y��
        bool setFloorEnable;
        int floor;
        int velocity;                // �ثe���t��(�I/��)
        int initial_velocity;        // ��l�t��
        bool rising;                // true���W�ɡBfalse���U��        
        bool isMovingDown;            // �O�_���b���U����
        bool isMovingLeft;            // �O�_���b��������
        bool isMovingRight;            // �O�_���b���k����
        bool isMovingUp;            // �O�_���b���W����
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