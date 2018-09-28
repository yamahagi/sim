li %r3,0
li %r4,1
cmpd %r3,%r4
beq b1
b1:
    out %r3
    jump end
b2:
    out %r4
    jump end
end:
(* 1 is expected *)
