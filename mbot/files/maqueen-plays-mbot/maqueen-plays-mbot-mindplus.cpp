/*!
 * MindPlus
 * maqueen
 *
 */
#include <Maqueen_Motor.h>
#include <DFRobot_URM10.h>
#include <Microbit_Sound.h>
#include <DFRobot_NeoPixel.h>
#include <DFRobot_IRremote.h>

// Dynamic variables
volatile float mind_n_mode, mind_n_motor_state, mind_n_prev_motor_state, mind_n_tracking_flag,
               mind_n_speed, mind_n_gear_factor, mind_n_min_speed, mind_n_distance,
               mind_n_tracking_left, mind_n_tracking_right;
// Function declaration
void DF_stop();
void DF_mode_A();
void DF_mode_B();
void DF_mode_C();
void onIRReceive(uint8_t data);
void DF_forward();
void DF_backward();
void DF_turn_left();
void DF_backward_and_turn_left();
void DF_turn_right();
void DF_backward_and_turn_right();
void DF_change_gear(String gear);
// Create an object
DFRobot_NeoPixel neoPixel_15;
Maqueen_Motor    motor;
DFRobot_URM10    urm10;
IRremote_Receive remoteReceive_16;


// Main program start
void setup() {
	dfrobotRandomSeed();
	neoPixel_15.begin(15, 4, 255);
	remoteReceive_16.begin(16);
	remoteReceive_16.setCallback(onIRReceive);
	DF_stop();
	// 0=A
	// 1=B
	// 2=C
	mind_n_mode = 0;
	// 0=STOP
	// 1=FORWARD
	// 2=BACKWARD
	// 4=LEFT
	// 8=RIGHT
	mind_n_motor_state = 0;
	mind_n_prev_motor_state = 0;
	mind_n_tracking_flag = 0;
	mind_n_speed = 200;
	mind_n_gear_factor = 23;
	mind_n_min_speed = 48;
	neoPixel_15.setRangeColor(-1, -1, 0xFF0000);
	MSound.playTone(0, 294, BEAT_1);
	delay(300);
	neoPixel_15.setRangeColor(-1, -1, 0x00FF00);
	MSound.playTone(0, 330, BEAT_1);
	delay(300);
	neoPixel_15.setRangeColor(-1, -1, 0x0000FF);
	MSound.playTone(0, 349, BEAT_1);
	delay(300);
	neoPixel_15.setRangeColor(-1, -1, 0xFFFFFF);
}
void loop() {
	if ((Button_A.isPressed() && !Button_B.isPressed())) {
		while (!(!(Button_A.isPressed() && !Button_B.isPressed()))) {yield();}
		mind_n_mode = (((int)(mind_n_mode+1)) % ((int)3));
		if ((mind_n_mode==0)) {
			mind_n_speed = 220;
			DF_stop();
			MSound.playTone(0, 294, BEAT_1);
			neoPixel_15.setRangeColor(-1, -1, 0xFFFFFF);
		}
		if ((mind_n_mode==1)) {
			mind_n_speed = 200;
			DF_stop();
			MSound.playTone(0, 330, BEAT_1);
			neoPixel_15.setRangeColor(-1, -1, 0x00FF00);
		}
		if ((mind_n_mode==2)) {
			mind_n_speed = 120;
			DF_stop();
			MSound.playTone(0, 349, BEAT_1);
			neoPixel_15.setRangeColor(-1, -1, 0x0000FF);
		}
	}
	if ((mind_n_mode==0)) {
		DF_mode_A();
	}
	if ((mind_n_mode==1)) {
		DF_mode_B();
	}
	if ((mind_n_mode==2)) {
		DF_mode_C();
	}
}


// Custom function
void DF_stop() {
	neoPixel_15.setRangeColor(-1, -1, 0x000000);
	motor.motorStop(motor.LEFT);
	motor.motorStop(motor.RIGHT);
}
void DF_mode_A() {
	if ((mind_n_motor_state==1)) {
		DF_forward();
		mind_n_prev_motor_state = mind_n_motor_state;
	}
	if ((mind_n_motor_state==2)) {
		DF_backward();
		mind_n_prev_motor_state = mind_n_motor_state;
	}
	if ((mind_n_motor_state==4)) {
		DF_turn_left();
		mind_n_prev_motor_state = mind_n_motor_state;
	}
	if ((mind_n_motor_state==8)) {
		DF_turn_right();
		mind_n_prev_motor_state = mind_n_motor_state;
	}
	if ((mind_n_motor_state==0)) {
		if ((!(mind_n_prev_motor_state==mind_n_motor_state))) {
			DF_stop();
			mind_n_prev_motor_state = mind_n_motor_state;
		}
	}
}
void DF_mode_B() {
	mind_n_distance = (urm10.getDistanceCM(1, 2));
	if (((mind_n_distance>40) || (mind_n_distance==0))) {
		DF_forward();
	}
	else {
		if ((mind_n_distance>15)) {
			if (((random(1, 2+1))==1)) {
				DF_turn_left();
			}
			else {
				DF_turn_right();
			}
			delay(300);
		}
		else {
			if (((random(1, 2+1))==1)) {
				DF_backward_and_turn_left();
			}
			else {
				DF_backward_and_turn_right();
			}
			delay(800);
		}
	}
	delay(100);
}
void DF_mode_C() {
	if ((mind_n_speed>230)) {
		mind_n_speed = 230;
	}
	mind_n_tracking_left = digitalRead(13);
	mind_n_tracking_right = digitalRead(14);
	if (((mind_n_tracking_left==0) && (mind_n_tracking_right==0))) {
		mind_n_tracking_flag = 10;
		DF_forward();
	}
	if (((mind_n_tracking_left==0) && (mind_n_tracking_right==1))) {
		if ((mind_n_tracking_flag>1)) {
			mind_n_tracking_flag -= 1;
		}
		DF_forward();
	}
	if (((mind_n_tracking_left==1) && (mind_n_tracking_right==0))) {
		if ((mind_n_tracking_flag<20)) {
			mind_n_tracking_flag += 1;
		}
		DF_forward();
	}
	if (((mind_n_tracking_left==1) && (mind_n_tracking_right==1))) {
		if ((mind_n_tracking_flag<10)) {
			DF_turn_left();
		}
		if ((mind_n_tracking_flag==10)) {
			DF_backward();
		}
		if ((mind_n_tracking_flag>10)) {
			DF_turn_right();
		}
	}
}
void DF_forward() {
	motor.motorRun(motor.LEFT,motor.CW,mind_n_speed);
	motor.motorRun(motor.RIGHT,motor.CW,mind_n_speed);
}
void DF_backward() {
	motor.motorRun(motor.LEFT,motor.CCW,mind_n_speed);
	motor.motorRun(motor.RIGHT,motor.CCW,mind_n_speed);
}
void DF_turn_left() {
	motor.motorRun(motor.LEFT,motor.CW,(mind_n_speed/5));
	motor.motorRun(motor.RIGHT,motor.CW,mind_n_speed);
}
void DF_backward_and_turn_left() {
	motor.motorRun(motor.LEFT,motor.CCW,(mind_n_speed/8));
	motor.motorRun(motor.RIGHT,motor.CCW,mind_n_speed);
}
void DF_turn_right() {
	motor.motorRun(motor.LEFT,motor.CW,mind_n_speed);
	motor.motorRun(motor.RIGHT,motor.CW,(mind_n_speed/5));
}
void DF_backward_and_turn_right() {
	motor.motorRun(motor.LEFT,motor.CCW,mind_n_speed);
	motor.motorRun(motor.RIGHT,motor.CCW,(mind_n_speed/8));
}
void DF_change_gear(String gear) {
	mind_n_speed = (((String(gear).toInt())*mind_n_gear_factor)+mind_n_min_speed);
}

// Event callback function
void onIRReceive(uint8_t data) {
	if ((data==93)) {
		mind_n_speed = 220;
		mind_n_mode = 0;
		DF_stop();
		MSound.playTone(0, 294, BEAT_1);
		neoPixel_15.setRangeColor(-1, -1, 0xFFFFFF);
	}
	if ((data==157)) {
		mind_n_speed = 200;
		mind_n_mode = 1;
		DF_stop();
		MSound.playTone(0, 330, BEAT_1);
		neoPixel_15.setRangeColor(-1, -1, 0x00FF00);
	}
	if ((data==29)) {
		mind_n_speed = 120;
		mind_n_mode = 2;
		DF_stop();
		MSound.playTone(0, 349, BEAT_1);
		neoPixel_15.setRangeColor(-1, -1, 0x0000FF);
	}
	if ((data==253)) {
		mind_n_motor_state = 1;
		neoPixel_15.setRangeColor(-1, -1, 0xFFFF00);
	}
	if ((data==103)) {
		mind_n_motor_state = 2;
		neoPixel_15.setRangeColor(-1, -1, 0xFF0000);
	}
	if ((data==111)) {
		mind_n_motor_state = 8;
		neoPixel_15.setRangeColor(0, 0, 0x000000);
		neoPixel_15.setRangeColor(1, 1, 0x000000);
		neoPixel_15.setRangeColor(2, 2, 0xFFFF00);
		neoPixel_15.setRangeColor(3, 3, 0xFFFF00);
	}
	if ((data==31)) {
		mind_n_motor_state = 4;
		neoPixel_15.setRangeColor(0, 0, 0xFFFF00);
		neoPixel_15.setRangeColor(1, 1, 0xFFFF00);
		neoPixel_15.setRangeColor(2, 2, 0x000000);
		neoPixel_15.setRangeColor(3, 3, 0x000000);
	}
	if ((data==173)) {
		MSound.playTone(0, 659, BEAT_1);
		DF_change_gear("9");
	}
	if ((data==181)) {
		MSound.playTone(0, 587, BEAT_1);
		DF_change_gear("8");
	}
	if ((data==189)) {
		MSound.playTone(0, 523, BEAT_1);
		DF_change_gear("7");
	}
	if ((data==165)) {
		MSound.playTone(0, 494, BEAT_1);
		DF_change_gear("6");
	}
	if ((data==199)) {
		MSound.playTone(0, 440, BEAT_1);
		DF_change_gear("5");
	}
	if ((data==239)) {
		MSound.playTone(0, 392, BEAT_1);
		DF_change_gear("4");
	}
	if ((data==133)) {
		MSound.playTone(0, 349, BEAT_1);
		DF_change_gear("3");
	}
	if ((data==231)) {
		MSound.playTone(0, 330, BEAT_1);
		DF_change_gear("2");
	}
	if ((data==207)) {
		MSound.playTone(0, 294, BEAT_1);
		DF_change_gear("1");
	}
	if ((data==87)) {
		mind_n_motor_state = 0;
	}
}
