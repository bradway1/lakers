#include "data/observer.h"

// Pushes subscriber
void Observer::AddSubscriber(Subscriber *sub) {
  m_subscribers.push_back(sub);
}

// Iterates over subscribers to find match to remove
void Observer::RemoveSubscriber(Subscriber *sub) {
  vector<Subscriber*>::iterator it;

  for (it = m_subscribers.begin(); it != m_subscribers.end(); ++it) {
    if (*it == sub) {
      m_subscribers.erase(it);

      break;
    }
  }
}

// Notifies on student update
void Observer::NotifyStudentUpdate() {
  for (int i = 0; i < m_subscribers.size(); ++i) {
    m_subscribers[i]->OnStudentUpdate();
  }
}

// Notifies on course update
void Observer::NotifyCourseUpdate() {
  for (int i = 0; i < m_subscribers.size(); ++i) {
    m_subscribers[i]->OnCourseUpdate();
  }
}

// Notifies on assessment update
void Observer::NotifyAssessmentUpdate() {
  for (int i = 0; i < m_subscribers.size(); ++i) {
    m_subscribers[i]->OnAssessmentUpdate();
  }
}

// Notifies on grade update
void Observer::NotifyGradeUpdate() {
  for (int i = 0; i < m_subscribers.size(); ++i) {
    m_subscribers[i]->OnGradeUpdate();
  }
}
