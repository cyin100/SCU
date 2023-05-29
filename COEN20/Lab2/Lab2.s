				.syntax         unified
				.cpu            cortex-m4
				.text
				
				// int32_t Return32Bits(void)
				.global         Return32Bits
				.thumb_func
				.align
				
Return32Bits:	LDR 	R0,=10		//Load 10 into R0
				BX 		LR
				
				// int64_t Return64Bits(void) ;
				.global         Return64Bits
				.thumb_func
				.align
				
Return64Bits:	LDR 	R0,=-10		//Load 10 into R0
				LDR 	R1,=-1		//Load -1 into R1 
				BX 		LR
				
				// uint8_t Add8Bits(uint8_t x, uint8_t y)
				.global         Add8Bits
				.thumb_func
				.align
				
Add8Bits:		ADD 	R0, R0, R1	//Add x and y, store into R0
				UXTB 	R0, R0		//Change R0 to 8-bit
				BX 		LR
				
				// uint32_t FactSum32(uint32_t x, uint32_t y)
				.global         FactSum32
				.thumb_func
				.align
				
FactSum32:		PUSH 	{R4, LR}	//Pop LR and R4
				ADD 	R0, R0, R1	//Add x and y, store into R0
				BL 		Factorial	//R0 = factorial(x+y)
				POP		{R4, PC}	//Pop LR and R4
				
				// uint32_t XPlusGCD(uint32_t x, uint32_t y, uint32_t z)
				.global         XPlusGCD
				.thumb_func
				.align
				
XPlusGCD:		PUSH 	{R4, LR}	//Push LR and R4
				MOV 	R4, R0		//Store x value in R4
				MOV 	R0, R1		//Store y value in R0
				MOV 	R1, R2		//Store z value in R1
				BL 		gcd			//R0 = gcd(y,z)
				ADD 	R0, R0, R4	//Add x + gcd(y,z)
				POP 	{R4, PC}	//Pop LR and R4
				.end
