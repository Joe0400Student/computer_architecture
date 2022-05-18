Email:	joseph_Scannell@student.uml.edu
Name:	Joseph Scannell
Grade:	90%

I believe I should get a 90% as i remade the compiler so that it could make an unlinked obj
files, a linker that is capable of linking files, and rewrote the previous assignment so
that it used normal returns

BTW
the name of the executable is called LinkedVersion.exe

ALSO
the directory structure is made differently so that the files are more organized
the directory structure is this

hw6
|\
| \ Makefile, readme, Assembler.cpp , Linker.cpp (mcc), (mic1), (ll), instruction_booklet.json
|  \----------------------------------------------
|
|\
  \
   \ build
    \__________________________________________
    |\
    | \ Makefile instruction_booklet.json
    |  \---------------------------------
    |\  
    | \ sources (source .asm files for individual linked versions), Makefile
    |  \________________________________
    \
     \  bin (compiled object files), Makefile
      \_________________________________



This compiler I wrote works significantly different than masm, as this one uses something
called an instruction_booklet,

an instruction booklet is a json that contains a list of classes that have
{
	"mnem": a Mnemnomic name
	"length": the length of the operand, 0 if no operand
	"binary": what binary to substitute for the mnemnomic name
}

These construct a Instruction object which constructs its own regular expression, which
allows it to be quickly extended to add more instructions whatever you want

The linker is also works slightly differently than other methods. This allows it more
flexability. I defined names F U H Q, which stand for Full, Universal, Half, Quarter(6)
this allows it to replace the addresses used in all the different instructions without
figuring out the instruction that is linnked to, all it knows is the last however many
bits is to be replaced.

I am going to continue working on the compiler, as i am going to add sensical errors to 
compiler, and make the compiler only compile non executable elfs, so that the linker always
resolved the linked values.


