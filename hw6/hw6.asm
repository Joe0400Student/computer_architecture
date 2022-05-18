main:
	lodd charptr:
	push
	call print_str:
	insp 1
	call get_integer:
	stod num1:
	lodd charptr:
	push
	call print_str:
	insp 1
	call get_integer:
	stod num2:
	lodd resultptr:
	push
	call print_str:
	insp 11
	call add_nums:
	jneg overflow:
	push
	call print_integer:
	insp 1
	lodd emptyptr:
	push
	call print_str:
	insp 1
	loco 0
	halt
	jump main:
overflow:
	lodd ptrover:
	push
	call print_str:
	insp 1
	lodd n1:
	halt
	jump main:


add_nums:
	lodd num1:
	addd num2:
	jneg r1:
	retn
r1:	lodd n1:
	retn

enable_tx:
	loco 8
	stod 4095
	retn
write_char:
	call enable_tx:
	call xbsywt:
	lodl 1
	stod 4094
	call xbsywt:
	call disable_tx:
	retn
disable_tx:
	loco 0
	stod 4095
	retn

enable_rx:
	loco 8
	stod 4093
	lodd 4093
	retn

disable_rx:
	loco 0
	stod 4093
	retn


xbsywt:
	lodd 4095
	subd mask:
	jneg xbsywt:
	retn
rbsywt:
	lodd 4093
	subd mask:
	jneg rbsywt:
	retn

get_high:
	lodl 1
	rshift 8
	retn

get_low:
	lodl 1
	desp 2
	stol 0
	lodd c256:
	stol 1
	div
	lodl 1
	insp 4
	retn
print_double:
	lodl 1
	push
	call get_low:
	insp 1
	jzer eprint_double:
	push
	call write_char:
	insp 1
	lodl 1
	push
	call get_high:
	insp 1
	jzer eprint_double:
	push
	call write_char:
	insp 1
	loco 1
	retn
eprint_double:
	loco 13
	push
	call write_char:
	loco 10
	stol 0
	call write_char:
	insp 1
	loco 0
	retn



print_str:
	lodl 1
	push
	call deref:
	;halt
	insp 1
	push
	call print_double:
	insp 1
	jzer end_print:
	addl 1
	push
	call print_str:
	insp 1
end_print:
	retn

multiply:
	loco 0
	addl 1
	addl 1
	addl 1
	addl 1
	addl 1
	addl 1
	addl 1
	addl 1
	addl 1
	addl 1
	retn
get_integer:
	loco 0
	desp 2
	stol 1
	loco 0
	stol 0
	call enable_rx:
loop:	call get_input_char:
	subd nl:
	jzer end_int:
	addd nl:
	subd c48:
	stol 1
	call multiply:
	addl 1
	stol 0
	jump loop:
end_int:
	call disable_rx:
	lodl 0
	insp 2
	retn

get_input_char:
	call rbsywt:
	lodd 4092
	retn

deref:
	lodl 1
	;halt
	swap
	stod tmp0:
	lodl 0
	stod tmp1:
	lodd tmp0:
	swap
	lodd tmp1:
	retn

print_integer:
	lodl 1
	jzer end_pint:
	desp 2
	stol 0
	loco 10
	stol 1
	div
	call print_integer:
	lodl 1
	addd c48:
	stol 0
	call write_char:
	insp 4
	retn
end_pint:
	retn

char:	"PLEASE ENTER AN INTEGER BETWEEN 1 AND 32767"
mask:	10
charptr:	char:
tmp0: 0
tmp1: 0
c256: 256
c48:	48
tmp:	0
nl:	10
ptrover:	overflowed_number:
overflowed_number:	"OVERFLOW, NO SUM IS POSSIBLE"
empty:	"  "
emptyptr:	empty:
num1:	0
num2:	0
num3:	0
result:	"THE SUM OF THESE INTEGERS IS:"
resultptr:	result:
n1:	-1

