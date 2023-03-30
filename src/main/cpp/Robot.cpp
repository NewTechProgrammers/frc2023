#include <numbers>
#include <iostream>
#include <frc/motorcontrol/PWMMotorController.h>
#include <frc/motorcontrol/VictorSP.h>
#include <frc/motorcontrol/Spark.h>
#include <frc/system/plant/DCMotor.h>
#include <frc/Encoder.h>
#include <frc/Joystick.h>
#include <frc/XboxController.h>
#include <frc/TimedRobot.h>
#include <frc/motorcontrol/PWMSparkMax.h>
#include <frc/Compressor.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/DoubleSolenoid.h>
#include <frc/PneumaticsControlModule.h>
#include "units/voltage.h"
// #include <frc/RobotController>

class Robot : public frc::TimedRobot
{
private:
  int counter = 0;
  int buttonCounter = 0;
  int pack = 0;

  frc::Joystick m_stick{0};
  frc::XboxController xbox_stick{1};

  frc::VictorSP m_motor0{0};  // wheel
  frc::VictorSP m_motor1{1};  // wheel
  frc::VictorSP m_motor2{2};  // wheel
  frc::VictorSP m_motor3{3};  // wheel
  frc::VictorSP m_motor4{4};  // frame
  frc::VictorSP m_motor5{5};  // frame
  frc::VictorSP m_motor6{6};  // header

  // frc::DCMotor DCMotor;

  units::volt_t nominalVoltage;

  frc::Compressor phCompressor{1, frc::PneumaticsModuleType::REVPH};
  frc::DoubleSolenoid m_doubleSolenoid{frc::PneumaticsModuleType::REVPH, 0, 1};
  frc::DoubleSolenoid m_doubleSolenoid_II{frc::PneumaticsModuleType::REVPH, 2, 3};



  // .getBatteryVoltage();
  

  static constexpr int kSolenoidButton = 1;
  // -----------Solenoid 1-----------------------
  static constexpr int kDoubleSolenoidForward = 2;
  static constexpr int kDoubleSolenoidReverse = 3;
  // --------------------------------------------

  static constexpr int button8 = 8;
  bool pressureSwitch = phCompressor.GetPressureSwitchValue();
  bool isenable = phCompressor.IsEnabled();
  /*.~~~~~~~~~~.~~~~~~~~~~~~~~~~~~~~~~.~~~~~~~~~~.*/

  int statement1=0;
  int statement2=0;
  bool header = false;
  bool compressor_status = false;


public:
  void TeleopPeriodic() override
  {
    /*.~~~~~~~~~~.Gamepad.~~~~~~~~~~.*/
    double RightX = xbox_stick.GetRightX();
    double LeftY = xbox_stick.GetLeftY();
    double RightY = xbox_stick.GetRightY();

    bool A = xbox_stick.GetAButton();
    bool B = xbox_stick.GetBButton();
    bool X = xbox_stick.GetXButton();
    bool Y = xbox_stick.GetYButton();

    bool LB = xbox_stick.GetLeftBumper();
    // bool RT = xbox_stick.GetRightBumper();

    
    // double LeftX = xbox_stick.GetLeftX();

    /*.~~~~~~~~~~.Gamepad2.~~~~~~~~~~.*/
    double Slider = m_stick.GetThrottle();
    double JoystickX = m_stick.GetX();
    double JoystickY = m_stick.GetY();


    
    bool button1 = m_stick.GetRawButton(1);
    bool button2 = m_stick.GetRawButton(2); 
    bool button5 = m_stick.GetRawButton(5); // solenoid
    bool button4 = m_stick.GetRawButton(4); // solenoid header
    bool button3 = m_stick.GetRawButton(3); // solenoid frame
    bool button6 = m_stick.GetRawButton(6); // solenoid header
    bool button8 = m_stick.GetRawButton(8);
    bool button12 = m_stick.GetRawButton(12); // compressor

    /*.~~~~~~~~~~.Header.~~~~~~~~~~.*/
    

    if(button8){header=true;}
    if(header==true)    {
      statement2++;
      /*
      if(statement2<=100){m_motor4.Set(0.45);m_motor5.Set(0.45);}
      if(statement2>100 and statement2<=200){m_motor4.Set(0.2);m_motor5.Set(0.2);}
      if(statement2>200 and statement2<=300){m_motor4.Set(0.1);m_motor5.Set(0.1);}
      if(statement2>300 and statement2<=400){m_motor4.Set(0);m_motor5.Set(0);}
      */

      
      if(statement2<=50){m_motor4.Set(-0.6);m_motor5.Set(-0.6);}
      if(statement2>60 and statement2<=180){m_motor4.Set(0.3);m_motor5.Set(0.3);}
      if(statement2>180 and statement2<=250){m_motor4.Set(0.25);m_motor5.Set(0.1);}
      if(statement2>250 and statement2<=300){m_motor4.Set(0);m_motor5.Set(0);}
      if(statement2>=300){header=false; statement2=0;}
      
    }

    if(button1==true){m_motor5.Set(0.2); m_motor4.Set(0.2);}
    if(button2==true){m_motor5.Set(-0.2); m_motor4.Set(-0.2);}

    // Header
    // if(Slider>=0.5 or Slider<=-0.5){ m_motor6.Set(Slider); }
    // else{m_motor6.Set(0);}

    if(JoystickY>=0.3 or JoystickY<=-0.3)
    {
      m_motor4.Set(-JoystickY/1.5); m_motor5.Set(-JoystickY/1.5); 
    }
    else if(JoystickY<=0.3 and JoystickY>=-0.3 and statement2==0 and statement1==false and button2==false and button1==false)
    { m_motor4.Set(0);
      m_motor5.Set(0); }

    
    // int option;


    /*.~~~~~~~~~~.Compressor & Solenoids.~~~~~~~~~~.*/
    
    
    m_doubleSolenoid.Set(frc::DoubleSolenoid::kOff);

    if(Slider<=-0.4 and Slider>=-1){phCompressor.EnableDigital();}
    else if(Slider>-0.4 and Slider<=1) { phCompressor.Disable(); }
  
    /*.______________.Robot ride control._____________.*/

    /*.~~~~~~~~~~.Multiplicators.~~~~~~~~~~.*/
    double mul = 0.0;
   

    /*.~~~~~~~~~~.Forward and backward.~~~~~~~~~~.*/
    if (LeftY >= 0.25 or LeftY <= -0.25)
    { if (RightX < -0.25){ mul = RightX; }
      if (RightX > 0.25){ mul = RightX; }
      if (RightX < 0.25 and RightX > -0.25){ mul = 0; }

      m_motor0.Set((-LeftY + mul) / 3);
      m_motor1.Set((-LeftY + mul) / 3);

      m_motor2.Set((LeftY + mul) / 3);
      m_motor3.Set((LeftY + mul) / 3); }

    /*.~~~~~~~~~~.Turning right and left.~~~~~~~~~~.*/
    if ((RightX >= 0.2 or RightX <= -0.2) and LeftY < 0.2 and LeftY > -0.2)
    { m_motor0.Set(RightX / 2);
      m_motor1.Set(RightX / 2);
      m_motor2.Set(RightX / 2);
      m_motor3.Set(RightX / 2); }
    /*.~~~~~~~~~~.Stop.~~~~~~~~~~.*/
    if ((RightX > -0.15 and RightX < 0.15) and (LeftY > -0.15 and LeftY < 0.15))
    { m_motor0.Set(0);
      m_motor1.Set(0);
      m_motor2.Set(0);
      m_motor3.Set(0); }
    /*.~~~~~~~~~~.Drag.~~~~~~~~~~.*/
    if (A)
    { m_motor0.Set(0);
      m_motor1.Set(0);
      m_motor2.Set(0);
      m_motor3.Set(0); }
    /*.~~~~~~~~~~.TURBO.~~~~~~~~~~.*/
    /*
    if(RT==true and LT==true)
    {
      m_motor1.Set(-1);
      m_motor2.Set(-1);
      m_motor3.Set(1);
      m_motor4.Set(1);
    }*/

    /*.______________._________________._____________.*/

    /*.~~~~~~~~~~.Solenoids.~~~~~~~~~~.*/

    //-----------Solenoid 1-------------
    if (button5) { m_doubleSolenoid.Set(frc::DoubleSolenoid::kForward); }
    else if (button3) { m_doubleSolenoid.Set(frc::DoubleSolenoid::kReverse); }
    else { m_doubleSolenoid.Set(frc::DoubleSolenoid::kOff); }
    //-------------Solenoid 2------------
    if (button6){ m_doubleSolenoid_II.Set(frc::DoubleSolenoid::kForward); }
    else if (button4){ m_doubleSolenoid_II.Set(frc::DoubleSolenoid::kReverse); }
    else { m_doubleSolenoid_II.Set(frc::DoubleSolenoid::kOff); }

    /*
    int pov = m_stick.GetPOV();
    if (pov == 270) {   m_doubleSolenoid_II.Set(frc::DoubleSolenoid::kForward);    }
    else if (pov == 90) {   m_doubleSolenoid_II.Set(frc::DoubleSolenoid::kReverse);    }
    else{   m_doubleSolenoid_II.Set(frc::DoubleSolenoid::kOff);   }
    */

    // if (m_stick.GetRawButton(kSolenoidButton))
    // {
    //   m_doubleSolenoid.Set(frc::DoubleSolenoid::kOff);
    // }
    
    std::cout << "This file" << " " << pack++ << std::endl;
    std::cout << "statement1: " << statement1 << "\n";
    std::cout << "statement2: " << statement2 << "\n";
    std::cout << "LeftY: " << LeftY << "\n";
    std::cout << "RightY: " << RightY << "\n";
    std::cout << "JoystickX: " << JoystickX << "\n";
    std::cout << "JoystickY: " << JoystickY << "\n";
    std::cout << "Slider: " << Slider << "\n";
    std::cout << "Voltage: " << int(nominalVoltage) << "\n";
    
  }
};

#ifndef RUNNING_FRC_TESTS
int main()
{
  return frc::StartRobot<Robot>();
}
#endif

