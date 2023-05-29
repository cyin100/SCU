/*
    Conner Yin
	Lab 2
	Filename: Lab4.c
*/

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

static const char hex[] = "0123456789ABCDEF";
static const int length = 8;

/* Helper method to convert base 10 to base x string */
void UnsignedHelper(uint8_t bits, char string[], int radix){
	
	int temp = bits;
	int count = 0;
	char values[8];

	//Repeat division and remainder until 0
	while(temp > 0){
		values[count] = hex[temp%radix];
		temp /= radix;
		count++;
	}
	
	//If binary keep 0's in front
	if(radix == 2){
		for(int i=count; i<length; i++){
			values[count] = hex[0];
			count++;
		}
	}
	
	//Add remainders into string
	for(int i=0; i<count; i++){
		string[i] = values[count-i-1];
	}
	
	//Populate extra with nulls
	for(int i=count; i<length; i++){
		string[i] = '\0';
	}
	
	//Edge case if bits is 0
	if(bits == 0)
		string[0] = '0';
}

/* Convert to octal string */
void Bits2OctalString(uint8_t bits, char string[]){ 
	UnsignedHelper(bits, string, 8);
}

/* Convert to decimal string */
void Bits2UnsignedString(uint8_t bits, char string[]){ 
	UnsignedHelper(bits, string, 10);
}

/* Convert to hexadecimal string */
void Bits2HexString(uint8_t bits, char string[]){ 
	UnsignedHelper(bits, string, 16);
}

/* Convert to two's complement string */
void Bits2TwosCompString(uint8_t bits, char string[]){
	
	char binary[8];
	int index = length-1;
	UnsignedHelper(bits, binary, 2);
	
	//If starts with 0, return decimal
	if(binary[0] == '0'){
		UnsignedHelper(bits, string, 10);
	}
	else {
		
		char magnitude[8];
		
		//Copy from LSB until find 1
		while(binary[index] == '0' && index >= 0){
			magnitude[index] = '0';
			index--;
		}
		magnitude[index] = '1';
		index--;
		
		//Return opposites from then on
		while(index >= 0){
			if(binary[index] == '0')
				magnitude[index] = '1';
			else
				magnitude[index] = '0';
			index--;
		}
		
		//Convert new to decimal
		int value = 1;
		int mag = 0;
		for(int i=length-1; i>=0; i--){
			if(magnitude[i]=='1')
				mag += value;
			value *= 2;
		}
		UnsignedHelper(mag, magnitude, 10);
		
		//Return '-' + magnitude
		string[0] = '-';
		for(int i=1; i<length; i++){
			string[i] = magnitude[i-1];
		}
	}
}

/* Convert to signed magnitude string */
void Bits2SignMagString(uint8_t bits, char string[]){
	
	//Depending on sign, keep value or subtract 2^7
	char binary[8];
	int mag = 0;
	UnsignedHelper(bits, binary, 2);
	
	if(binary[0] == '0'){
		string[0] = '+';
		mag = bits;
	}
	else{
		string[0] = '-';
		mag = bits - 128;
	}
	
	//Set string to sign + magnitude
	char magnitude[8];
	UnsignedHelper(mag, magnitude, 10);
	for(int i=1; i<length; i++){
		string[i] = magnitude[i-1];
	}
}

