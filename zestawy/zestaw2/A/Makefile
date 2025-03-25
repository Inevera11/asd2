CC=g++
CFLAGS=-Wall -std=c++14 -pedantic

NAME1=main
HFILES = hashset.h

EXEC1  = $(NAME1).x   
OBJS1  = $(NAME1).o   

DIR := $(notdir $(CURDIR))

%.o: %.cpp $(HFILES)
	$(CC) $(CFLAGS) -c $<

all: $(EXEC1)

$(EXEC1): $(OBJS1)
	$(CC) -o $@ $(CFLAGS) $^

clean:
	rm -f $(EXEC1) $(OBJS1)

tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz $(DIR))

# Uruchomienie programu
run: $(EXEC1)
	./$(EXEC1)


.PHONY: clean tar run