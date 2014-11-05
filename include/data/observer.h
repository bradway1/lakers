#ifndef _OBSERVER_H_
#define _OBSERVER_H_

#include "data\subscriber.h"

#include <vector>

using std::vector;

class Observer {
  public:
    void AddSubscriber(Subscriber *sub);
    void RemoveSubscriber(Subscriber *sub);

  protected:
    void NotifyStudentUpdate();
    void NotifyCourseUpdate();
    void NotifyAssessmentUpdate();
    void NotifyGradeUpdate();

  private:
    vector<Subscriber *> m_subscribers;
};

#endif
