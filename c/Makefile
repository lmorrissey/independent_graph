
empty =

CXX = g++

CXXFLAGS = -Wall -Wextra -Werror -std=c++11 -Ic:/cygwin64/usr/include

DEPENDSFLAGS = -MM -MF

LDFLAGS =

LIBS = -Lc:/cygwin64/lib

RM = rm -f

EXEC = graph.exe

EXEC_OBJS_GRAPH = \
	main.o  \
	$(empty)

SRCS_CPP =          \
	main.cpp \
	graph.h \
	$(empty)

OBJS_CPP = $(SRCS_CPP:.cpp=.o)

all : $(EXEC)

clean :
	$(RM) $(EXEC)
	$(RM) $(EXEC_OBJS_CLIENT)
	$(RM) $(EXEC_OBJS_SERVER)
	$(RM) 00-depends-*.mk

graph.exe : $(EXEC_OBJS_GRAPH)

$(EXEC):
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^ $(LIBS)

$(OBJS_CPP) :
	$(CXX) $(CXXFLAGS) $(@:.o=.cpp) $(DEPENDSFLAGS) 00-depends-$(@:.o=.mk)
	$(CXX) $(CXXFLAGS) -c -o $@ $(@:.o=.cpp)

include *.mk
