CROSS		=
CC			= $(CROSS)gcc
CXX			= $(CROSS)g++
TARGET		= app#ledtank
CFLAGS		= -Wall -O0

OBJDIR		= .
SRCDIR		= .

SRCS		= $(shell find $(SRCDIR) -name "*.cpp" -or -name "*.c")
OBJS		= $(SRCS:%=$(OBJDIR)/%.o)

INCLUDES	= -I../VL53L0X_rasp/platform/inc
INCLUDES	+= -I../VL53L0X_1.0.2/Api/core/inc
LIBS		= -lwiringPi
#-lpthread -lpaho-mqtt3c
LIBS		+= -lVL53L0X_Rasp

.PHONY: all
all: $(OBJS) $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) -L../VL53L0X_rasp/bin -o $@ $(OBJS) $(LIBS)

$(OBJDIR)/%.c.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

$(OBJDIR)/%.cpp.o: $(SRCDIR)/%.cpp
	$(CXX) $(CFLAGS) $(INCLUDES) -o $@ -c $<

.PHONY: clean
clean:
	rm -rf $(TARGET) $(OBJS)
