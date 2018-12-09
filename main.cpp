#include "mbed.h"
// assign pin for swith
DigitalOut gpo(D0);
DigitalOut gpo1(D1);
DigitalOut gpo2(D2);
// assign pin for button
DigitalIn gpo3(D3);
DigitalIn gpo4(D4);
// assign pin for uart serial communication
Serial pc(USBTX, USBRX);
// assign timer
Timer t;
Timer t1;
// initial outpt state and timer
void init(){
		gpo = 1;
		gpo1 = 0;
		gpo2 = 0;
		t.start();
	  t1.start();
}
int main()
{
	init();
	pc.printf("welcome to the react time game!\r\n");// serial print the progress
	//setting button press flag
	bool sw1_flag = false;
	bool sw2_flag = false;
	while(true){
		/*if (gpo3 && !sw1_flag && !sw2_flag){
			wait(0.01);
			if(gpo3){
				sw1_flag = true;
				sw2_flag = false;
			}
		}
		if (gpo4 && !sw1_flag && !sw2_flag){
			wait(0.01f);
			if(gpo4){
				sw1_flag = false;
				sw2_flag = true;
			}
		}
		if(sw1_flag){
			sw1_flag = false;
			gpo2 = 1;
			gpo = 0;
			wait(3.0f);
			pc.printf("restart the game!");
		}
		if(sw2_flag){
			sw2_flag = false;
			gpo1 = 1;
			gpo = 0;
			wait(3.0f);
			pc.printf("restart the game!\n");
		}*/
		
		
		
		while(!sw1_flag || !sw2_flag){
		if (gpo3 && !sw1_flag){
			wait(0.01);//debounce check in a short time
			if(gpo3 && !sw1_flag){
				t.stop();
				pc.printf("Player 1's reaction time is %f seconds\r\n", t.read());
				gpo = 0;
				sw1_flag = true;
			}
		}
		if (gpo4 && !sw2_flag){
			wait(0.01f);//debounce check in a short time
			if(gpo4 && !sw2_flag){
				t1.stop();
				pc.printf("Player 2's reaction time is %f seconds\r\n", t1.read());
				gpo = 0;
				sw2_flag = true;
			}
			
		}
	}
		// show the winner information and light up the winner's LED
		if (t1.read() >t.read()){
			gpo1 = 1;
			pc.printf("player 1 wins!\r\n");
		}
		if (t1.read() < t.read()){
			gpo2 = 1;
			pc.printf("player 2 wins!\r\n");
		}
		// reset the button flag and timer
		sw1_flag = false;
		sw2_flag = false;
		t.reset();
		t1.reset();
		wait(3.0f);
		init();
		pc.printf("restart the game!\r\n");
		

	
	}
	
}
