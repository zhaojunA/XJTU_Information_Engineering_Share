.global calculate
	mov w0,#0
calculate:
	add w0,w1,w0
	lsl w0,w0,3
	lsr w0,w0,1
	ret
