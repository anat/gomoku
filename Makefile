#############################################################################
# Makefile for building: Gomoku
# Generated by qmake (2.01a) (Qt 4.7.0) on: dim. juil. 24 16:11:27 2011
# Project:  Gomoku.pro
# Template: app
# Command: /usr/bin/qmake -spec /usr/share/qt4/mkspecs/linux-g++ CONFIG+=debug -o Makefile Gomoku.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_GUI_LIB -DQT_NETWORK_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -pipe -g -Wall -W -D_REENTRANT $(DEFINES)
CXXFLAGS      = -pipe -g -Wall -W -D_REENTRANT $(DEFINES)
INCPATH       = -I/usr/share/qt4/mkspecs/linux-g++ -I. -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtNetwork -I/usr/include/qt4/QtGui -I/usr/include/qt4 -Iinc -I. -I.
LINK          = g++
LFLAGS        = 
LIBS          = $(SUBLIBS)  -L/usr/lib -lQtGui -lQtNetwork -lQtCore -lpthread -lboost_thread
AR            = ar cqs
RANLIB        = 
QMAKE         = /usr/bin/qmake
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
STRIP         = strip
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = src/main.cpp \
		src/APlayer.cpp \
		src/Board.cpp \
		src/Game.cpp \
		src/HPlayer.cpp \
		src/mainwindow.cpp \
		src/Referee.cpp \
		src/Square.cpp \
		src/gridmanager.cpp \
		src/parameters.cpp \
		src/newgame.cpp \
		src/finalstate.cpp \
		src/open.cpp \
		src/BasicHeuristic.cpp \
		src/RefereeManager.cpp \
		src/BasicSearchCase.cpp \
		src/ThreeAlignChecker.cpp \
		src/remoteplayer.cpp moc_mainwindow.cpp \
		moc_Game.cpp \
		moc_parameters.cpp \
		moc_newgame.cpp \
		moc_finalstate.cpp \
		moc_open.cpp \
		qrc_texture.cpp
OBJECTS       = main.o \
		APlayer.o \
		Board.o \
		Game.o \
		HPlayer.o \
		mainwindow.o \
		Referee.o \
		Square.o \
		gridmanager.o \
		parameters.o \
		newgame.o \
		finalstate.o \
		open.o \
		BasicHeuristic.o \
		RefereeManager.o \
		BasicSearchCase.o \
		ThreeAlignChecker.o \
		remoteplayer.o \
		moc_mainwindow.o \
		moc_Game.o \
		moc_parameters.o \
		moc_newgame.o \
		moc_finalstate.o \
		moc_open.o \
		qrc_texture.o
DIST          = /usr/share/qt4/mkspecs/common/g++.conf \
		/usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/modules/qt_webkit_version.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/debug.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		Gomoku.pro
QMAKE_TARGET  = Gomoku
DESTDIR       = 
TARGET        = Gomoku

first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile $(TARGET)

$(TARGET): ui_mainwindow.h ui_parameters.h ui_newgame.h ui_finalstate.h ui_open.h $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: Gomoku.pro  /usr/share/qt4/mkspecs/linux-g++/qmake.conf /usr/share/qt4/mkspecs/common/g++.conf \
		/usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/modules/qt_webkit_version.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/debug.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		/usr/lib/libQtGui.prl \
		/usr/lib/libQtNetwork.prl \
		/usr/lib/libQtCore.prl
	$(QMAKE) -spec /usr/share/qt4/mkspecs/linux-g++ CONFIG+=debug -o Makefile Gomoku.pro
/usr/share/qt4/mkspecs/common/g++.conf:
/usr/share/qt4/mkspecs/common/unix.conf:
/usr/share/qt4/mkspecs/common/linux.conf:
/usr/share/qt4/mkspecs/qconfig.pri:
/usr/share/qt4/mkspecs/modules/qt_webkit_version.pri:
/usr/share/qt4/mkspecs/features/qt_functions.prf:
/usr/share/qt4/mkspecs/features/qt_config.prf:
/usr/share/qt4/mkspecs/features/exclusive_builds.prf:
/usr/share/qt4/mkspecs/features/default_pre.prf:
/usr/share/qt4/mkspecs/features/debug.prf:
/usr/share/qt4/mkspecs/features/default_post.prf:
/usr/share/qt4/mkspecs/features/warn_on.prf:
/usr/share/qt4/mkspecs/features/qt.prf:
/usr/share/qt4/mkspecs/features/unix/thread.prf:
/usr/share/qt4/mkspecs/features/moc.prf:
/usr/share/qt4/mkspecs/features/resources.prf:
/usr/share/qt4/mkspecs/features/uic.prf:
/usr/share/qt4/mkspecs/features/yacc.prf:
/usr/share/qt4/mkspecs/features/lex.prf:
/usr/share/qt4/mkspecs/features/include_source_dir.prf:
/usr/lib/libQtGui.prl:
/usr/lib/libQtNetwork.prl:
/usr/lib/libQtCore.prl:
qmake:  FORCE
	@$(QMAKE) -spec /usr/share/qt4/mkspecs/linux-g++ CONFIG+=debug -o Makefile Gomoku.pro

dist: 
	@$(CHK_DIR_EXISTS) .tmp/Gomoku1.0.0 || $(MKDIR) .tmp/Gomoku1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) .tmp/Gomoku1.0.0/ && $(COPY_FILE) --parents inc/mainwindow.hpp inc/Types.hpp inc/Square.hpp inc/Referee.hpp inc/HPlayer.hpp inc/gridmanager.hpp inc/Game.hpp inc/Board.hpp inc/APlayer.hpp inc/parameters.hpp inc/newgame.hpp inc/finalstate.hpp inc/open.hpp inc/PlayerAi.hpp inc/IHeuristic.hpp inc/BasicHeuristic.hpp inc/Singleton.hpp inc/RefereeManager.hpp inc/Coord.hpp inc/Array.hpp inc/ISearchCase.hpp inc/BasicSearchCase.hpp inc/ThreeAlignChecker.hpp src/remoteplayer.h .tmp/Gomoku1.0.0/ && $(COPY_FILE) --parents ressources/texture.qrc .tmp/Gomoku1.0.0/ && $(COPY_FILE) --parents src/main.cpp src/APlayer.cpp src/Board.cpp src/Game.cpp src/HPlayer.cpp src/mainwindow.cpp src/Referee.cpp src/Square.cpp src/gridmanager.cpp src/parameters.cpp src/newgame.cpp src/finalstate.cpp src/open.cpp src/BasicHeuristic.cpp src/RefereeManager.cpp src/BasicSearchCase.cpp src/ThreeAlignChecker.cpp src/remoteplayer.cpp .tmp/Gomoku1.0.0/ && $(COPY_FILE) --parents forms/mainwindow.ui forms/parameters.ui forms/newgame.ui forms/finalstate.ui forms/open.ui .tmp/Gomoku1.0.0/ && (cd `dirname .tmp/Gomoku1.0.0` && $(TAR) Gomoku1.0.0.tar Gomoku1.0.0 && $(COMPRESS) Gomoku1.0.0.tar) && $(MOVE) `dirname .tmp/Gomoku1.0.0`/Gomoku1.0.0.tar.gz . && $(DEL_FILE) -r .tmp/Gomoku1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


check: first

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all: moc_mainwindow.cpp moc_Game.cpp moc_parameters.cpp moc_newgame.cpp moc_finalstate.cpp moc_open.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_mainwindow.cpp moc_Game.cpp moc_parameters.cpp moc_newgame.cpp moc_finalstate.cpp moc_open.cpp
moc_mainwindow.cpp: inc/Singleton.hpp \
		inc/Game.hpp \
		inc/Referee.hpp \
		inc/Coord.hpp \
		inc/RefereeManager.hpp \
		inc/Array.hpp \
		inc/Square.hpp \
		inc/Types.hpp \
		inc/ThreeAlignChecker.hpp \
		inc/Board.hpp \
		inc/APlayer.hpp \
		inc/parameters.hpp \
		inc/newgame.hpp \
		inc/finalstate.hpp \
		inc/mainwindow.hpp
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) inc/mainwindow.hpp -o moc_mainwindow.cpp

moc_Game.cpp: inc/Referee.hpp \
		inc/Coord.hpp \
		inc/RefereeManager.hpp \
		inc/Array.hpp \
		inc/Singleton.hpp \
		inc/Square.hpp \
		inc/Types.hpp \
		inc/ThreeAlignChecker.hpp \
		inc/Board.hpp \
		inc/APlayer.hpp \
		inc/Game.hpp
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) inc/Game.hpp -o moc_Game.cpp

moc_parameters.cpp: inc/parameters.hpp
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) inc/parameters.hpp -o moc_parameters.cpp

moc_newgame.cpp: inc/Game.hpp \
		inc/Referee.hpp \
		inc/Coord.hpp \
		inc/RefereeManager.hpp \
		inc/Array.hpp \
		inc/Singleton.hpp \
		inc/Square.hpp \
		inc/Types.hpp \
		inc/ThreeAlignChecker.hpp \
		inc/Board.hpp \
		inc/APlayer.hpp \
		inc/newgame.hpp
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) inc/newgame.hpp -o moc_newgame.cpp

moc_finalstate.cpp: inc/finalstate.hpp
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) inc/finalstate.hpp -o moc_finalstate.cpp

moc_open.cpp: inc/open.hpp
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) inc/open.hpp -o moc_open.cpp

compiler_rcc_make_all: qrc_texture.cpp
compiler_rcc_clean:
	-$(DEL_FILE) qrc_texture.cpp
qrc_texture.cpp: ressources/texture.qrc \
		ressources/gazon.jpg \
		ressources/parquet.jpg \
		ressources/WhiteWin.png \
		ressources/BlackWin.png
	/usr/bin/rcc -name texture ressources/texture.qrc -o qrc_texture.cpp

compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all: ui_mainwindow.h ui_parameters.h ui_newgame.h ui_finalstate.h ui_open.h
compiler_uic_clean:
	-$(DEL_FILE) ui_mainwindow.h ui_parameters.h ui_newgame.h ui_finalstate.h ui_open.h
ui_mainwindow.h: forms/mainwindow.ui
	/usr/bin/uic-qt4 forms/mainwindow.ui -o ui_mainwindow.h

ui_parameters.h: forms/parameters.ui
	/usr/bin/uic-qt4 forms/parameters.ui -o ui_parameters.h

ui_newgame.h: forms/newgame.ui
	/usr/bin/uic-qt4 forms/newgame.ui -o ui_newgame.h

ui_finalstate.h: forms/finalstate.ui
	/usr/bin/uic-qt4 forms/finalstate.ui -o ui_finalstate.h

ui_open.h: forms/open.ui
	/usr/bin/uic-qt4 forms/open.ui -o ui_open.h

compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean compiler_rcc_clean compiler_uic_clean 

####### Compile

main.o: src/main.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o src/main.cpp

APlayer.o: src/APlayer.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o APlayer.o src/APlayer.cpp

Board.o: src/Board.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o Board.o src/Board.cpp

Game.o: src/Game.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o Game.o src/Game.cpp

HPlayer.o: src/HPlayer.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o HPlayer.o src/HPlayer.cpp

mainwindow.o: src/mainwindow.cpp ui_mainwindow.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o mainwindow.o src/mainwindow.cpp

Referee.o: src/Referee.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o Referee.o src/Referee.cpp

Square.o: src/Square.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o Square.o src/Square.cpp

gridmanager.o: src/gridmanager.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o gridmanager.o src/gridmanager.cpp

parameters.o: src/parameters.cpp ui_parameters.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o parameters.o src/parameters.cpp

newgame.o: src/newgame.cpp ui_newgame.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o newgame.o src/newgame.cpp

finalstate.o: src/finalstate.cpp ui_finalstate.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o finalstate.o src/finalstate.cpp

open.o: src/open.cpp ui_open.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o open.o src/open.cpp

BasicHeuristic.o: src/BasicHeuristic.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o BasicHeuristic.o src/BasicHeuristic.cpp

RefereeManager.o: src/RefereeManager.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o RefereeManager.o src/RefereeManager.cpp

BasicSearchCase.o: src/BasicSearchCase.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o BasicSearchCase.o src/BasicSearchCase.cpp

ThreeAlignChecker.o: src/ThreeAlignChecker.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o ThreeAlignChecker.o src/ThreeAlignChecker.cpp

remoteplayer.o: src/remoteplayer.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o remoteplayer.o src/remoteplayer.cpp

moc_mainwindow.o: moc_mainwindow.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_mainwindow.o moc_mainwindow.cpp

moc_Game.o: moc_Game.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_Game.o moc_Game.cpp

moc_parameters.o: moc_parameters.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_parameters.o moc_parameters.cpp

moc_newgame.o: moc_newgame.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_newgame.o moc_newgame.cpp

moc_finalstate.o: moc_finalstate.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_finalstate.o moc_finalstate.cpp

moc_open.o: moc_open.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_open.o moc_open.cpp

qrc_texture.o: qrc_texture.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o qrc_texture.o qrc_texture.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

