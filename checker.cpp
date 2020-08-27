#include <assert.h>

const int bpmLimits[] = {70,150};
const int spo2Min = 90;
const int respRateLimits[] = {30,95};

bool vitalIsOk(float value,int lower,int upper)
{
	return (value >= lower && value <= upper);
}

bool vitalIsOk(float value,int lower)
{
	return (value >= lower);
}

bool vitalsAreOk(float bpm, float spo2, float respRate) {
	return (vitalIsOk(bpm,bpmLimits[0],bpmLimits[1]) && vitalIsOk(spo2,spo2Min) && vitalIsOk(respRate,respRateLimits[0],respRateLimits[1]));
}

int main() {
  assert(vitalIsOk(5,2,8)==true);
  assert(vitalIsOk(5,6,8)==false);
  assert(vitalIsOk(5,2,4)==false);
  assert(vitalIsOk(5,2)==true);
  assert(vitalIsOk(5,10)==false);
  assert(vitalsAreOk(80, 95, 60) == true);
  assert(vitalsAreOk(60, 90, 40) == false);
  assert(vitalsAreOk(170, 95, 40) == false);
  assert(vitalsAreOk(80, 85, 40) == false);
  assert(vitalsAreOk(80, 95, 20) == false);
  assert(vitalsAreOk(80, 95, 100) == false);
}
