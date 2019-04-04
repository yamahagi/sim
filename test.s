test_opi: 
    addi %r3,%r4,1
    subi %r3,%r4,2
    muli %r3,%r4,3
    divi %r3,%r4,4
test_op: 
    add %r4,%r5,%r6
    sub %r4,%r5,%r6
    mul %r4,%r5,%r6
    div %r4,%r5,%r6
test_data:
    load %r4,%r5,5 (* %r4 <- [%r5+100] *)
    store %r4,%r5,6 (* [%r5+100] <- %r4 *)
jump_test: 
    jump test_opi
    cmpd %r3,%r4 
    beq test_op
    ble test_data
    in %r30
    out %r31
