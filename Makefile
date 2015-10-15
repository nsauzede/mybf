TARGET=bf

CFLAGS=-Wall -Werror
CFLAGS+=-g -O0 -fno-omit-frame-pointer

all:	$(TARGET)

check:	bf
	./$<

clean:
	$(RM) $(TARGET)
