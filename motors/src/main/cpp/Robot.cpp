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


class Robot : public frc::TimedRobot
{
private:
  int counter = 0;

public:
  void TeleopPeriodic() override
  {
    frc::Compressor pcmCompressor{0, frc::PneumaticsModuleType::CTREPCM};

    //frc::Solenoid exampleSolenoidPCM{frc::PneumaticsModuleType::CTREPCM, 1};

    // bool A = m_stick.GetRawButton(1);
    bool A = xbox_stick.GetAButton();
    bool B = xbox_stick.GetBButton();
    bool X = xbox_stick.GetXButton();
    bool Y = xbox_stick.GetYButton();

    bool LT = xbox_stick.GetLeftBumper();
    bool RT = xbox_stick.GetRightBumper();

    double RightX = xbox_stick.GetRightX();
    double RightY = xbox_stick.GetRightY();

    double LeftX = xbox_stick.GetLeftX();
    double LeftY = xbox_stick.GetLeftY();

    // double r_div_2=RightY/2;
    // double m_r_div_2=-RightY/2;

    double mul = 0;
    /*
    double joystickValue_Y = m_stick.GetY();
    double joystickValue_X = m_stick.GetX();
    //bool A = m_stick.GetTrigger();
    //bool Top = m_stick.GetTop(); 
    */

    //bool pneumatics = pcmCompressor.Enabled();
    //bool pneumatics_switch = pcmCompressor.GetPressureSwitchValue();
    //double pneumatics_current = pcmCompressor.GetCompressorCurrent();

    std::cout << "This file" << " " << counter++ << std::endl;
    

    //pcmCompressor.EnableDigital();

    // .~~~~~~.Forward and backward.~~~~~~.
     if (LeftY >= 0.15 or LeftY <= -0.15)
    {
      if(RightX<-0.15){   mul=RightX;   }
      if(RightX>0.15){    mul=RightX;   }
      if(RightX<0.15 and RightX>-0.15){   mul=0;   }
      
      m_motor1.Set((LeftY+mul)/2);
      m_motor2.Set((LeftY+mul)/2);
      m_motor3.Set((-LeftY+mul)/2);
      m_motor4.Set((-LeftY+mul)/2);
    }
    // .~~~~~~.Turning right and left.~~~~~~.

    
    if ( (RightX>=0.2 or RightX<=-0.2) and LeftY<0.1 and LeftY>-0.1 )
    {
      m_motor1.Set(RightX/2);
      m_motor2.Set(RightX/2);
      m_motor3.Set(RightX/2);
      m_motor4.Set(RightX/2);
    }
    

    // .~~~~~~.Stop.~~~~~~.
    if(RightX==0 and LeftY==0 and RightX==0 and LeftY==0)
    {
      m_motor1.Set(0);
      m_motor2.Set(0);
      m_motor3.Set(0);
      m_motor4.Set(0);
    }
    // .~~~~~~.Drag.~~~~~~.
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

    if (B==true){   std::cout << "It is button B" << std::endl;    }
    if (Y==true){   std::cout << "It is button Y" << std::endl;    }
    if (X==true){   std::cout << "It is button X" << std::endl;    }

    std::cout << std::endl;
    std::cout << ".~~~~~~~~~~~~~.~~~~~~~~~~~~." << std::endl;
    std::cout << "Wartosc LeftX: " << LeftX << std::endl;
    std::cout << "Wartosc LeftY: " << LeftY << std::endl;
    std::cout << "Wartosc RightX: " << RightX << std::endl;
    std::cout << "Wartosc RightY: " << RightY << std::endl;
    std::cout << ".~~~~~~~~~~~~~.~~~~~~~~~~~~." << std::endl;
  }

private:
  frc::XboxController xbox_stick{0};
  frc::VictorSP m_motor1{0};
  frc::VictorSP m_motor2{1};
  frc::VictorSP m_motor3{2};
  frc::VictorSP m_motor4{3};
};

#ifndef RUNNING_FRC_TESTS
int main()
{
  return frc::StartRobot<Robot>();
}
#endif
