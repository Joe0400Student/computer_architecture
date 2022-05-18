enable_tx:
	loco 8
	stod 4095
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

