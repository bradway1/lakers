#ifndef _SUBSCRIBER_H_
#define _SUBSCRIBER_H_

class Subscriber {
  public:
    virtual void OnStudentUpdate();
    virtual void OnCourseUpdate();
    virtual void OnAssessmentUpdate();
    virtual void OnGradeUpdate();
};

#endif
