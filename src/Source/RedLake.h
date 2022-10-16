#include "IcePlayer.h"
#pragma once
namespace game_framework {
    /////////////////////////////////////////////////////////////////////////////
    // �o��class�O������Class
    /////////////////////////////////////////////////////////////////////////////
    class RedLake
    {
    public:
        RedLake();
        bool HitPlayer(IcePlayer *player);                        // �O�_�I�쪱�a
        void LoadBitmap();                                        // ���J�ϧ�
        void OnMove();                                            // ����
        void OnShow();                                            // �N�ϧζK��e��
        void SetXY(int nx, int ny);        
        bool hack;// �]�w��ߪ��y��
    protected:
        CMovingBitmap LAKE;            
        int x, y;                    // �y��
    private:
        bool HitRectangle(int tx1, int ty1, int tx2, int ty2);    // �O�_�I��Ѽƽd�򪺯x��
    };
}