#编译器
CC = g++

#当前编译路径
APP_DIR = .

#操作系统位数（32 or 64）
PLATFORM=$(shell uname -p)
ifeq ("$(PLATFORM)", "x86_64")
	TARGET = zigbeeadapter
else
	TARGET = zigbeeadapter_32
endif

#include 头文件路径
#INC_DIR = $(APP_DIR)/include
#vpath %.h $(INC)
#include $($(INC_DIR)/*.h)
#src 源文件路径
#SRC_DIR = $(APP_DIR)/src
#vpath %.cpp $(SRC_DIR)
#vpath %.o $(SRC_DIR)
#CFLAGS 编译选项
#LIBS =
CFLAGS = -w -W -Wall

#编译版本是DEBUG or RELEASE
ACTION = release 

ifeq ("$(ACTION)", "release")
	CFLAGS += -O2
else
	CFLAGS += -g
endif

#所有*.cpp源文件
APP_SRCS := $(wildcard $(APP_DIR)/*.cpp)

#所有*.o目标文件
APP_OBJS := $(APP_SRCS:.cpp=.o)

$(TARGET):$(APP_OBJS)
#	@echo $(APP_SRCS)
#	@echo $(APP_OBJS)
	$(CC) $(CFLAGS)  $^ -o $@ -lpthread -levent
clean:
	rm -f $(APP_DIR)/*.o $(APP_DIR)/$(TARGET)
	
