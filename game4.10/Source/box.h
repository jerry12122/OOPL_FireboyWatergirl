#include "IcePlayer.h"
#include "RedPlayer.h"
#include <fstream> 
extern bool current_rank;
namespace game_framework {

	class box
	{
	public:
		box();
		void init();
		int x, y;					
		bool HitEraser(RedPlayer *redplayer);						
		bool HitEraser(IcePlayer *iceplayer);							
		void LoadBitmap();										
		void OnMove();											
		void SetMovingLeft(bool flag);	
		void OnShow();											
		void SetXY(int nx, int ny);								
		void SetIsAlive(bool alive);							
		bool isLeftRightEmpty(int x, int y, int value);
		void setfloor();
		bool OnBox(int tx1, int ty1, int tx2, int ty2);
		int GetX1();
		int GetY1();
	protected:
		CMovingBitmap bmp;			
		CGameMap gamemap;
		bool isMovingDown;			
		bool isMovingLeft;			
		bool isMovingRight;			
		bool isMovingUp;			
		int dx, dy;					
		int floor;
		int index;					
		int delay_counter;			
		int delay;					
		int map[60][80];
		int x_edge[800];
		int y_edge[600];
		bool is_alive;				
	private:
		bool HitRectangle(int tx1, int ty1, int tx2, int ty2);	
		bool inertia;
		int initial_velocity;	
		int velocity;			
	};
}