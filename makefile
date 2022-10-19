OBJDIR = ./ObjDir
SRCDIR = ./SrcDir

NetConnSocketObj = $(OBJDIR)/NetConnSocketObj.o
NetConnSocketDep = $(SRCDIR)/NetConnSocket.cpp

SenderObj = $(OBJDIR)/SenderObj.o
SenderDep = $(SRCDIR)/SenderSocket.cpp

ReceiverObj = $(OBJDIR)/ReceiverObj.o
ReceiverDep = $(SRCDIR)/ReceiverSocket.cpp

MainObj = $(OBJDIR)/main.o
MainDep = ./main.cpp


COMPILE = g++ -c
executable = main.exe

all : $(executable)


$(executable): $(NetConnSocketObj) $(SenderObj) $(ReceiverObj) $(MainObj)
	@echo linking object files
	@g++ -o $(executable) $(NetConnSocketObj) $(ReceiverObj) $(SenderObj) $(MainObj)

$(NetConnSocketObj):
	@echo Compiling NetConnSocket
	@$(COMPILE) $(NetConnSocketDep) -o $(NetConnSocketObj) -std=c++11

$(SenderObj):
	@echo Compiling sender object
	@$(COMPILE) $(SenderDep) -o $(SenderObj) -std=c++11

$(ReceiverObj):
	@echo Compiling receiver object
	@$(COMPILE) $(ReceiverDep) -o $(ReceiverObj) -std=c++11

$(MainObj):
	@echo Compiling main file
	@$(COMPILE) $(MainDep) -o $(MainObj) -std=c++11

clean:
	@echo cleaning all
	@rm -f $(MainObj) $(SenderObj) $(ReceiverObj) $(NetConnSocketObj) $(executable)