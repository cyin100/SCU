			// void CopyCell(uint32_t *dst, uint32_t *src) ;		// R0 = dst, R1 = src
			.syntax     unified
			.cpu        cortex-m4
			.text
			.global		CopyCell
			.thumb_func
			.align
CopyCell:	PUSH {R4, LR}
			LDR R2,=0
rowtop:		LDR R3,=0
			CMP R2, 60					// row < 60
			BHS done
coltop:		CMP R3, 60					// col < 60
			BHS coldone
			LDR R4, [R1, R3, LSL 2]		// dst[col] = src[col]
			STR R4, [R0, R3, LSL 2]		
			ADD R3, R3, 1				// col++
			B coltop
coldone:	ADD R0, R0, 960				// src+=240, dst+=240
			ADD R1, R1, 960
			ADD R2, R2, 1				// row ++
			B rowtop
done:		POP {R4, PC}

			// void FillCell(uint32_t *dst, uint32_t color) ;		// R0 = dst, R1 = color
			.global		FillCell
			.thumb_func
			.align
FillCell:	LDR R2,=0
rowtop2:	LDR R3,=0
			CMP R2, 60					// row < 60
			BHS done2
coltop2:	CMP R3, 60					// col < 60
			BHS coldone2
			STR R1, [R0, R3, LSL 2]		// dst[col] = pixel
			ADD R3, R3, 1				// col++
			B coltop2
coldone2:	ADD R0, R0, 960				// dst+=240
			ADD R2, R2, 1				// row ++
			B rowtop2
done2:
			.end
