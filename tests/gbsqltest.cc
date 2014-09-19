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
