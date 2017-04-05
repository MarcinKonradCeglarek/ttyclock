#SHELL = /bin/sh

NAME = ttyclock
VERSION = 0.3.2
CC = gcc
NCURS_CFLAGS = -lncurses -Wall
CFLAGS = -c -Wall

# Where the executables should be put
SRCDIR = src/
DESTDIR = /usr/local/bin

# Where the man page should be put
MANDIR = /usr/local/man/man6

OBJECTS = $(SRCDIR)main.o \
	  $(SRCDIR)mod_commandline.o \
	  $(SRCDIR)mod_output.o \
	  $(SRCDIR)languages.o \
	  $(SRCDIR)lang_bcd.o \
	  $(SRCDIR)lang_digital.o \
	  $(SRCDIR)lang_binary.o \
	  $(SRCDIR)mod_time.o \
	  $(SRCDIR)mod_curses.o \
	  $(SRCDIR)mod_colors.o



### It's default - compile and install
all: $(NAME)

### clean up src dir
.PHONY: clean
clean:
	-rm -f $(SRCDIR)*.o 
	-rm -f $(NAME)


### pack up the whole directory
.PHONY: pack
pack:
	@echo "Cleaining instalation..."
	make clean
	@echo "Creating package..."
	tar -czf ../$(NAME)-$(VERSION).tar.gz .
#	echo "Removing src directory..."
#	#rm -fr 

.PHONY: install
install: $(NAME)
	cp $(NAME) $(DESTDIR)

.PHONY: uninstall
uninstall:
	@echo "Removing $(DESTDIR)/$(NAME)..."
	rm $(DESTDIR)/$(NAME)


$(NAME): $(OBJECTS)
	$(CC) -lncurses $(OBJECTS) -o $(NAME)


#compiling each module:
$(SRCDIR)main.o: $(SRCDIR)main.c $(SRCDIR)main.h $(SRCDIR)defs.h
	$(CC) $(CFLAGS) -o $(SRCDIR)main.o $(SRCDIR)main.c

$(SRCDIR)mod_commandline.o: $(SRCDIR)mod_commandline.c $(SRCDIR)mod_commandline.h $(SRCDIR)defs.h
	$(CC) $(CFLAGS) -o $(SRCDIR)mod_commandline.o $(SRCDIR)mod_commandline.c

$(SRCDIR)mod_output.o: $(SRCDIR)mod_output.c $(SRCDIR)mod_output.h $(SRCDIR)defs.h
	$(CC) $(CFLAGS) -o $(SRCDIR)mod_output.o $(SRCDIR)mod_output.c

$(SRCDIR)mod_time.o: $(SRCDIR)mod_time.c $(SRCDIR)mod_time.h $(SRCDIR)defs.h
	$(CC) $(CFLAGS) -o $(SRCDIR)mod_time.o $(SRCDIR)mod_time.c

$(SRCDIR)mod_colors.o: $(SRCDIR)mod_colors.c $(SRCDIR)mod_colors.h $(SRCDIR)defs.h
	$(CC) $(CFLAGS) -o $(SRCDIR)mod_colors.o $(SRCDIR)mod_colors.c

$(SRCDIR)mod_curses.o: $(SRCDIR)mod_curses.c $(SRCDIR)mod_curses.h
	$(CC) $(CFLAGS) -o $(SRCDIR)mod_curses.o $(SRCDIR)mod_curses.c

$(SRCDIR)languages.o: $(SRCDIR)languages.c $(SRCDIR)languages.h
	$(CC) $(CFLAGS) -o $(SRCDIR)languages.o $(SRCDIR)languages.c

$(SRCDIR)lang_bcd.o: $(SRCDIR)lang_bcd.c $(SRCDIR)lang_bcd.h $(SRCDIR)defs.h
	$(CC) $(CFLAGS) -o $(SRCDIR)lang_bcd.o $(SRCDIR)lang_bcd.c

$(SRCDIR)lang_binary.o: $(SRCDIR)lang_binary.c $(SRCDIR)lang_binary.h $(SRCDIR)defs.h
	$(CC) $(CFLAGS) -o $(SRCDIR)lang_binary.o $(SRCDIR)lang_binary.c

$(SRCDIR)lang_digital.o: $(SRCDIR)lang_digital.c $(SRCDIR)lang_digital.h $(SRCDIR)defs.h
	$(CC) $(CFLAGS) -o $(SRCDIR)lang_digital.o $(SRCDIR)lang_digital.c
