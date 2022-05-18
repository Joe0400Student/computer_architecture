CC = ../../mcc
SOURCES := $(wildcard *.asm)
OBJECTS := $(SOURCES:%.asm=../bin/%.o)

main:	$(OBJECTS)

../bin/%.o:	%.asm
	$(CC) -o $< > $@
