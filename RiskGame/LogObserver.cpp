#include<iostream>
#include<fstream>
#include"LogObserver.h"

using namespace std;
//ILoggable Class Implementation
ILoggable::ILoggable()
{
}

ILoggable::~ILoggable()
{
}



//Observer	Class Implementation
Observer::~Observer()
{
}

Observer::Observer()
{
}

//Subject	Class Implementation
Subject::Subject() {
    _observers = new list<Observer*>;
}

// once object is deleted, deletes the list of observers attached to it
Subject::~Subject() {
    delete _observers;
}
// attaches observer to the Subject
void Subject::Attach(Observer* o) {
    _observers->push_back(o);
};

// detaches observer from said subject
void Subject::Detach(Observer* o) {
    _observers->remove(o);
};

// when a subjects method is called you use notify to let the observer know
void Subject::Notify(ILoggable* iLog) {
    list<Observer*>::iterator i = _observers->begin();
    for (; i != _observers->end(); ++i)
        (*i)->Update(iLog);
};




//LogObserver Class Implementation 

LogObserver::LogObserver(Subject* s) {
    //Upon instantiation, attaches itself to a Subject Subclass
    _subject = s;
    _subject->Attach(this);
};
LogObserver::~LogObserver() {
    //Upon destruction, detaches itself to a Subject Subclass�
    _subject->Detach(this);
};

// Log Observer Update() implementation
void LogObserver::Update(ILoggable* iLog)
{
    // create fileStreamObject
    ofstream outputfilestream;

    // open correct file use  object
    outputfilestream.open("gameLogger.txt", std::ios_base::app);

    //enter string to file
    outputfilestream << iLog->stringToLog() << endl;

    //close file
    outputfilestream.close();


}