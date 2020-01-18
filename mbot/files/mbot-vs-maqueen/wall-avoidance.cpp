/*!
 * MindPlus
 * maqueen
 *
 */
#include <DFRobot_URM10.h>
#include <Maqueen_Motor.h>
#include <DFRobot_NeoPixel.h>

// Dynamic variables
volatile float mind_n_speed, mind_n_distance;
// Create an object
DFRobot_NeoPixel neoPixel_15;
DFRobot_URM10    urm10;
Maqueen_Motor    motor;


// Main program start
void setup() {
	dfrobotRandomSeed();
	neoPixel_15.begin(15, 4, 255);
	neoPixel_15.clear();
	digitalWrite(8,LOW);
	digitalWrite(12,LOW);
	while (!(Button_A.isPressed() && !Button_B.isPressed())) {yield();}
	mind_n_speed = 200;
}
void loop() {
	mind_n_distance = (urm10.getDistanceCM(1, 2));
	if ((mind_n_distance>40)) {
		motor.motorRun(motor.LEFT,motor.CW,mind_n_speed);
		motor.motorRun(motor.RIGHT,motor.CW,mind_n_speed);
	}
	else {
		if ((mind_n_distance>15)) {
			if (((random(1, 2+1))==1)) {
				motor.motorRun(motor.LEFT,motor.CW,mind_n_speed);
				motor.motorRun(motor.RIGHT,motor.CW,(mind_n_speed/5));
			}
			else {
				motor.motorRun(motor.LEFT,motor.CW,(mind_n_speed/5));
				motor.motorRun(motor.RIGHT,motor.CW,mind_n_speed);
			}
			delay(300);
		}
		else {
			if (((random(1, 2+1))==1)) {
				motor.motorRun(motor.LEFT,motor.CCW,mind_n_speed);
				motor.motorRun(motor.RIGHT,motor.CCW,(mind_n_speed/8));
			}
			else {
				motor.motorRun(motor.LEFT,motor.CCW,(mind_n_speed/8));
				motor.motorRun(motor.RIGHT,motor.CCW,mind_n_speed);
			}
			delay(800);
		}
	}
	delay(100);
}
