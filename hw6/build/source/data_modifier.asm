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

