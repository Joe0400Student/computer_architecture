LL = ../../ll
Names := $(wildcard:../source/*.asm)
Deps := $(Names:../sources/%.asm=%.o)

../main.exe: $(DEPS)
	$(LL) main.o data.o addint.o enable.o rbyswt.o write_char.o write_string.o \
	data_modifier.o deref.o get_input_char.o readint.o write_int.o xbsywt.o > ../main.exe
$(Deps): update
	echo "updating" 
update:
	make -C ../source
clean:
	rm *.o

