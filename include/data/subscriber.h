#ifndef _SUBSCRIBER_H_
#define _SUBSCRIBER_H_

// Defines possible updates
class Subscriber {
  public:
    // Called on student update
    virtual void OnStudentUpdate();
    // Called on course update
    virtual void OnCourseUpdate();
    // Called on assessment update
    virtual void OnAssessmentUpdate();
    // Called on grade update
    virtual void OnGradeUpdate();
};

#endif
