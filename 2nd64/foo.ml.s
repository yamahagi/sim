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
	li %r3,3 (* at line 3 *)
	bl V7.V3.f (* at line 3 *)
	addi %r3,%r3,0 (*  ? somewhere  *)
	load %lr, %fp ,1 (*  ? somewhere  *)
	addi %sp,%fp,0 (*  ? somewhere  *)
	load %fp, %fp ,0 (*  ? somewhere  *)
	blr
V7.V3.f : (* Global Fun  ? somewhere  *)
	addi %fp,%sp,0 (*  ? somewhere  *)
	store %lr,%fp, 1 (*  ? somewhere  *)
	addi %sp,%sp,3 (*  ? somewhere  *)
	store %fp,%sp, 0 (*  ? somewhere  *)
	store %r3,%fp, 2 (*  ? somewhere  *)
	li %r28,2 (* at line 2 *)
	add %r3,%r3,%r28 (* at line 2 *)
	load %lr, %fp ,1 (*  ? somewhere  *)
	addi %sp,%fp,0 (*  ? somewhere  *)
	load %fp, %fp ,0 (*  ? somewhere  *)
	blr
