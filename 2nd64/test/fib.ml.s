return:
 	end
init:
	lil %lr,return
	li %r0,0
	li %fp,3
	li %sp,3
	li %r3,500000
	store %r3, %r0,0
	jump main
main : (* Global Fun  ? somewhere  *)
	addi %fp,%sp,0 (*  ? somewhere  *)
	store %lr,%fp, 1 (*  ? somewhere  *)
	addi %sp,%sp,2 (*  ? somewhere  *)
	store %fp,%sp, 0 (*  ? somewhere  *)
	li %r3,5 (* at line 4 *)
	bl V19.V9.fib (* at line 4 *)
	addi %r3,%r3,0 (*  ? somewhere  *)
	load %lr, %fp ,1 (*  ? somewhere  *)
	addi %sp,%fp,0 (*  ? somewhere  *)
	load %fp, %fp ,0 (*  ? somewhere  *)
	blr
V19.V9.fib : (* Global Fun  ? somewhere  *)
	addi %fp,%sp,0 (*  ? somewhere  *)
	store %lr,%fp, 1 (*  ? somewhere  *)
	addi %sp,%sp,5 (*  ? somewhere  *)
	store %fp,%sp, 0 (*  ? somewhere  *)
	store %r3,%fp, 2 (*  ? somewhere  *)
	li %r28,1 (* at line 2 *)
	store %r28,%fp, 3 (*  ? somewhere  *)
	cmpd %r3,%r28(* at line 2 *)
	ble @@label37.if.true (* at line 2 *)
@@label37.if.false : (* Local Label at line 2 *)
	li %r27,1 (* at line 3 *)
	sub %r3,%r3,%r27 (* at line 3 *)
	bl V19.V9.fib (* at line 3 *)
	addi %r28,%r3,0 (*  ? somewhere  *)
	store %r28,%fp, 4 (*  ? somewhere  *)
	li %r27,2 (* at line 3 *)
	load %r26, %fp ,2 (*  ? somewhere  *)
	sub %r3,%r26,%r27 (* at line 3 *)
	bl V19.V9.fib (* at line 3 *)
	addi %r27,%r3,0 (*  ? somewhere  *)
	load %r28, %fp ,4 (*  ? somewhere  *)
	add %r3,%r28,%r27 (* at line 3 *)
	jump @@label38 (* at line 2 *)
@@label37.if.true : (* Local Label at line 2 *)
	addi %r3,%r3,0 (* at line 2 *)
@@label38 : (* Local Label at line 2 *)
	load %lr, %fp ,1 (*  ? somewhere  *)
	addi %sp,%fp,0 (*  ? somewhere  *)
	load %fp, %fp ,0 (*  ? somewhere  *)
	blr
