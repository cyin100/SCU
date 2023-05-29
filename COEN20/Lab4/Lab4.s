			.syntax     unified
			.cpu        cortex-m4
			.text
			//                         R0         R1            R2            R3
			// int32_t MxPlusB(int32_t x, int32_t mtop, int32_t mbtm, int32_t b) ;
			.global     MxPlusB
			.thumb_func
			.align
MxPlusB:	PUSH		{R4-R12, LR}	//Push R4-12 and LR
			MUL			R4, R1, R0		//Multiply R1*R0
			SMMUL		R5, R4, R2		//Signed multiply R4*R2
			ASR			R6, R5, 31		//Shift R5 31 bits, store into R6
			MUL 		R7, R6, R2		//Multiply R6*R2
			LSL			R8, R7, 1		//Left shift R7 1 bit, store into R8
			ADD			R9, R8, R2		//Add R2+R8
			LDR			R4, =2			//Load constant into R4 for division
			SDIV		R10, R9, R4		//Returns value of 'rounding' variable
			MUL			R11, R1, R0 	//Multiply R1*R0
			ADD			R12, R11, R10	//Add R11+R10
			SDIV		R0, R12, R2		//Divide R12/R2
			ADD			R0, R0, R3		//Add R0+R3
			POP			{R4-R12, PC}	//Pop R4-12 and PC
			.end
