#include "gtest/gtest.h"

#include "sql/gbsql.h"
#include "data/course.h"

#include <wx/filefn.h>

class GBSqlTest : public ::testing::Test {
    protected:
        GBSql sql;

        virtual void TearDown() {
            sql.Close();
            
            if (wxFileExists("gb.db")) {
                wxRemoveFile("gb.db");
            }
        }
};

TEST_F(GBSqlTest, testAddCourse) {
    Course c;

    c.SetId("1");
    c.SetTitle("MATH-217");
    c.SetStart(wxDateTime::Today());
    c.SetEnd(wxDateTime::Today());

    int r = sql.InsertCourse(c);

    ASSERT_EQ(1, r);
}
