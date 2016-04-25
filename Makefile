MAKE = make
CC = gcc
CXX = g++

##################
CFLAGS = -Wall -g -O3
CXXFLAGS = $(CFLAGS)
LDFLAGS = -L/usr/lib/arm-linux-gnueabihf/ -lpng -lz

NAME = png

CSOURCE =
CPPSOURCE = test.cpp readpng.cpp circlesegment.cpp searcher.cpp rgbimage.cpp labimage.cpp bitimage.cpp shape.cpp medianfilter.cpp writepng.cpp labeledimage.cpp

IMAGE = pngs/scannedtest.png
#################

OBJS += $(patsubst %.cpp, %.o, $(filter %.cpp, $(CPPSOURCE)))
OBJS += $(patsubst $.c, %.o, $(filter %.c, $(CSOURCE)))

%.o : %.c
	$(CC) -c $(CFLAGS) -o $@ $<

%.o : %.cpp
	$(CXX) -c $(CXXFLAGS) -o $@ $<

default : $(NAME)
	$(MAKE) $(NAME)
	./$(NAME) $(IMAGE)
	gpicview debugpng/after_scaling.png

r :
	reset
	$(MAKE) $(NAME)
	./$(NAME) $(IMAGE)
	gpicview debugpng/after_scaling.png

compile : 
	$(MAKE) $(NAME)

run :
	./$(NAME) $(IMAGE)

#all :
#	$(MAKE) $(NAME)	

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
