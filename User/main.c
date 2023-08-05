#include "stm32f10x.h"   // Device header
#include "Delay.h"
#include "MPU6050.h"
#include "MPU6050Reg.h"
#include "Max7219.h"
#include "HourGlass.h"
#include <stdbool.h>

struct hourglass hg;
uint8_t flag_status = 1;
int main(){
		Max7219_Init(); 
		MPU6050_Init();
	
		uint8_t num_sands = 128; 
		hourglass_Init(&hg, num_sands);
		Max7219_1_ScanMatrix(hg.Matrix_1);
		while(1){
			hourglass_set_gravity(&hg); 
			for(uint8_t i = 1; i <= num_sands; i ++){
				sand_next(&hg,&hg.sands[i]);
			}
			Max7219_1_ScanMatrix(hg.Matrix_1);
			Delay_ms(50);
		}	
}


