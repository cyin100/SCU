			.syntax	unified
			.cpu	cortex-m4
			.text
			.global	PutNibble
			.thumb_func
			.align
			// void PutNibble(void *nibbles, uint32_t index, uint32_t nibble) ;
PutNibble:	PUSH	{R4, LR}
			ADD 	R4,	R0, R1, LSR 1	// which >> 1 ;
			LDRB	R3, [R4]			// pbyte = (uint8_t *) nibbles + (which >> 1)
			AND		R1, R1, 1			// which & 1
			CMP 	R1 , 1				// if ((which & 1) == 1)
			IT		EQ
			LSLEQ	R2, R2, 4			// value << 4 ; 
			CMP		R1, 1
			ITTEE	EQ					
			ANDEQ	R3, R3, 0b00001111	// *pbyte &= 0b00001111 ;
			ORREQ	R3, R3, R2			// *pbyte |= value << 4 ; 
			ANDNE	R3, R3, 0b11110000	// *pbyte &= 0b11110000 ;
			ORRNE	R3, R3, R2 			// *pbyte |= value ;
			STRB	R3, [R4]
			POP		{R4, PC}
			.global	GetNibble
			.thumb_func
			.align
			// uint32_t GetNibble(void *nibbles, uint32_t index) ;
GetNibble:	LSR		R3, R1, 1			// which >> 1
			LDRB	R2, [R0, R3]		// byte = ((uint8_t *) nibbles)[which >> 1] ;
			AND 	R1, R1, 1			// which & 1
			CMP		R1, 1				// if ((which & 1) == 1)
			IT		EQ
			LSREQ 	R2, R2, 4			// byte >>= 4 
			AND		R0, R2, 0b00001111	// return (uint32_t) (byte & 0b00001111) ;
			BX		LR
			.end
