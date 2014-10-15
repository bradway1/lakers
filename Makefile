vpath %.cc src:src\data:src\sql:tests:src\gui

OBJ = gbframe.o assessment.o student.o course.o gbsql.o gbapp.o 
TEST_OBJ = gbsqltest.o gbtest.o

BUILD = debug

BUILD_DIR = build

OUTPUT_OBJ = $(addprefix $(BUILD_DIR)\, $(OBJ))

APP_NAME = gbapp.exe

WX_VER = 3.0.1
WX_DIR = lib\wxwidgets-$(WX_VER)
WX_MAKE_DIR = $(WX_DIR)\build\msw
WX_MAKE = makefile.gcc
WX_ARCH = wxwidgets-$(WX_VER).7z

WX_SQL_VER = 3.1.1
WX_SQL_DIR = lib\wxsqlite3-$(WX_SQL_VER)
WX_SQL_MAKE_DIR = $(WX_SQL_DIR)\build30
WX_SQL_MAKE = makefile.gcc
WX_SQL_ARCH = wxsqlite3-$(WX_SQL_VER).7z

SQL_DIR = $(WX_SQL_DIR)\sqlite3

GTEST_VER = 1.7.0
GTEST_DIR = lib\gtest-$(GTEST_VER)
GTEST_ARCH = gtest-$(GTEST_VER).7z

ARCH_TOOL = tools\7za.exe
SQL_TOOL = tools\sqlite3.exe

CPPFLAGS := -Iinclude \
						-Iinclude\data \
						-Iinclude\sql \
					-I$(WX_DIR)\include \
					-I$(WX_DIR)\lib\gcc_lib\mswud \
					-I$(WX_SQL_DIR)\include \
					-DBUILD=$(BUILD)

LDFLAGS := 	-L$(SQL_DIR)\lib \
			-L$(WX_SQL_DIR)\lib\gcc_lib	\
			-L$(WX_DIR)\lib\gcc_lib \

LDLIBS :=	-lwxcode_msw30ud_wxsqlite3 -lsqlite3 -lwxmsw30ud_adv -lwxmsw30ud_core \
			-lwxbase30ud -luuid -lole32 -loleaut32 -lwxregexud -lcomctl32 \
			-lgdi32 -lwxpngd -lwxzlibd -lcomdlg32 -lwinspool 

OUTPUT_OPTION = -o $(BUILD_DIR)\$@

build: setup gbapp ;

release: BUILD=release
release: build

run: build
	$(BUILD_DIR)\$(APP_NAME)

test: CPPFLAGS += -I$(GTEST_DIR)\include 
test: setup build_test
	
build_test: $(OBJ) $(TEST_OBJ)
	$(CXX) $(LDFLAGS) -L$(GTEST_DIR)\make $(addprefix $(BUILD_DIR)\, $^) \
		$(LDLIBS) -lgtest -o $(BUILD_DIR)\test.exe
	$(BUILD_DIR)\test.exe

setup: wxwidgets wxsqlite3 gtest

dummy:
	$(SQL_TOOL) build\gb.db < tests\data\gb.sql

wxwidgets:
ifeq (,$(wildcard $(WX_DIR)))
	$(ARCH_TOOL) x -olib lib\$(WX_ARCH)
	$(MAKE) -C $(WX_MAKE_DIR) -f $(WX_MAKE) BUILD=$(BUILD)
endif

wxsqlite3:
ifeq (,$(wildcard $(WX_SQL_DIR)))
	$(ARCH_TOOL) x -olib lib\$(WX_SQL_ARCH)
	$(MAKE) -C $(SQL_DIR)
	$(MAKE) -C $(WX_SQL_MAKE_DIR) -f $(WX_SQL_MAKE) WXWIN=$(CURDIR)\$(WX_DIR)
endif

gtest:
ifeq (,$(wildcard $(GTEST_DIR)))
	$(ARCH_TOOL) x -olib lib\$(GTEST_ARCH)
	$(MAKE) -C $(GTEST_DIR)\make gtest.a
	copy $(GTEST_DIR)\make\gtest.a $(GTEST_DIR)\make\libgtest.a
endif

gbapp: $(OBJ)
	$(CXX) $(LDFLAGS) $(OUTPUT_OBJ) $(LDLIBS) -o $(BUILD_DIR)\$(APP_NAME)
