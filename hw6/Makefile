both:	mcc	ll	LinkedVersion.exe
	make run
mcc:	Assembler.cpp
	g++ Assembler.cpp -O3 -o mcc
	cp mcc masm_mrd
ll:	linker.cpp
	g++ linker.cpp -O3 -o ll
LinkedVersion.exe:	mcc	ll
	make -C build
	cp build/main.exe LinkedVersion.exe
SingleFile.exe:	mcc	ll	hw6.asm
	./mcc hw6.asm > SingleFile.exe
run:	LinkedVersion.exe
	./mic1 prom.dat LinkedVersion.exe 0 2048
clean:
	rm *.exe
	rm mcc
	rm ll
	rm masm_mrd
	make clean -C build
