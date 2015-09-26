MAKE = make
CC = gcc
CXX = g++

##################
CFLAGS = -Wall -g
CXXFLAGS = $(CFLAGS)
LDFLAGS = -L/usr/lib/arm-linux-gnueabihf/ -lpng -lz

NAME = png

CSOURCE =
CPPSOURCE = test.cpp readpng.cpp format.cpp
#################

OBJS += $(patsubst %.cpp, %.o, $(filter %.cpp, $(CPPSOURCE)))
OBJS += $(patsubst $.c, %.o, $(filter %.c, $(CSOURCE)))

%.o : %.c
	$(CC) -c $(CFLAGS) -o $@ $<

%.o : %.cpp
	$(CXX) -c $(CXXFLAGS) -o $@ $<

default :
	$(MAKE) $(NAME)

all :
	$(MAKE) $(NAME)	

$(NAME) : $(OBJS)
	$(CXX) $(CFLAGS) -o $(NAME) $(OBJS) $(LDFLAGS)

clean :
	rm -rf *.o

veryclean : clean
	rm -rf $(NAME)

depend :
	$(CXX) -MM $(CFLAGS) $(CSOURCE) $(CPPSOURCE) > Makefile.dep

-include Makefile.dep

.PHONY: all clean default depend veryclean
