#include <assert.h>
#include<iostream>
#include<vector>
using namespace std;

class Alert
{
  public:
  virtual void sendAlert(const string vitalName,const char* message) = 0;
  
};

class AlertInSms: public Alert
{
  public:
  void sendAlert(const string vitalName,const char* message)
  {
    std::cout<<"SMS sent - "<<vitalName<<" "<<message<<std::endl;
  }
};

class AlertinSound: public Alert
{
  public:
  void sendAlert(const string vitalName,const char* message)
  {
    std::cout<<"Alarm Sound - "<<vitalName<<" "<<message<<std::endl;
  }
};

struct vital
{
  string vitalName;
  int lowerLimit,upperLimit,vitalValue;
  vital(string name,int lower,int upper)
  {
    vitalName = name;
    lowerLimit = lower;
    upperLimit = upper;
  }
};

bool vitalIsOk(Alert *alert, const string vitalName,float value,int lower,int upper)
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

bool vitalsAreOk(Alert* alert,vector<vital>vitalsList) {
  bool check = true;
  
  for(int i=0;i<vitalsList.size();i++)
  {
    if(!vitalIsOk(alert,vitalsList[i].vitalName,vitalsList[i].vitalValue,vitalsList[i].lowerLimit,vitalsList[i].upperLimit))
      check=false;
  }
  
  return check;
}

void setVitalValue(vector<vital>&vitalsList,string name,int value)
{
  for(int i=0;i<vitalsList.size();i++)
  {
    if(vitalsList[i].vitalName.compare(name) == 0)
      vitalsList[i].vitalValue = value;
  }
}

int main() {

  AlertInSms smsAlert;
  AlertinSound soundAlert;

  assert(vitalIsOk(&smsAlert,"Test",5,2,8)==true);
  assert(vitalIsOk(&smsAlert,"Test",5,6,8)==false);
  assert(vitalIsOk(&soundAlert,"Test",5,2,4)==false);
  
  vector<vital>vitalsList;
  
  vitalsList.push_back(*(new vital("bpm",70,150)));
  vitalsList.push_back(*(new vital("spo2",90,250)));
  vitalsList.push_back(*(new vital("respRate",30,95)));
  
  setVitalValue(vitalsList,"bpm",95);
  setVitalValue(vitalsList,"spo2",100);
  setVitalValue(vitalsList,"respRate",70);
  assert(vitalsAreOk(&smsAlert,vitalsList) == true);
  
  
  setVitalValue(vitalsList,"bpm",60);
  setVitalValue(vitalsList,"spo2",80);
  setVitalValue(vitalsList,"respRate",40);
  assert(vitalsAreOk(&smsAlert,vitalsList) == false);
  
  setVitalValue(vitalsList,"bpm",170);
  setVitalValue(vitalsList,"spo2",95);
  setVitalValue(vitalsList,"respRate",100);
  assert(vitalsAreOk(&smsAlert,vitalsList) == false);
  
  setVitalValue(vitalsList,"bpm",80);
  setVitalValue(vitalsList,"spo2",85);
  setVitalValue(vitalsList,"respRate",40);
  assert(vitalsAreOk(&soundAlert,vitalsList) == false);
  
  setVitalValue(vitalsList,"bpm",80);
  setVitalValue(vitalsList,"spo2",70);
  setVitalValue(vitalsList,"respRate",20);
  assert(vitalsAreOk(&soundAlert,vitalsList) == false);

  setVitalValue(vitalsList,"bpm",80);
  setVitalValue(vitalsList,"spo2",95);
  setVitalValue(vitalsList,"respRate",100);
  assert(vitalsAreOk(&soundAlert,vitalsList) == false);
  
}
