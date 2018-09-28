main:
    in %r3
    li %r4,0
loop:
    li %r5,0
    cmpd %r3,%r5
    beq end
    add %r4,%r4,%r3
    subi %r3,%r3,1
    jump loop
end:
    out %r3
(* => n * (n+1) / 2 *)
