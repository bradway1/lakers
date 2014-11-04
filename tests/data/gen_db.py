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

sid = 0

for x in range(len(courses)):
  c.execute("INSERT INTO courses VALUES (NULL, '" + courses[x] + "')") 
  cid = c.execute("SELECT id FROM courses WHERE title='" + courses[x] + "'").fetchone()
  for y in range(students[x]):
    name = random.randint(0, 1)
    c.execute("INSERT INTO students VALUES (NULL, '" + str(sid) + "', '" + names[name] + "', 'doe')")
    c.execute("INSERT INTO course_student VALUES (NULL, '" + str(sid) + "', '" + str(cid[0]) + "')")
    sid += 1
  s = c.execute("SELECT students.sid, first, last FROM students inner join course_student on students.sid=course_student.sid WHERE course_student.cid='" + str(cid[0]) + "'").fetchall()
  for z in range(assessments[x]):
    c.execute("INSERT INTO assessments VALUES (NULL, 'assessment" + str(z) + "', '" + str(cid[0]) + "')")
    aid = c.execute("SELECT id FROM assessments WHERE title='assessment" + str(z) + "'").fetchone()
    for u in range(len(s)): 
      grade = random.randint(0, 100)
      c.execute("INSERT INTO grades VALUES (NULL, '" + str(s[u][0]) + "', '" + str(cid[0]) + "', '" + str(aid[0]) + "', '" + str(grade) + "')")

conn.commit()

conn.close()
