#ifndef _OBSERVER_H_
#define _OBSERVER_H_

#include "data\subscriber.h"

#include <vector>

using std::vector;

// Observer declaration of Observer pattern
class Observer {
  public:
    // Adds listening subscriber
    void AddSubscriber(Subscriber *sub);
    // Remove listening subscriber
    void RemoveSubscriber(Subscriber *sub);

  protected:
    // Notify all subscribers on student table update
    void NotifyStudentUpdate();
    // Notify all subscribers on course table update
    void NotifyCourseUpdate();
    // Notify all subscribers on assessment table update
    void NotifyAssessmentUpdate();
    // Notify all subscribers on grade table update
    void NotifyGradeUpdate();

  private:
    // Vector for storing subscribers
    vector<Subscriber *> m_subscribers;
};

#endif
