import os
import random
import sqlite3

tables = [ 
    "CREATE TABLE IF NOT EXISTS students (\
        id integer primary key, \
        sid text not null unique, \
        first text not null, \
        last text not null)",
    "CREATE TABLE IF NOT EXISTS courses (\
        id integer primary key, \
        title text not null)",
    "CREATE TABLE IF NOT EXISTS assessments (\
        id integer primary key, \
        title text not null, \
        cid text not null)",
    "CREATE TABLE IF NOT EXISTS grades (\
        id integer primary key, \
        sid text not null, \
        cid text not null, \
        aid text not null, \
        value text not null)",
    "CREATE TABLE IF NOT EXISTS course_student (\
        id integer primary key, \
        sid text not null, \
        cid text not null)",
    ]
students = [ 32, 25 ]
courses = [ "MATH-217", "CSCI-217" ]
assessments = [ 20, 32 ]
names = [ "John", "Jane" ]

if os.path.exists('gb.db'):
  os.remove('gb.db')

conn = sqlite3.connect('gb.db')

c = conn.cursor()

for table in tables:
  c.execute(table)

for x in range(len(courses)):
  c.execute("INSERT INTO courses VALUES (NULL, '" + str(courses[x]) + "')")
  cid = c.execute("SELECT id FROM courses WHERE title='" + str(courses[x]) + "'").fetchone()[0]
  for y in range(assessments[x]):
    c.execute("INSERT INTO assessments VALUES (NULL,'assessment" + str(y) + "','" + str(cid) + "')")
  for y in range(students[x]):
    actual_sid = random.randint(900000, 1000000)
    name = random.randint(0, 1)
    c.execute("INSERT INTO students VALUES (NULL,'" + str(actual_sid) + "','" + str(names[name]) + "','Doe')")
    sid = c.execute("SELECT id FROM students WHERE sid='" + str(actual_sid) + "'").fetchone()[0]
    c.execute("INSERT INTO course_student VALUES (NULL,'" + str(sid) + "','" + str(cid) + "')")
    for z in range(assessments[x]):
      value = random.randint(0, 100)
      aid = c.execute("SELECT id FROM assessments WHERE title='assessment" + str(z) + "' AND cid='" + str(cid) + "'").fetchone()[0]
      c.execute("INSERT INTO grades VALUES (NULL,'" + str(sid) + "','" + str(cid) + "','" + str(aid) + "','" + str(value) + "')")

conn.commit()

conn.close()
