#include <scheduler.h>

Scheduler sched;

class SchedulerBasic : public Base {
  public:
    void boing() {
      Serial.println("boing!");
      Scheduler::addEvent(1, (Base::ptr) &SchedulerBasic::boing, this);  
    }
};

SchedulerBasic mything;

void setup() {
  Serial.begin(9600);
  mything.boing();
}

void loop() {
  unsigned long time = micros();
  Scheduler::poll(time);
}
