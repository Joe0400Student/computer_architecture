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

