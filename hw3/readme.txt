name: Joseph Scannell
email: joseph_scannell@student.uml.edu

The purpose of the assignment was to first a.) figure out how to use the mic1 assembler and simulator.
This was simple. However the second more important thing that the assignment was for, was to understand
the microarchitecture of the mic1 architecture. This was complicated as it only had ACC (Accumulator)
and (SP) Stack Pointer available to use. We had to figure out how to use the microarch to make a fib
function.

This assignment was complex. I believe i deserve a 100% on this assignment, as it works as intended.
I had to use the stack to implement this by pushing the results of fib onto the stack and 
looking at it.

the 25th number in fib(25) is going to overflow the integer limit, that is to be expected. Due to
that it overflows the integer limit and rolls over to ~9000.

(I did this so i can make a pseudo asm to make the mic1 off of)

(Psuedo ASM) (makes it more readable)
set acc, val	       // set accumultor to n
if acc == 0 fib(0)     // if acc is 0 then return 0
sub acc, 1	       // decrement acc
if val == 0 fib(1)     // if acc is 0 then return 1
push acc               // add acc to new stack frame for call
fib(acc)               // call acc
push(acc)              // push fib return
peek(acc, 1)           // 1 before stack pointer to look at previous
sub acc, 1             // decrement n by 1
push(acc)              // pushes n onto stack
fib(acc)	       // calls accumulator
add_from_stack(acc, 1) // 1 before stack pointer
remove_stack(3)        // resets sp so we dont overflow stack

compile and run shell commands are in commands.txt
output is in output.txt
