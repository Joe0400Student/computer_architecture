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
