vpath %.cpp src
vpath %.o build

OBJ = gbapp.o

BUILD = debug

BUILD_DIR = build

BIN_NAME = gbapp.exe

WX_VER = 3.0.1
WX_DIR = lib\wxwidgets-$(WX_VER)
WX_MAKE_DIR = $(WX_DIR)\build\msw
WX_MAKE = makefile.gcc

CPPFLAGS := -Iinclude	\
			-I$(WX_DIR)\include \
			-I$(WX_DIR)\lib\gcc_lib\mswud

LDFLAGS := -L$(WX_DIR)\lib\gcc_lib

LDLIBS := -lwxmsw30ud_core -lwxbase30ud -luuid -lole32 -lcomctl32 -lgdi32	\
		  -lwxpngd -lwxzlibd -loleaut32 -lcomdlg32 -lwinspool

OUTPUT_OPTION = -o $(BUILD_DIR)\$@

build: setup libs gbapp ;

release: BUILD = release
release: build ;

run:
	$(BUILD_DIR)\$(BIN_NAME)

clean:
	del /Q build\*

deepclean: clean
	$(MAKE) -C $(WX_MAKE_DIR) -f $(WX_MAKE) clean

libs:
	$(MAKE) -C $(WX_MAKE_DIR) -f $(WX_MAKE) BUILD=$(BUILD)

setup:
	if not exist $(WX_DIR). ( lib\7za.exe x lib\wxwidgets-3.0.1.7z. )
	
gbapp: $(OBJ)
	$(CXX) $(LDFLAGS) $^ $(LDLIBS) -o $(BUILD_DIR)\$(BIN_NAME)
