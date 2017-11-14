.class public PrintNums
.super java/lang/Object
.method public <init>()V
	aload_0
	invokenonvirtual java/lang/Object/<init>()V
	return
.end method
.method public Start(I)I
.limit locals 10
.limit stack 10
	ldc 1
	istore_3
	ldc 0
	istore_2
	ldc 3
	ldc 5
	ldc 5
	iadd
	iadd
	istore_4
	ldc 3
	istore_3
	label1:
	iload_2
	iload_1
	if_icmpge label3
	iconst_1
	goto label4
	label3:
	iconst_0
	label4:
	ifeq label2
	getstatic java/lang/System/out Ljava/io/PrintStream;
	iload_2
	invokevirtual java/io/PrintStream/println(I)V
	iload_2
	ldc 1
	iadd
	istore_2
	goto label1
	label2:
	iload_2
	ireturn
.end method
