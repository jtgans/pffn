CFLAGS  := -I../include
LDFLAGS :=

ifndef RELEASE
  CFLAGS += -g
  LIBS   += -lefence
else
  CFLAGS += -O3
endif

SRC_FILES := $(wildcard *.c)
OBJ_FILES := $(shell echo $(SRC_FILES) |sed 's/\.c/.o/g')

all: libpffn.a

libpffn.a: libpffn.a($(OBJ_FILES))
	ranlib libpffn.a

clean:
	rm -f libpffn.a
	rm -f $(OBJ_FILES)

mrclean:
	rm -f *~

.PHONY: all
