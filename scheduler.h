#ifndef _SCHEDULER_H
#define _SCHEDULER_H

class Event;
class Base {
  public:
    typedef void (Base::*ptr)(Event *ev);
};
class Event {
  public:
    bool active;
    unsigned long time;
    Base::ptr callback;
    Base *obj;
    
    Event();
    void reset();
    void set(unsigned long time, void (Base::*callback)(Event *ev), Base *obj);
    void trigger();
};
class Scheduler {
  public:
    static const int maxevents = 10;
    static Event events[Scheduler::maxevents];

    static void poll(unsigned long time=0);
    static void addEvent(unsigned long time, Base::ptr callback, Base *obj);
    static void addEventMilli(unsigned long time, Base::ptr callback, Base *obj);
    static void addEventMicro(unsigned long time, Base::ptr callback, Base *obj);
    static Event *getUnusedEvent();
};

/* Macros for cleaner syntax */
#define SCHEDULER_ADDEVENT(t, classname, funcname, ref) Scheduler::addEvent(t, (Base::ptr) &classname::funcname, ref);
#define SCHEDULER_ADDEVENTMILLI(t, classname, funcname, ref) Scheduler::addEventMilli(t, (Base::ptr) &classname::funcname, ref);
#define SCHEDULER_ADDEVENTMICRO(t, classname, funcname, ref) Scheduler::addEventMicro(t, (Base::ptr) &classname::funcname, ref);

#endif
