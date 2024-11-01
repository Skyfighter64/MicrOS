#ifndef THREAD_H
#define THREAD_H


/*
  Base class for threads running on MicrOS

  rules for threads:
  - run function should not be blocking and as fast as possible
  - Initialization and running of a thread is handled by the OS

  - A thread can be paused by calling Pause() and unpaused by calling Continue() manually
  - A thread can be paused for a certain time in ms using Sleep(int ms). Note that this time is not entirely accurate
      and depends on the performance and number of the other threads currently runnign on the OS
*/

/*
    TODO: Add Thread.cpp and think of a way to implement the functions
*/


class Thread
{
  public:
    //the name of this thread, May not be unique
    char * name;

    virtual void Initialize() = 0;
    virtual void Run() = 0;
    void Pause();
    void Continue();
    //TODO:
    //void Sleep(int ms);
    bool isPaused();

    enum State
    {
      ACTIVE = 0,
      PAUSED = 1
    };

  protected:
    //flag indicating the current state of this thread
    State threadState;

};
#endif
