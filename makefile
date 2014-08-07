CC=cc
CFLAGS=-c -Wall
LDFLAGS=
FLEX_SOURCE=lex.yy.c
SOURCES=$(FLEX_SOURCE)
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=ruby

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

$(FLEX_SOURCE): ruby.l
	flex ruby.l

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm *.o $(EXECUTABLE) $(FLEX_SOURCE)
