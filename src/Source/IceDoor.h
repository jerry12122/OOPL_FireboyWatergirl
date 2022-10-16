#include "IcePlayer.h"
#pragma once
namespace game_framework {
    /////////////////////////////////////////////////////////////////////////////
    // �o��class�O�B�q������Class
    /////////////////////////////////////////////////////////////////////////////
    class IceDoor
    {
    public:
        IceDoor();
        bool HitPlayer(IcePlayer *player);                        // �O�_�I�쪱�a
        bool IsAlive();                                            // �O�_����
        void LoadBitmap();                                        // ���J�ϧ�
        void OnMove();                                            // ����
        void OnShow();                                            // �N�ϧζK��e��
        void SetXY(int nx, int ny);                                // �]�w�y��
        void SetIsAlive(bool alive);                            // �]�w�O�_����
    protected:
        CMovingBitmap door, bmp2;        
        int x, y;                    // �y��
        bool is_alive;                // �O�_����
    private:
        bool HitRectangle(int tx1, int ty1, int tx2, int ty2);    // �O�_�I��Ѽƽd�򪺯x��
    };
}
