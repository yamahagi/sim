li %r3,1
li %r4,0
cmpd %r3,%r4
ble b1
b1:
    out %r3
    jump end
b2:
    out %r4
    jump end
end:
(* 0 is expected *)
