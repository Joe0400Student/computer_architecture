start:  lodd on:
        stod 4095
        call xbsywt:
        loco str1:
nextw:  pshi
        addd c1:
        stod pstr1:
        pop
        jzer crnl:
        stod 4094
        push
        subd c255:
        jneg crnl:
        call sb:
        insp 1
        push
        call xbsywt:
        pop
        stod 4094
        call xbsywt:
        lodd pstr1:
        jump nextw:
crnl:   lodd count:
	jzer endprogram:
	lodd cr:
        stod 4094
        call xbsywt:
        lodd nl:
        stod 4094
        call xbsywt:
        lodd on:                ; mic1 program to print string
        stod 4093               ; and scan in a 1-5 digit number
bgndig: call rbsywt:            ; using CSR memory locations
        lodd 4092
        subd numoff:
        push
nxtdig: call rbsywt:
        lodd 4092
        stod nxtchr:
        subd nl:
        jzer endnum:
        mult 10
        lodd nxtchr:
        subd numoff:
        addl 0
        stol 0
        jump nxtdig:
endnum: lodd numptr:
        popi
        addd c1:
        stod numptr:
        lodd numcnt:
        jzer addnms:
        subd c1:
        stod numcnt:
        jump start:
addnms: lodd pointer:
	stod temppointer:
	loco str2:
	stod copyfrompointer:
	call copyover:
	loco 15
	stod pos:
	loco str1:
	stod pointer:
	lodd binum1:
	addd binum2:
	jneg overflow:
	push
	call getn:
	pop
	loco 0
	stod count:
	loco str1:
	jump start:
overflow:
	loco 0
	stod count:
	loco str3:
	stod copyfrompointer:
	call copyover:
	loco str1:
	jump start:
xbsywt:	lodd 4095
        subd mask:
        jneg xbsywt:
        retn
rbsywt:	lodd 4093
        subd mask:
        jneg rbsywt:
        retn
sb:     loco 8
loop1:  jzer finish:
        subd c1:
        stod lpcnt:
        lodl 1
        jneg add1:
        addl 1
        stol 1
        lodd lpcnt:
        jump loop1:
add1:   addl 1
        addd c1:
        stol 1
        lodd lpcnt:
        jump loop1:
finish: lodl 1
        retn

insert:
	lodd pos:
	addd pointer:
	swap
	stod stack:
	lodd handthrough:
	stol 0
	lodd stack:
	swap
	retn

getn:	lodl 1
	jzer endof:
	desp 2
	stol 0
	loco 10
	stol 1
	div
	lodl 0
	jzer single:
	jump double:
single:	loco 48
	addl 1
	stol 0
	loco 32
	stol 1
	mult 4
	mult 4
	mult 4
	mult 4
	lodl 0
	addl 1
	stol 0
	stod handthrough:
	call insert:
	insp 4
	retn
double:	loco 48
	addl 1
	stol 1
	lodl 0
	desp 2
	stol 0
	loco 10
	stol 1
	div
	call getn:
	loco 1
	addd pos:
	stod pos:
	loco 0
	addl 5
	stol 0
	mult 4
	mult 4
	mult 4
	mult 4
	loco 48
	addl 0
	addl 1
	stod handthrough:
	call insert:
	insp 8
	retn
endof:	retn

copyover:
	desp 1
	loco 30
	stol 0
loop11:	lodl 0
	jneg endcopyover:
	lodd copyfrompointer:
	stod pointer:
	lodl 0
	stod pos:
	call getstr:
	loco str1:
	stod pointer:
	call insert:
	lodl 0
	subd c1:
	stol 0
	jump loop11:
endcopyover:
	insp 1
	retn
getstr:
	lodd pointer:
	addd pos:
	swap
	stod stack:
	lodl 0
	stod handthrough:
	lodd stack:
	swap
	retn

endprogram:
	halt

numoff: 48
nxtchr: 0
numptr: binum1:
binum1: 0
binum2: 0
lpcnt:  0
mask:   10
on:     8
nl:     10
cr:     13
c1:     1
c10:    10
c255:   255
sum:    0
numcnt: 1
pstr1:  0
str1:   "Please enter a 1-5 digit number followed by enter           "
c256:	256
str2:	"THE SUM OF THESE INTEGERS IS:                               "
char:	0
ptrswap: 0
char2:  0
carRetn: 13
newLine: 10
pos:	15
pointer: str1:
val:	0
handthrough: 0
tempavl:	0
stack:	0
constant: 256
zerochar:	48
spaces: " "
str3:	"THE SUM OF THESE INTEGERS IS: OVERFLOW, NO SUM IS POSSIBLE  "
pointerstr1:	str1:
pointerstr2:	str2:
pointerstr3:	str3:
temppointer:	0
temppos:	0
copyfrompointer:	0
count: 3
