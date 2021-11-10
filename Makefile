SRCDIR  := src
LIBDIR  := $(SRCDIR)/matrix
OBJDIR  := objs
OBJS    := $(addprefix $(OBJDIR)/,Matrix.o main.o)
BINDIR  := bin
BIN     := $(BINDIR)/main

.PHONY: clean

all: $(BIN)

$(BIN): $(OBJS)
	g++ -o $(BIN) $^

$(OBJDIR)/Matrix.o: $(LIBDIR)/Matrix.cpp $(LIBDIR)/Matrix.h
	g++ -Wall -std=c++11 -I $(LIBDIR) -o $@ -c $<

$(OBJDIR)/main.o: $(SRCDIR)/main.cpp $(LIBDIR)/Matrix.h
	g++ -Wall -std=c++11 -I $(LIBDIR) -o $@ -c $<

$(BIN): | $(BINDIR)

$(BINDIR):
	mkdir $(BINDIR)

$(OBJS): | $(OBJDIR)

$(OBJDIR):
	mkdir  $(OBJDIR)

clean:
	rm -R $(OBJDIR) $(BINDIR)
