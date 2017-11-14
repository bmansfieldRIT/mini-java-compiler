.class public TestOptimization
.super java/lang/Object
.method public static main([Ljava/lang/String;)V
.limit locals 10
.limit stack 10
	getstatic java/lang/System/out Ljava/io/PrintStream;
	new PrintNums
	dup 
	invokespecial PrintNums/<init>()V
	ldc 10
	invokevirtual PrintNums/Start(I)I
	invokevirtual java/io/PrintStream/println(I)V
	return
.end method
