get_integer:
        loco 0
        desp 2
        stol 1
        loco 0
        stol 0
        call enable_rx:
loop:   call get_input_char:
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


