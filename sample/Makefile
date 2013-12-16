include ../makefile.env
WORKROOT=../../
CC=g++

TARGET=sample
OBJS=sample.o

INCS=\
	-I$(MYLOG_PATH)include \
	-I$(MYCONF_PATH)include

LIBS=\
	-L$(MYLOG_PATH)lib \
	-L$(MYCONF_PATH)lib \
	-Wl,-whole-archive -lmylog -Wl,-no-whole-archive \
	-Wl,-whole-archive -lmyconf -Wl,-no-whole-archive \
	-lpthread

CPPFLAGS=$(INCS)  -Wall -W -pipe -Wno-unused-parameter -g -O2
LDFLAGS=$(LIBS) -O2 

.PHONY : all

all: $(TARGET)

$(TARGET) : $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

$(OBJS) :%.o : %.cpp 
	$(CC) -c $(CPPFLAGS) $< 

.PHONY : clean
clean:
	rm -rf $(OBJS) $(TARGET)
