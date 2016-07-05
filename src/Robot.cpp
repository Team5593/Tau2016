#include "WPILib.h"
#include "CustomFunctions.h"

class Robot: public IterativeRobot
{
private:
	RobotDrive DriveSystem;
	Talon MotorShootLeft;
	Talon MotorShootRight;
	Talon MotorLoad;
	TalonSRX MotorLiftLeft;
	TalonSRX MotorLiftRight;
	Joystick Cont;
	DigitalInput LimitLeft;
	DigitalInput LimitRight;
	//*Gyro Gyro;

public:
	Robot():
		DriveSystem(0,1), 	// Drive Motors
		MotorShootLeft(2),	// Left Shooter Motor
		MotorShootRight(3),	// Right Shooter Motor
		MotorLoad(4),		// Loading Motors
		MotorLiftLeft(5), 	// Left Lift Motor
		MotorLiftRight(6), 	// Right Lift Motor
		Cont(0),			// Controller
		LimitLeft(0),		// Limit Switch Left
		LimitRight(1)		// Limit Switch Right
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
		//float angle = Gyro::GetAngle();
		// Driving
		float forwardSpeed = -Cont.GetRawAxis(1);
		float headingAngle = Cont.GetRawAxis(4);
		if (headingAngle <= 0.2 and headingAngle >= -0.2) {
			headingAngle = 0;
		}
		float speed = 0.8; // 80%
		DriveSystem.TankDrive((forwardSpeed+headingAngle)*speed, (forwardSpeed-headingAngle)*speed);

		// Shooter Wheels
		MotorShootLeft.Set(Cont.GetRawAxis(3)*0.75-Cont.GetRawButton(6));
		MotorShootRight.Set(Cont.GetRawAxis(3)*0.75-Cont.GetRawButton(6));

		// Loading Motors
		MotorLoad.Set(Cont.GetRawAxis(2)-Cont.GetRawButton(5));

		// Lifting Motors
		if (Cont.GetRawButton(4)) {
			MotorLiftLeft.Set(-1.0);
			MotorLiftRight.Set(-1.0);
		}
		else if (Cont.GetRawButton(1)) {
			MotorLiftLeft.Set(0.35*LimitLeft.Get());
			MotorLiftRight.Set(0.35*!LimitRight.Get());
		}
		else {
			MotorLiftLeft.Set(0.0);
			MotorLiftRight.Set(0.0);
		}
	}

	void TestPeriodic()
	{
	}
};

START_ROBOT_CLASS(Robot)
