					.syntax         unified
					.cpu            cortex-m4
					.text
					// float EccentricAnomaly(float e, float M)
					.global         EccentricAnomaly
					.thumb_func
					.align
EccentricAnomaly:	// S0 = e, S1 = M
					PUSH            {LR}
					VPUSH           {S16-S18}
					VMOV			S16, S0			// S16 <-- e
					VMOV			S17, S1			// S17 <-- M
					VMOV			S0, S17			// S0 <-- M
					BL				sinDeg			// S0 <-- sinDeg(M)
					VMOV			S18, S0			// S18 <-- sinDeg(M)
					VMOV			S0, S17			// S0 <-- M
					BL				cosDeg			// S0 <-- cosDeg(M)
					VMUL.F32		S0, S0, S16		// S0 <-- e*cosDeg(M)
					VMOV			S1, 1.0 		// S2 <-- 1.0
					VADD.F32		S0, S0, S1		// S0 <-- 1+e*cosDeg(M)
					VMUL.F32		S0, S0, S16		// S0 <-- S0*e
					VMUL.F32		S0, S0, S18		// S0 <-- S0*sinDeg(M)
					BL				Rad2Deg			// S0 <-- Rad2Deg(S0)
					VMOV			S1, S17			// S1 <-- M
					VADD.F32		S0, S0, S1		// S0 <-- M+S0
					VPOP            {S16-S18}
					POP             {PC}

					// float Kepler(float m, float ecc)
					.global         Kepler
					.thumb_func
					.align
Kepler:				// S0 = m, S1 = ecc
					PUSH            {R3,LR}
					VPUSH           {S16-S19}
					VMOV			S16, S1			// S16 <-- ecc
					BL				Deg2Rad			// S0  <-- Deg2Rad(m)
					VMOV			S17, S0			// S17 <-- e
					VMOV			S18, S0			// S16 <-- m
Top:				BL				sinf			// S0 <-- sinf(e)
					VMUL.F32		S0, S16, S0		// S0 <-- ecc*sinf(e)
					VSUB.F32		S0, S17, S0		// S0 <-- e-ecc*sinf(e)
					VSUB.F32		S0, S0, S18		// S0 <-- e-ecc*sinf(e)-m
					VMOV			S19, S0			// S19 <-- delta
					VMOV			S0, S17			// S0 <-- e
					BL				cosf			// S0 <-- cosf(e)
					VMOV			S1, 1.0			// S1 <-- 1.0
					VMUL.F32		S0, S16, S0		// S0 <-- ecc*cosf(e)	
					VSUB.F32		S0, S1, S0		// S0 <-- 1-ecc*cosf(e)
					VDIV.F32		S0, S19, S0		// S0 <-- delta/S0
					VSUB.F32		S0, S17, S0		// S0 <-- e-S0
					VMOV			S0, S17			// S17 <-- e-s0
					VMOV			S0, S19			// S0 <-- delta
					VABS.F32		S0, S0			// S0 <-- abs(delta)
					VLDR			S1, epsilon		// S1 <-- 1E-6
					VCMP.F32		S0, S1			// CMP S0, S1
					VMRS 			APSR_nzcv, FPSCR
					BGT				Top				// if(S0 > S1) Top
					VMOV			S0, S17			// S0 <-- e
					VPOP            {S16-S19}
					POP             {R3,PC}

					.align
epsilon:			.float          1E-6
					.end
