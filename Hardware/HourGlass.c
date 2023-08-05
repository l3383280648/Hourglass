#include "stm32f10x.h"    
#include "MPU6050.h"
#include <stdlib.h>
#include <stdbool.h>
#include "Max7219.h"
#include <time.h>
#include "Delay.h"
#include <stdio.h>
extern uint8_t flag_status;
enum gravity{
	down = 0,
	down_left,
	down_right,
	above,
	above_left,
	above_right,
	left,
	right
};
struct sand{
	uint8_t coordinate_x;
	uint8_t coordinate_y;
};

struct hourglass{
	uint16_t Matrix_1[16];
	uint8_t SANDNUM;
	struct sand *sands;
	enum gravity gravity_direction;
};

void hourglass_Init(struct hourglass *hg, int num_sands) {
			hg->SANDNUM = num_sands;
			hg->sands = (struct sand*)malloc(num_sands * sizeof(struct sand));
			for(uint8_t i = 1; i <= 16; i++){
					hg->Matrix_1[i] = 0x0000;
			}
			uint8_t x = 1,y = 1;
			for(uint8_t i = 1; i <= num_sands; i++){
				
				hg->sands[i].coordinate_x = x;
				hg->sands[i].coordinate_y = y;
				Max7219_OpenXY(x,y,hg->Matrix_1);
				y ++;
				if(y == 17){
					x ++ ;
					y = 1;
				}
			}
			hg->gravity_direction = down;
}

void hourglass_set_gravity(struct hourglass *hg){
			uint8_t temp = Get_Gravity();
			switch(temp){
				case 0:hg->gravity_direction = down; 				break;
				case 1:hg->gravity_direction = down_left; 	break;
				case 2:hg->gravity_direction = down_right; 	break;
				case 3:hg->gravity_direction = above; 			break;
				case 4:hg->gravity_direction = above_left; 	break;
				case 5:hg->gravity_direction = above_right; break;
				case 6:hg->gravity_direction = left; 				break;
				case 7:hg->gravity_direction = right; 			break;
			}
}



bool if_left_null(struct hourglass *hg,struct sand *s){
	uint8_t x = s->coordinate_x;
	uint8_t y = s->coordinate_y;
	uint16_t *Matrix;
	Matrix = hg->Matrix_1;
	 switch (hg->gravity_direction) {
			case down:
					if(x == 1 || y == 1)
						return false;
					if(Max7219_CheckXY(x - 1,y - 1,Matrix) == 0)
							return true;
					else   return false;
					break;
					
			case down_left:
					if(y == 1)
						return false;
					if(Max7219_CheckXY(x,y - 1,Matrix) == 0)
							return true;
					else   return false;
					break;
					
			case down_right:
					if(x == 1)
								return false;
					if(Max7219_CheckXY(x - 1, y,Matrix) == 0)
								return true;
						else   return false;
					break;
					
			case right:
				if(x == 1 || y == 16)
					return false;
				if(Max7219_CheckXY(x - 1, y + 1,Matrix) == 0)
							return true;
					else   return false;
				break;
					
			case left:
					if(x == 16 || y == 1)
						return false;
					if(Max7219_CheckXY(x + 1,y - 1,Matrix) == 0)
							return true;
					else   return false;
					break;
					
			case above:
					if(y == 16 || x == 16)
						return false;
					if(Max7219_CheckXY(x + 1,y + 1,Matrix) == 0)
							return true;
					else   return false;
					break;
					
			case above_left:
					if(y == 16)
						return false;
				if(Max7219_CheckXY(x, y + 1,Matrix) == 0)
							return true;
					else   return false;
				break;
					
			case above_right:
				if(x == 16)
					return false;
				if(Max7219_CheckXY(x + 1, y,Matrix) == 0)
							return true;
					else   return false;
				break;
	}
}
bool if_right_null(struct hourglass *hg,struct sand *s){
	uint8_t x = s->coordinate_x;
	uint8_t y = s->coordinate_y;
	uint16_t *Matrix;
	Matrix = hg->Matrix_1;
	 switch (hg->gravity_direction) {
			case down:
					if(x == 1 || y == 16)
						return false;
					if(Max7219_CheckXY(x - 1,y + 1,Matrix) == 0)
							return true;
					else   return false;
					break;
					
			case down_left:
					if(x == 1)
						return false;
					if(Max7219_CheckXY(x - 1,y, Matrix) == 0)
							return true;
					else   return false;
					break;
					
			case down_right:
				if(y == 16)
						return false;
				if(Max7219_CheckXY(x, y + 1, Matrix) == 0)
							return true;
					else   return false;
				break;
					
			case right:
				if(x == 16 || y == 16)
					return false;
				if(Max7219_CheckXY(x + 1, y + 1,Matrix) == 0)
							return true;
					else   return false;
				break;
					
			case left:
					if(x == 1 || y == 1)
						return false;
					if(Max7219_CheckXY(x - 1,y - 1,Matrix) == 0)
							return true;
					else   return false;
					break;
					
			case above:
					if(y == 1 || x == 16)
						return false;
					if(Max7219_CheckXY(x + 1,y - 1,Matrix) == 0)
							return true;
					else   return false;
					break;
					
			case above_left:
					if(x == 16)
						return false;
					if(Max7219_CheckXY(x + 1, y,Matrix) == 0)
							return true;
					else   return false;
					break;
					
			case above_right:
					if(y == 1)
							return false;
					if(Max7219_CheckXY(x, y - 1,Matrix) == 0)
							return true;
					else   return false;
					break;
	}
}

bool if_down_null(struct hourglass *hg,struct sand *s){
	uint8_t x = s->coordinate_x;
	uint8_t y = s->coordinate_y;
	uint16_t *Matrix;
	Matrix = hg->Matrix_1;
	 switch (hg->gravity_direction) {
			case down:
					if(x == 1)
						return false;
					if(Max7219_CheckXY(x - 1,y,Matrix) == 0)
							return true;
					else   return false;
					break;
					
			case down_left:
					if(x == 1 || y == 1)
						return false;
					if(Max7219_CheckXY(x - 1,y - 1, Matrix) == 0)
							return true;
					else   return false;
					break;
					
			case down_right:
					if(y == 16 || x == 1)
							return false;
					if(Max7219_CheckXY(x - 1, y + 1, Matrix) == 0)
							return true;
					else   return false;
					break;
					
			case right:
					if(y == 16)
						return false;
					if(Max7219_CheckXY(x, y + 1,Matrix) == 0)
								return true;
					else   return false;
					break;
					
			case left:

					if(y == 1)
						return false;
					if(Max7219_CheckXY(x,y - 1,Matrix) == 0)
						return true;
					else   return false;
					break;
					
			case above:
					if(x == 16)
						return false;
					if(Max7219_CheckXY(x + 1,y,Matrix) == 0)
							return true;
					else   return false;
					break;
					
			case above_left:
				if(x == 16 || y == 16)
						return false;
				if(Max7219_CheckXY(x + 1, y + 1,Matrix) == 0)
							return true;
					else   return false;
				break;
					
			case above_right:
				if(y == 1 || x == 16)
					 return false;
				if(Max7219_CheckXY(x + 1, y - 1,Matrix) == 0)
							return true;
				else   return false;
				break;
	}
}

void move_down(struct hourglass *hg,struct sand *s){
			 uint8_t x = s->coordinate_x;
			 uint8_t y = s->coordinate_y;
			 uint16_t *Matrix;
			 Matrix = hg->Matrix_1;
			switch (hg->gravity_direction) {
				case down:
								Max7219_CloseXY(x,y,Matrix);
								Max7219_OpenXY(x - 1,y,Matrix);
								s->coordinate_x --;
								break;
				case down_left:
								Max7219_CloseXY(x,y,Matrix);
								Max7219_OpenXY(x - 1,y - 1,Matrix);
								s->coordinate_x --;
								s->coordinate_y --;
								break;
				case down_right:
								Max7219_CloseXY(x,y,Matrix);
								Max7219_OpenXY(x - 1,y + 1,Matrix);
								s->coordinate_x --;
								s->coordinate_y ++;
								break;
				case right:
								Max7219_CloseXY(x,y,Matrix);
								Max7219_OpenXY(x,y + 1,Matrix);
								s->coordinate_y ++;
								break;
				case left:
								Max7219_CloseXY(x,y,Matrix);
								Max7219_OpenXY(x,y - 1,Matrix);
								s->coordinate_y --;
								break;
				case above:
								Max7219_CloseXY(x,y,Matrix);
								Max7219_OpenXY(x + 1,y,Matrix);
								s->coordinate_x ++;
								break;
				case above_left:
								Max7219_CloseXY(x,y,Matrix);
								Max7219_OpenXY(x + 1,y + 1,Matrix);
								s->coordinate_x ++;
								s->coordinate_y ++;
								break;
				case above_right:
								Max7219_CloseXY(x,y,Matrix);
								Max7219_OpenXY(x + 1,y - 1,Matrix);
								s->coordinate_x ++;
								s->coordinate_y --;
								break;
		}
}

void move_left(struct hourglass *hg,struct sand *s){
		uint8_t x = s->coordinate_x;
		uint8_t y = s->coordinate_y;
		uint16_t *Matrix;
		Matrix = hg->Matrix_1;
			switch (hg->gravity_direction) {
				case down:
								Max7219_CloseXY(x,y,Matrix);
								Max7219_OpenXY(x - 1,y - 1,Matrix);
								s->coordinate_x --;
								s->coordinate_y --;
								break;
				case down_left:
								Max7219_CloseXY(x,y,Matrix);
								Max7219_OpenXY(x,y - 1,Matrix);
								s->coordinate_y --;
								break;
				case down_right:
								Max7219_CloseXY(x,y,Matrix);
								Max7219_OpenXY(x - 1,y,Matrix);
								s->coordinate_x --;
								break;
				case right:
								Max7219_CloseXY(x,y,Matrix);
								Max7219_OpenXY(x - 1,y + 1,Matrix);
								s->coordinate_y ++;
								s->coordinate_x --;
								break;
				case left:
								Max7219_CloseXY(x,y,Matrix);
								Max7219_OpenXY(x + 1,y - 1,Matrix);
								s->coordinate_y --;
								s->coordinate_x ++;
								break;
				case above:
								Max7219_CloseXY(x,y,Matrix);
								Max7219_OpenXY(x + 1,y + 1 ,Matrix);
								s->coordinate_x ++;
								s->coordinate_y ++;
								break;
				case above_left:
								Max7219_CloseXY(x,y,Matrix);
								Max7219_OpenXY(x,y + 1,Matrix);
								s->coordinate_y ++;
				break;
				case above_right:
								Max7219_CloseXY(x,y,Matrix);
								Max7219_OpenXY(x + 1,y,Matrix);
								s->coordinate_x ++;
				break;
		}
}

void move_right(struct hourglass *hg,struct sand *s){
		uint8_t x = s->coordinate_x;
		uint8_t y = s->coordinate_y;
		uint16_t *Matrix;
		Matrix = hg->Matrix_1;
			switch (hg->gravity_direction) {
				case down:
								Max7219_CloseXY(x,y,Matrix);
								Max7219_OpenXY(x - 1,y + 1,Matrix);
								s->coordinate_x --;
								s->coordinate_y ++;
								break;
				case down_left:
								Max7219_CloseXY(x,y,Matrix);
								Max7219_OpenXY(x - 1,y,Matrix);
								s->coordinate_x --;
								break;
				case down_right:
								Max7219_CloseXY(x,y,Matrix);
								Max7219_OpenXY(x ,y + 1,Matrix);
								s->coordinate_y ++;
								break;
				case right:
								Max7219_CloseXY(x,y,Matrix);
								Max7219_OpenXY(x + 1,y + 1,Matrix);
								s->coordinate_y ++;
								s->coordinate_x ++;
								break;
				case left:
								Max7219_CloseXY(x,y,Matrix);
								Max7219_OpenXY(x - 1,y - 1,Matrix);
								s->coordinate_y --;
								s->coordinate_x --;
								break;
				case above:
								Max7219_CloseXY(x,y,Matrix);
								Max7219_OpenXY(x + 1,y - 1 ,Matrix);
								s->coordinate_x ++;
								s->coordinate_y --;
								break;
				case above_left:
								Max7219_CloseXY(x,y,Matrix);
								Max7219_OpenXY(x + 1,y,Matrix);
								s->coordinate_x ++;
				break;
				case above_right:
								Max7219_CloseXY(x,y,Matrix);
								Max7219_OpenXY(x,y - 1,Matrix);
								s->coordinate_y --;
				break;
				
		}
}

void sand_next(struct hourglass *hg,struct sand *s){
	bool down_ifNull = if_down_null(hg,s);
	if(down_ifNull == true){
			move_down(hg,s);
	}
	else{
		bool left_ifNull = if_left_null(hg,s);
		bool right_ifNull = if_right_null(hg,s);
				if(left_ifNull == true && right_ifNull == true){
						uint8_t index = rand() %2;
						if(index == 0)
								move_left(hg,s);
						else
								move_right(hg,s);
				}
				else if(left_ifNull == true && right_ifNull == false)
						move_left(hg,s);   
			
				else if(left_ifNull == false && right_ifNull == true)
						move_right(hg,s);
		}
}

