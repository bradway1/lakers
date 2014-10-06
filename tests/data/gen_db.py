import os
import random
import sqlite3

os.remove("build/gb.db")

conn = sqlite3.connect("build/gb.db")

c = conn.cursor()

c.execute("CREATE TABLE IF NOT EXISTS courses (\
    cid   TEXT  not null, \
    title TEXT  not null, \
    start TEXT  not null, \
    end   TEXT  not null, \
    primary key(cid))")

c.execute("CREATE TABLE IF NOT EXISTS students (\
    sid   TEXT  not null, \
    first TEXT  not null, \
    last  TEXT  not null, \
    primary key(sid))")

c.execute("CREATE TABLE IF NOT EXISTS sc_relation (\
    id    INTEGER   PRIMARY KEY AUTOINCREMENT, \
    sid   TEXT      not null, \
    cid   TEXT      not null)")

c.execute("CREATE TABLE IF NOT EXISTS assessments (\
    aid   TEXT  not null, \
    cid   TEXT  not null, \
    title TEXT  not null, \
    date  TEXT  not null, \
    type  TEXT  not null, \
    primary key(aid))")

conn.commit()

courses = ["MATH-217", "CSCI-580"]

for x in range(0, 2):
  c.execute("INSERT INTO courses (cid, title, start, end) \
      VALUES ('" + str(x) + "', '" + courses[x] + "', '10/5/14', '10/5/14')")

for x in range(0, 50):
  c.execute("INSERT INTO students (sid, first, last) \
      VALUES ('" + str(x) + "', 'john', 'doe" + str(x) + "')")

  course = random.randint(1, 100)

  c.execute("INSERT INTO sc_relation (sid, cid) \
      VALUES ('" + str(x) + "', '" + str(course % 2) + "')")

conn.commit()

conn.close()
