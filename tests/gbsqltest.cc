#include "gtest/gtest.h"

#include "sql/gbsql.h"
#include "data/course.h"

#include <wx/filefn.h>

#include <vector>

using std::vector;

class GBSqlTest : public ::testing::Test {
    protected:
        GBSql *sql;

        virtual void SetUp() {
            if (wxFileExists("gb.db")) {
                wxRemoveFile("gb.db");
            }

            sql = new GBSql();
        };

        virtual void TearDown() {
            sql->Close();
        }
};

TEST_F(GBSqlTest, testAddCourse) {
    Course c;
    
    c.SetId("1");
    c.SetTitle("MATH-217");
    c.SetStart(wxDateTime::Today());
    c.SetEnd(wxDateTime::Today());

    int r = sql->InsertCourse(c);

    ASSERT_EQ(1, r);
}

TEST_F(GBSqlTest, testUpdateCourse) {
    Course c;

    c.SetId("1");
    c.SetTitle("MATH-217");
    c.SetStart(wxDateTime::Today());
    c.SetEnd(wxDateTime::Today());

    sql->InsertCourse(c);

    c.SetTitle("CSCI-217");

    int r = sql->UpdateCourse(c);

    ASSERT_EQ(1, r);
}

TEST_F(GBSqlTest, testDeleteCourse) {
    Course c;
    
    c.SetId("1");
    c.SetTitle("MATH-217");
    c.SetStart(wxDateTime::Today());
    c.SetEnd(wxDateTime::Today());

    sql->InsertCourse(c);

    int r = sql->DeleteCourse(c);

    ASSERT_EQ(1, r);
}

TEST_F(GBSqlTest, testSelectCourse) {
    Course c[2];

    c[0].SetId("1");
    c[0].SetTitle("MATH-217");
    c[0].SetStart(wxDateTime::Today());
    c[0].SetEnd(wxDateTime::Today());

    c[1].SetId("2");
    c[1].SetTitle("CSCI-217");
    c[1].SetStart(wxDateTime::Today());
    c[1].SetEnd(wxDateTime::Today());

    sql->InsertCourse(c[0]);

    sql->InsertCourse(c[1]);

    vector<Course*> result;

    int r = sql->SelectCourse(&result);

    ASSERT_EQ(2, r);

    for (int i = 0; i < r; ++i) {
        ASSERT_STREQ(c[i].GetId()->fn_str(), result[i]->GetId()->fn_str());
    }
}

TEST_F(GBSqlTest, testInsertStudent) {
    Student s;

    s.SetStudentId("1");
    s.SetFirst("John");
    s.SetLast("Doe");

    int r = sql->InsertStudent(s);

    ASSERT_EQ(1, r);
}

TEST_F(GBSqlTest, testUpdateStudent) {
    Student s;

    s.SetStudentId("1");
    s.SetFirst("John");
    s.SetLast("Doe");

    sql->InsertStudent(s);

    s.SetFirst("Jimmy");

    int r = sql->UpdateStudent(s);

    ASSERT_EQ(1, r);
}

TEST_F(GBSqlTest, testDeleteStudent) {
    Student s;

    s.SetStudentId("1");
    s.SetFirst("John");
    s.SetLast("Doe");

    sql->InsertStudent(s);

    int r = sql->DeleteStudent(s);

    ASSERT_EQ(1, r);
}

TEST_F(GBSqlTest, testSelectStudent) {
    Student s[2];

    s[0].SetStudentId("1");
    s[0].SetFirst("John");
    s[0].SetLast("Doe");

    s[1].SetStudentId("2");
    s[1].SetFirst("Helen");
    s[1].SetLast("Doe");

    for (int i = 0; i < 2; ++i) {
        sql->InsertStudent(s[i]);
    }

    vector<Student*> sVec;

    int r = sql->SelectStudents(&sVec);

    ASSERT_EQ(2, r);
}

TEST_F(GBSqlTest, testAddSCRelation) {
    Student s;

    s.SetStudentId("1");
    s.SetFirst("John");
    s.SetLast("Doe");

    Course c;

    c.SetId("1");
    c.SetTitle("MATH-217");
    c.SetStart(wxDateTime::Today());
    c.SetEnd(wxDateTime::Today());

    int r = sql->AddStudentCourseRelation(s, c);

    ASSERT_EQ(1, r);
}

TEST_F(GBSqlTest, testInsertAssessment) {
    Assessment a;

    a.SetId("1");
    a.SetCourseId("MATH-217");
    a.SetTitle("Test1");
    a.SetDate(wxDateTime::Today());

    int r = sql->InsertAssessment(a);

    ASSERT_EQ(1, r);
}

TEST_F(GBSqlTest, testUpdateAssessment) {
     Assessment a;

    a.SetId("1");
    a.SetCourseId("MATH-217");
    a.SetTitle("Test1");
    a.SetDate(wxDateTime::Today());

    sql->InsertAssessment(a);

    a.SetTitle("Test2");

    int r = sql->UpdateAssessment(a);

    ASSERT_EQ(1, r);   
}

TEST_F(GBSqlTest, testDeleteAssessment) {
    Assessment a;

    a.SetId("1");
    a.SetCourseId("MATH-217");
    a.SetTitle("Test1");
    a.SetDate(wxDateTime::Today());

    sql->InsertAssessment(a);

    int r = sql->DeleteAssessment(a);

    ASSERT_EQ(1, r);
}

TEST_F(GBSqlTest, testSelectAssessments) {
    Assessment a;
    vector<Assessment*> aVec;

    a.SetId("1");
    a.SetCourseId("MATH-217");
    a.SetTitle("Test1");
    a.SetDate(wxDateTime::Today());

    sql->InsertAssessment(a);

    int r = sql->SelectAssessments(&aVec);

    ASSERT_EQ(1, r);
}
