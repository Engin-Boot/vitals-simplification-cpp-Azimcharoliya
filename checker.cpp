#include <assert.h>
#include<iostream>

const int bpmLimits[] = {70,150};
const int spo2Min = 90;
const int respRateLimits[] = {30,95};

class Alert
{
  public:
  virtual void sendAlert(const char* vitalName,const char* message) = 0;
  
};

class AlertInSms: public Alert
{
  public:
  void sendAlert(const char* vitalName,const char* message)
  {
    std::cout<<"SMS sent - "<<vitalName<<" "<<message<<std::endl;
  }
};

class AlertinSound: public Alert
{
  public:
  void sendAlert(const char* vitalName,const char* message)
  {
    std::cout<<"Alarm Sound - "<<vitalName<<" "<<message<<std::endl;
  }
};

class Vitals{

  private:
    Alert *alert;

  public:

  void setAlertType(Alert * alert)
  {
    this->alert = alert;
  }

  bool vitalIsOk(const char * vitalName,float value,int lower,int upper)
  {
    if(value < lower)
    {
      alert->sendAlert(vitalName,"is low");
      return false;
    }
    else if(value > upper)
    {
      alert->sendAlert(vitalName,"is high");
      return false;
    }
    return true;
    
  }

  bool vitalIsOk(const char* vitalName,float value,int lower)
  {
    if(value < lower)
    {
      alert->sendAlert(vitalName,"is low");
      return false;
    }
    return true;
  }

  bool vitalsAreOk(float bpm, float spo2, float respRate) {
    bool check = true;
    if(!vitalIsOk("bpm",bpm,bpmLimits[0],bpmLimits[1]))
      check = false;
    if(!vitalIsOk("spo2",spo2,spo2Min))
      check = false;
    if(!vitalIsOk("Resprate",respRate,respRateLimits[0],respRateLimits[1]))
      check = false;
    return check;
  }

};

int main() {

  AlertInSms smsAlert;
  
  Vitals vital;
  vital.setAlertType(&smsAlert); 

  assert(vital.vitalIsOk("Test",5,2,8)==true);
  assert(vital.vitalIsOk("Test",5,6,8)==false);
  assert(vital.vitalIsOk("Test",5,2,4)==false);
  assert(vital.vitalIsOk("Test",5,2)==true);
  assert(vital.vitalIsOk("Test",5,10)==false);
  assert(vital.vitalsAreOk(80, 95, 60) == true);
  assert(vital.vitalsAreOk(60, 80, 40) == false);
  assert(vital.vitalsAreOk(170, 95, 40) == false);
  assert(vital.vitalsAreOk(80, 85, 40) == false);
  assert(vital.vitalsAreOk(80, 95, 20) == false);
  assert(vital.vitalsAreOk(80, 95, 100) == false);
}
