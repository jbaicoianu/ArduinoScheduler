/* Basic example of Arduino Scheduler library
 * 
 * Prints "boing!" over serial on 1 second intervals
 */

#include <scheduler.h>

class SchedulerBasic : public Base {
  public:
    void boing() {
      Serial.println("boing!");

      // Schedule next interval
      Scheduler::addEvent(1, (Base::ptr) &SchedulerBasic::boing, this);  
    }
};

SchedulerBasic mything;

void setup() {
  Serial.begin(9600);
  mything.boing();
}

void loop() {
  Scheduler::poll();
}
