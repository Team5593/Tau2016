#include "WPILib.h"
#include "CustomFunctions.h"

class Robot: public IterativeRobot
{
private:
	RobotDrive DriveSystem;
	Talon MotorShootLeft;
	Talon MotorShootRight;
	Talon MotorGrab;
	TalonSRX MotorLiftLeft;
	TalonSRX MotorLiftRight;
	Joystick Xbox;
	Joystick Joy;
	DigitalInput LimitLowLeft;
	DigitalInput LimitLowRight;


public:
	Robot() :
		DriveSystem(0,1), 	// Drive Motors
		MotorShootLeft(2),	// Left Shooter Motor
		MotorShootRight(3),	// Right Shooter Motor
		MotorGrab(4),			// Loading Motors
		MotorLiftLeft(5), 	// Left Lift Motor
		MotorLiftRight(6), 	// Right Lift Motor
		Xbox(0),			// XBOX Controller
		Joy(1),				// Joystick
		LimitLowLeft(0),		// Limit Switch Left
		LimitLowRight(1)	// Limit Switch Right
	{
	}

	void RobotInit()
	{
		DriveSystem.TankDrive(0.0,0.0); // Safety Stop
	}

	void AutonomousInit()
	{

	}

	void AutonomousPeriodic()
	{

	}

	void TeleopInit()
	{

	}

	void TeleopPeriodic()
	{
		// Inverting
		bool XboxInvert = Xbox.GetRawButton(6); 	// Is Right Shoulder Button Pressed?
		bool JoyInvert = Joy.GetRawAxis(3) < 0.5;	// Is Joystick Padle Down?

		// Set Motor Directions
		MotorShootLeft.SetInverted(JoyInvert);
		MotorShootRight.SetInverted(JoyInvert);
		MotorGrab.SetInverted(JoyInvert);
		DriveSystem.SetInvertedMotor(RobotDrive::MotorType(0), XboxInvert); // Not Clean :(
		DriveSystem.SetInvertedMotor(RobotDrive::MotorType(1), XboxInvert); // Won't let me use "DriveSystem.MotorType(0)"

		// Driving Input
		float LeftInput = AxisDeadband(Xbox.GetRawAxis(1), 0.20); // 20% Deadband
		float RightInput = AxisDeadband(Xbox.GetRawAxis(5), 0.20);
		float speed = 1.0-(Xbox.GetRawAxis(3)/2)*XboxInvert;

		// Shooting Motors
		if (Joy.GetRawButton(2)) { // Thumb Button
			MotorShootLeft.Set(0.75);
			MotorShootRight.Set(0.75);
		}
		else {
			MotorShootLeft.Set(0.0);
			MotorShootRight.Set(0.0);
		}

		// Loading Motors
		if (Joy.GetRawButton(1)) { // Trigger Button
			MotorGrab.Set(1);
		}
		else {
			MotorGrab.Set(0);
		}

		// Lifting Motors
		if (Joy.GetRawButton(5)) { // Top #5
			MotorLiftLeft.Set(-1.0);
			MotorLiftRight.Set(-1.0);
		}
		else if (Joy.GetRawButton(3)) { // Top #3
			if (!LimitLowLeft.Get())  MotorLiftLeft.Set(0.35);  else MotorLiftLeft.Set(0.0); // Left Limiting
			if (!LimitLowRight.Get()) MotorLiftRight.Set(0.35); else MotorLiftRight.Set(0.0); // Right Limiting
		}
		else {
			MotorLiftLeft.Set(0.0); // Stop Motors
			MotorLiftRight.Set(0.0);
		}


		// Drive
		if (!XboxInvert) { // Swap left and right if XboxInvert = true
			DriveSystem.TankDrive(LeftInput*speed, RightInput*speed); // Normal
		}
		else {
			DriveSystem.TankDrive(RightInput*speed, LeftInput*speed); // Swapped
		}
	}

	void TestPeriodic()
	{
	}
};

START_ROBOT_CLASS(Robot)
