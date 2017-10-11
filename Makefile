CC=gcc
CFLAGS=-I.
OBJDIR=obj
SRCDIR=src
OUTDIR=bin

DEPS = $(addprefix $(SRCDIR)/, wall_stream.h)
# SRC = $(addprefix $(SRCDIR)/, )
OBJ = $(addprefix $(OBJDIR)/, wall_stream.o wall_stream_func.o)

	
wall_stream: $(OBJ)
	$(CC) -o $(OUTDIR)/$@ $^ $(CFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: clean
clean:
	rm $(OBJ)