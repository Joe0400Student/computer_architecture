make_source:
	./masm_nr < hw5.asm > out.obj
masm_nr: mic1symasm_nand_rshift.o lex.yy.o
	gcc -o masm_nr mic1symasm_nand_rshift.o lex.yy.o
mic1symasm_nand_rshift.o:  mic1symasm_nand_rshift.c
	gcc -c -g mic1symasm_nand_rshift.c
lex.yy.o:  lex.yy.c
	gcc -c -g lex.yy.c
lex.yy.c: mic1symasm_nand_rshift.ll
	flex mic1symasm_nand_rshift.ll
compile_div:
	./masm_nr < a4_div_test.asm > out.obj
compile_mul:
	./masm_nr < a4_mult_test.asm > out.obj
compile_rsh:
	./masm_nr < a4_rshift_test.asm > out.obj
compile_source:
	./mcc microcode.mc > prom_new.dat
run_source:
	./mic1 prom_new.dat out.obj 0 2048
clean:
	rm lex.yy.o lex.yy.c mic1symasm_nand_rshift.o masm_nr
