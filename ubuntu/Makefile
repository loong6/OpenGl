#Makefile更多hack写法 
#blog.csdn.net/ruglcc/article/details/7814546/
VPATH =src/
LIBS = -lGL -lGLU -lglut -std=c++11
objs = init.o init2.o trangle.o polyLine.o chessBoard.o interactive.o \
menu.o viewPortTest.o

all:$(objs)
	g++ -o bin/init init.o $(LIBS)
	g++ -o bin/init2 init2.o	$(LIBS)
	g++ -o bin/trangle trangle.o	$(LIBS) -lm
	g++ -o bin/polyLine polyLine.o $(LIBS)
	g++ -o bin/chessBoard chessBoard.o $(LIBS)
	g++ -o bin/interactive interactive.o $(LIBS)
	g++ -o bin/menu menu.o $(LIBS)
	g++ -o bin/viewPortTest viewPortTest.o $(LIBS)
	make clean

#编译init
init:init.o
	g++ init.o -o init $(LIBS)
# 隐晦规则写法 会自动扩展成 无其它依赖文件时可忽略不写
# init.o:init.cpp
# 	g++ -c init.cpp
# init.o:

#编译init2
init2:init2.o
	g++  init2.o -o bin/init2 $(LIBS)
# init2.o : 

#编译trangle
trangle:trangle.o
	g++ trangle.o -o bin/trangle $(LIBS) -lm

#编译polyLine
polyLine:polyLine.o
	g++  polyLine.o -o bin/polyLine $(LIBS)

#编译chessBoard
chessBoard:chessBoard.o
	g++  chessBoard.o -o bin/chessBoard $(LIBS)

#编译interactive
interactive:interactive.o
	g++  interactive.o -o bin/interactive $(LIBS)


#编译menu
menu:menu.o
	g++  menu.o -o bin/menu $(LIBS)




#编译viewPortTest
viewPortTest:viewPortTest.o
	g++  viewPortTest.o -o bin/viewPortTest $(LIBS)

.PHONY:clean

clean:
	-rm *.o