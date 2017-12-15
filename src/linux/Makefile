CFLAGS  := -I../../include -Wall
LDFLAGS := -L../../lib

ifndef RELEASE
  CFLAGS += -g
  LIBS   += -lefence
else
  CFLAGS += -O3
endif

SRC_FILES := $(wildcard *.c)                      # foo.c
OBJ_FILES := $(patsubst %.c,%.o,$(wildcard *.c))  # foo.c -> foo.o

all: $(OBJ_FILES) pffn

$(OBJ_FILES): %.o: %.c ../../lib/libpffn.a
	$(CC) $(CFLAGS) -c -o $@ $<

pffn: $(OBJ_FILES)
	$(CC) $(LDFLAGS) $(LIBS) -o $@ $(OBJ_FILES) ../../lib/libpffn.a

clean:
	rm -f $(OBJ_FILES)
	rm -f pffn

mrclean: clean
	rm -f *~

.PHONY: all run clean mrclean
