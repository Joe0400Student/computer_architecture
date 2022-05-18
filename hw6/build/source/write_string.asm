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

