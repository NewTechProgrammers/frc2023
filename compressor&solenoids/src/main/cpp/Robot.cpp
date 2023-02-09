#include <frc/DoubleSolenoid.h>
#include <frc/Joystick.h>
#include <frc/PneumaticsControlModule.h>
#include <frc/Solenoid.h>
#include <frc/TimedRobot.h>
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
  }

private:
  int counter = 0;
 
  frc::Compressor phCompressor{1, frc::PneumaticsModuleType::REVPH};
  frc::DoubleSolenoid m_doubleSolenoid{frc::PneumaticsModuleType::REVPH, 2, 3};
  frc::Joystick m_stick{0};

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
