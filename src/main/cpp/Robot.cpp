/*
#include <frc/DoubleSolenoid.h>
#include <frc/Joystick.h>
#include <frc/PneumaticsControlModule.h>
#include <frc/Solenoid.h>
#include <frc/TimedRobot.h>
#include <frc/XboxController.h>
#include <frc/Compressor.h>
#include <iostream>

class Robot : public frc::TimedRobot
{
public:
 

  void TeleopPeriodic() override
  {
    bool pressureSwitch = phCompressor.GetPressureSwitchValue();
    bool isenable = phCompressor.IsEnabled();
    phCompressor.Disable();
    m_doubleSolenoid.Set(frc::DoubleSolenoid::kOff);

    if (m_stick.GetRawButton(button8)){  counter++;  }
    if (counter%2==0){   phCompressor.Disable();   } 
    if(counter%2!=0){ phCompressor.EnableDigital();  }
    
    if (m_stick.GetRawButton(kDoubleSolenoidForward))
    {  
    m_doubleSolenoid.Set(frc::DoubleSolenoid::kForward);
    }
    if (m_stick.GetRawButton(kDoubleSolenoidReverse))
    {  
    m_doubleSolenoid.Set(frc::DoubleSolenoid::kReverse);
    }
    if (m_stick.GetRawButton(kSolenoidButton))
    {  
    m_doubleSolenoid.Set(frc::DoubleSolenoid::kOff);
    }
    
    // Dodane
    double leftY = m_xbox.GetLeftY();
    double rightX = m_xbox.GetRightX();

    // TODO: Steruj silnikami za pomocą pomiarów z gałek pada Xbox
  }

private:
  int counter = 0;
 
  frc::Compressor phCompressor{1, frc::PneumaticsModuleType::REVPH};
  frc::DoubleSolenoid m_doubleSolenoid{frc::PneumaticsModuleType::REVPH, 2, 3};
  frc::Joystick m_stick{0};
  frc::XboxController m_xbox{1}; // Dodane

  static constexpr int kSolenoidButton = 1;
  static constexpr int kDoubleSolenoidForward = 2;
  static constexpr int kDoubleSolenoidReverse = 3;
  static constexpr int button8 = 8;
};

#ifndef RUNNING_FRC_TESTS
int main()
{
  return frc::StartRobot<Robot>();
}
#endif
*/

#include <numbers>
#include <iostream>
#include <frc/motorcontrol/PWMMotorController.h>
#include <frc/motorcontrol/VictorSP.h>
#include <frc/Encoder.h>
#include <frc/Joystick.h>
#include <frc/XboxController.h>
#include <frc/TimedRobot.h>
#include <frc/motorcontrol/PWMSparkMax.h>
#include <frc/Compressor.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/DoubleSolenoid.h>
#include <frc/PneumaticsControlModule.h>


class Robot : public frc::TimedRobot
{
private:
  int counter = 0;
  int pack = 0;
  frc::XboxController xbox_stick{0};
  frc::VictorSP m_motor1{0};
  frc::VictorSP m_motor2{1};
  frc::VictorSP m_motor3{2};
  frc::VictorSP m_motor4{3};
  frc::VictorSP m_motor5{4};
  frc::Compressor phCompressor{1, frc::PneumaticsModuleType::REVPH};
  frc::DoubleSolenoid m_doubleSolenoid{frc::PneumaticsModuleType::REVPH, 2, 3};
  frc::DoubleSolenoid m_doubleSolenoid_II{frc::PneumaticsModuleType::REVPH, 4, 5};
  frc::Joystick m_stick{1};
  

  static constexpr int kSolenoidButton = 1;
// -----------Solenoid 1-----------------------
  static constexpr int kDoubleSolenoidForward = 2;
  static constexpr int kDoubleSolenoidReverse = 3;
// ----------------------------------

  static constexpr int button8 = 8;
  bool pressureSwitch = phCompressor.GetPressureSwitchValue();
  bool isenable = phCompressor.IsEnabled();
  
    /*.~~~~~~~~~~.~~~~~~~~~~~~~~~~~~~~~~.~~~~~~~~~~.*/

    /*.~~~~~~~~~~.Gamepad.~~~~~~~~~~.*/
    

    

    // bool LT = xbox_stick.GetLeftBumper();
    // bool RT = xbox_stick.GetRightBumper();

    // double RightY = xbox_stick.GetRightY();
    // double LeftX = xbox_stick.GetLeftX();
    /*.~~~~~~~~~~.~~~~~~~.~~~~~~~~~~.*/

public:
  void TeleopPeriodic() override
  {
//--------------Ramię----------------------
    double RightX_AR = m_stick.GetY();

     m_motor5.Set(RightX_AR);
//-----------Jazda-------------------------
    double RightX = xbox_stick.GetRightX();
    double LeftY = xbox_stick.GetLeftY();

    bool A = xbox_stick.GetAButton();
    bool B = xbox_stick.GetBButton();
    bool X = xbox_stick.GetXButton();
    bool Y = xbox_stick.GetYButton();

    double JoyStickRightX=m_stick.GetX();
    double JoyStickRightY=m_stick.GetY();

    /*.~~~~~~~~~~.Compressor & Solenoids.~~~~~~~~~~.*/
    phCompressor.Disable();
    m_doubleSolenoid.Set(frc::DoubleSolenoid::kOff);

    double mul = 0.0;
    double joymul=0.0;
    std::cout << "This file" << " " << pack++ << std::endl; 

    /*.~~~~~~~~~~.Compressor.~~~~~~~~~~.*/
    if (m_stick.GetRawButton(button8)){  counter++;  }
    if (counter%2==0){   phCompressor.Disable();   } 
    if(counter%2!=0){ phCompressor.EnableDigital();  }
    /*.~~~~~~~~~~.~~~~~~~~~~.~~~~~~~~~~.*/

    /*
    if(JoyStickRightY>=0.15 or JoyStickRightY<=-0.15){
      if(JoyStickRightX<-0.15){   joymul=JoyStickRightX;   }
      if(JoyStickRightX>0.15){    joymul=JoyStickRightX;   }
      if(JoyStickRightX<0.15 and JoyStickRightX>-0.15){   joymul=0;   }

      m_motor1.Set((JoyStickRightY+joymul)/2);
      m_motor2.Set((JoyStickRightY+joymul)/2);
      m_motor3.Set((-JoyStickRightY+joymul)/2);
      m_motor4.Set((-JoyStickRightY+joymul)/2);
    }
    */

    // .~~~~~~~~~~.Forward and backward.~~~~~~~~~~.
     if (LeftY >= 0.25 or LeftY <= -0.25)
    {
      if(RightX<-0.25){   mul=RightX;   }
      if(RightX>0.25){    mul=RightX;   }
      if(RightX<0.25 and RightX>-0.25){   mul=0;   }
      
      m_motor1.Set((LeftY+mul)/2);
      m_motor2.Set((LeftY+mul)/2);
      m_motor3.Set((-LeftY+mul)/2);
      m_motor4.Set((-LeftY+mul)/2);
    }
    // .~~~~~~~~~~.Turning right and left.~~~~~~~~~~.
    if ( (RightX>=0.2 or RightX<=-0.2) and LeftY<0.2 and LeftY>-0.2 )
    {
      m_motor1.Set(RightX/2);
      m_motor2.Set(RightX/2);
      m_motor3.Set(RightX/2);
      m_motor4.Set(RightX/2);
    }
    // .~~~~~~~~~~.Stop.~~~~~~~~~~.
    if(/*RightX==0 and LeftY==0 and RightX==0 and LeftY==0*/ (RightX>-0.15 and RightX<0.15) and (LeftY>-0.15 and LeftY<0.15))
    {
      m_motor1.Set(0);
      m_motor2.Set(0);
      m_motor3.Set(0);
      m_motor4.Set(0);
    }
    // .~~~~~~~~~~.Drag.~~~~~~~~~~.
    if  (A == true)
    {
      m_motor1.Set(0);
      m_motor2.Set(0);
      m_motor3.Set(0);
      m_motor4.Set(0);
    }


    /*.~~~~~~~~~~.TURBO.~~~~~~~~~~.*/
    /*
    if(RT==true and LT==true)
    {
      m_motor1.Set(-1);
      m_motor2.Set(-1);
      m_motor3.Set(1);
      m_motor4.Set(1);
    }*/

    /*.~~~~~~~~~~.Solenoid.~~~~~~~~~~.*/
    //-----------Solenoid 1-------------
    if (m_stick.GetRawButton(kDoubleSolenoidForward)){    m_doubleSolenoid.Set(frc::DoubleSolenoid::kForward);   }
    if (m_stick.GetRawButton(kDoubleSolenoidReverse)){    m_doubleSolenoid.Set(frc::DoubleSolenoid::kReverse);   }
   //-------------Solenoid 2------------

    int pov = m_stick.GetPOV();

    if (pov == 270) {
      m_doubleSolenoid_II.Set(frc::DoubleSolenoid::kForward);
    }
//༼ つ ◕_◕ ༽つ      ¯\_(ツ)_/¯
    else if (pov == 90) {
      m_doubleSolenoid_II.Set(frc::DoubleSolenoid::kReverse);
    }

    else{
      m_doubleSolenoid_II.Set(frc::DoubleSolenoid::kOff);
    }

    if (m_stick.GetRawButton(kSolenoidButton)){   m_doubleSolenoid.Set(frc::DoubleSolenoid::kOff);    }
    /*.~~~~~~~~~~.~~~~~~~~.~~~~~~~~~~.*/

    std::cout << std::endl;
    std::cout << ".~~~~~~~~~~~~~.~~~~~~~~~~~~." << std::endl;
    std::cout << "Wartosc LeftY: " << LeftY << std::endl;
    std::cout << "Wartosc RightX: " << RightX << std::endl;
    std::cout << ".~~~~~~~~~~~~~.~~~~~~~~~~~~." << std::endl;
  }

private:
  
};

#ifndef RUNNING_FRC_TESTS
int main()
{
  return frc::StartRobot<Robot>();
}
#endif
