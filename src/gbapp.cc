#include "gbapp.h"

#include "sql/gbsql.h"

IMPLEMENT_APP(GBApp)

bool GBApp::OnInit() {
    GBSql *sql = new GBSql();

    delete sql;

    return true;
}
