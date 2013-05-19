#include "scheduler.h"
#include "Arduino.h"


Event::Event() {
  this->reset();
}
void Event::reset() {
  this->active = false;
  this->time = 0;
  this->callback = NULL;
  this->obj = NULL;
}
void Event::set(unsigned long time, void (Base::*callback)(Event *ev), Base *obj) {
  /*
  Serial.print("Registered new event: ");
  Serial.println(time);
  */
  this->time = time;
  this->obj = obj;
  this->callback = callback;
  this->active = true;
}
void Event::trigger() {
  (((Base *)(this->obj))->*callback)(this);
  this->reset();
}

Event Scheduler::events[Scheduler::maxevents];

void Scheduler::poll(unsigned long time) {
  if (time == 0) time = micros();
  for (int i = 0; i < Scheduler::maxevents; i++) {
    if (Scheduler::events[i].active && Scheduler::events[i].time <= time) {
      /*
      Serial.print("Trigger event ");
      Serial.println(i);
      */
      Scheduler::events[i].trigger();
    }
  }
}
void Scheduler::addEvent(unsigned long time, Base::ptr callback, Base *obj) {
  Scheduler::addEventMicro(time * 1000000, callback, obj);
}
void Scheduler::addEventMilli(unsigned long time, Base::ptr callback, Base *obj) {
  Scheduler::addEventMicro(time * 1000, callback, obj);
}
void Scheduler::addEventMicro(unsigned long time, Base::ptr callback, Base *obj) {
  Event *ev = Scheduler::getUnusedEvent();
  if (ev == NULL) {
    Serial.print("Error: exceeded max events - ");
    Serial.println(Scheduler::maxevents);
  } else {
    ev->set(micros() + time, callback, obj);
    /*
    Serial.print("Added event: ");
    Serial.println(time);
    */
  }
}

Event *Scheduler::getUnusedEvent() {
  for (int i = 0; i < Scheduler::maxevents; i++) {
    if (!Scheduler::events[i].active)
      return &(Scheduler::events[i]);
  }
  return NULL;
}
