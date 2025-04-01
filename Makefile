TARGET  = libucgui
SRC_C   = $(shell find GUI* -name "*.c")
OBJ_C   = $(patsubst %.c, %.o, $(SRC_C))
SRCS    = $(SRC_C) $(SRC_C)
OBJS    = $(OBJ_C)
CFLAGS += -O3
CFLAGS += -DUSE_SDL
CFLAGS += -I./GUI_X
CFLAGS += -I./GUI/WM
CFLAGS += -I./GUI/Core
CFLAGS += -I./GUI/Widget
CFLAGS += -I/usr/local/include/SDL
LDFLAGS = -lSDL

.PHONY: all
all: $(TARGET).a

$(TARGET).a : $(OBJS)
	ar crv $(TARGET).a $(OBJS)

%.o : %.c
	$(CC) -c $(CFLAGS) $< -o  $@

.PHONY: clean
clean:
	rm -rf $(TARGET) *.a
	find . -name "*.[od]" | xargs rm -rf
