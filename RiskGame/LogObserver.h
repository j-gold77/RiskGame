
#pragma once
#include <list>
#include <string>
using namespace std;

// ILoggable Class Declaration 
class ILoggable {

public:
    ILoggable();
    ~ILoggable();
    virtual string stringToLog() = 0;

};
// Observer class Declaration  
class Observer {

public:
    ~Observer();
    virtual void Update(ILoggable* iLog) = 0;


protected:
    Observer();

};

// Subject class Declaration
class Subject {

public:
    virtual void Attach(Observer* o);
    virtual void Detach(Observer* o);
    virtual void Notify(ILoggable* iLog);
    Subject();
    ~Subject();
private:
    list<Observer*>* _observers;

};

// LogObserver class Declaration
class LogObserver : public Observer {

public:

    LogObserver(Subject* s);
    ~LogObserver();
    void Update(ILoggable* iLog);

private:
    Subject* _subject;


};