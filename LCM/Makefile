OBJS	= Build/test.o Build/ws2812.o Build/io_ws2812.o Build/tasktest.o Build/power.o Build/led.o Build/flag_bit.o
SOURCE	= Code/Test/test.c
HEADER	= 
OUT	= Build/test.exe
CC	 = gcc
FLAGS	 = -g -c -Wall -D test
LFLAGS	 = 
INC=-ICode/App -ICode/Test/fakelibs
all: buildall

buildall: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

Build/test.o: 
	$(CC) $(FLAGS) $(INC) $(SOURCE) -o Build/test.o

Build/tasktest.o: 
	$(CC) $(FLAGS) $(INC) Code/Test/tasktest.c -o Build/tasktest.o

Build/ws2812.o: 
	$(CC) $(FLAGS) $(INC) Code/App/ws2812.c -o Build/ws2812.o

Build/flag_bit.o: 
	$(CC) $(FLAGS) $(INC) Code/App/flag_bit.c -o Build/flag_bit.o

Build/io_ws2812.o:
	$(CC) $(FLAGS) $(INC) Code/Test/fakelibs/io_ws2812.c -o Build/io_ws2812.o

Build/power.o:
	$(CC) $(FLAGS) $(INC) Code/Test/fakelibs/power.c -o Build/power.o

Build/led.o:
	$(CC) $(FLAGS) $(INC) Code/Test/fakelibs/led.c -o Build/led.o

clean:
	rm -f $(OBJS) $(OUT)