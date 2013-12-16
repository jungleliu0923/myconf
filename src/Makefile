include ../makefile.env
WORKROOT=../../
CC=g++
TARGET=libmyconf.a
OBJS=myconf.o

INCS=\
	-I$(MYLOG_PATH)include

LIBS=\
	-L$(MYLOG_PATH)lib \
	-Wl,-whole-archive -lmylog -Wl,-no-whole-archive \
	-lpthread

CPPFLAGS=$(INCS)  -Wall -W -pipe -Wno-unused-parameter -g -O2
LDFLAGS=$(LIBS) -O2 

.PHONY : all

all: $(TARGET)
	mkdir -p ../output/include
	cp *h ../output/include
	mkdir -p ../output/lib
	cp *a ../output/lib

$(TARGET) : $(OBJS)
	ar -r $(TARGET) $(OBJS)

$(OBJS) :%.o : %.cpp 
	$(CC) -c $(CPPFLAGS) $< 

.PHONY : clean
clean:
	rm -rf $(OBJS) $(TARGET)
