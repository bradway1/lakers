#include "data/observer.h"

void Observer::AddSubscriber(Subscriber *sub) {
  m_subscribers.push_back(sub);
}

void Observer::RemoveSubscriber(Subscriber *sub) {
  vector<Subscriber*>::iterator it;

  for (it = m_subscribers.begin(); it != m_subscribers.end(); ++it) {
    if (*it == sub) {
      m_subscribers.erase(it);

      break;
    }
  }
}

void Observer::NotifyStudentUpdate() {
  for (int i = 0; i < m_subscribers.size(); ++i) {
    m_subscribers[i]->OnStudentUpdate();
  }
}

void Observer::NotifyCourseUpdate() {
  for (int i = 0; i < m_subscribers.size(); ++i) {
    m_subscribers[i]->OnCourseUpdate();
  }
}

void Observer::NotifyAssessmentUpdate() {
  for (int i = 0; i < m_subscribers.size(); ++i) {
    m_subscribers[i]->OnAssessmentUpdate();
  }
}

void Observer::NotifyGradeUpdate() {
  for (int i = 0; i < m_subscribers.size(); ++i) {
    m_subscribers[i]->OnGradeUpdate();
  }
}
