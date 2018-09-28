main:
    in %r3
fact:
    li %r5,1
fact_sub:
    li %r4,0
    cmpd %r3,%r4
    beq end
    muli %r5,%r3,1
    subi %r3,%r3,1
    jump fact_sub
end:
    out %r5
