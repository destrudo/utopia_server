#-I/usr/include/libbson-1.0 -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -I/usr/include/libmongoc-1.0 -lbson-1.0 -lmongoc-1.0

CC = g++
PROG = utopia_server
SOURCES = $(PROG).cpp mongoose/mongoose.c
#CFLAGS = -W -Wall -Imongoose/ $(CFLAGS_EXTRA)
CFLAGS = -Imongoose/

ifeq ($(SSL), openssl)
	CFLAGS += -DMG_ENABLE_SSL -lssl -lcrypto -lcrypto
else ifeq ($(SSL), krypton)
	CFLAGS += -DMG_ENABLE_SSL ../../../krypton/krypton.c
endif

ifeq ($(JS), yes)
	V7_PATH = ../../deps/v7
	CFLAGS_EXTRA += -DMG_ENABLE_JAVASCRIPT -I $(V7_PATH) $(V7_PATH)/v7.c
endif

all: $(PROG)

utopia_rest.o: utopia_rest.cpp
	$(CC) -g -o utopia_rest.o -c utopia_rest.cpp $(CFLAGS)

$(PROG): $(SOURCES) utopia_rest.o
	$(CC) $(SOURCES) -o $@ $(CFLAGS) utopia_rest.o -lpthread -pthread

clean:
	rm -rf *.gc* *.dSYM *.exe *.obj *.o a.out $(PROG)
