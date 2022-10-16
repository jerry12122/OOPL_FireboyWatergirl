#include "RedPlayer.h"
#pragma once
namespace game_framework {
    /////////////////////////////////////////////////////////////////////////////
    // �o��class�O�Ť���Class
    /////////////////////////////////////////////////////////////////////////////
    class IceLake
    {
    public:
        IceLake();
        bool HitPlayer(RedPlayer *player);                        // �O�_�I�쪱�a
        void LoadBitmap();                                        // ���J�ϧ�
        void OnMove();                                            // ����
        void OnShow();                                            // �N�ϧζK��e��
        void SetXY(int nx, int ny);    
        bool hack;                                                // �]�w�K�ޱҰʥ��L
    protected:
        CMovingBitmap LAKE;            
        int x, y;                    // �y��
    private:
        bool HitRectangle(int tx1, int ty1, int tx2, int ty2);    // �O�_�I��Ѽƽd�򪺯x��
    };
}