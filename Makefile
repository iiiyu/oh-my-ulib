ULIBINC	= include/
ULIBLIB = lib/

TARGET	= word2tree
OBJS	= word2tree.o

CC	?= gcc
CFLAGS	?= -c -O3 -g3 -W -Wall -pipe -DNDEBUG
LDFLAGS ?= -lulib

.c.o:
	make -C ulib/
	$(CC) -I $(ULIBINC) $(CFLAGS) $< -o $@

.PNONY: all clean remove_bak

all: $(TARGET)

clean:
	make -C ulib/ clean
	rm -rf $(TARGET) $(OBJS)
	rm -rf include/
	rm -rf lib/
	find . -name "*~" | xargs rm -f

remove_bak:
	find . -name "*~" | xargs rm -f

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) -L $(ULIBLIB) $(LDFLAGS)
