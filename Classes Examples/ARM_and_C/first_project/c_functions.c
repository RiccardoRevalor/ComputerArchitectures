#include <math.h>
#define MAX_LENGTH 20

//function written in another file
//extern = this function is implemented in another file, itn makes the func visible throught the whole project
//it imports the symbol from another file, which I don't have to specify
//it looks thorgh all the files in the projects and finds it autonomously
//the concatenateString IS IMPLEMENTED IN ASSEMBLY
//i ADDED THE ASM_FUNCTION.S FILE TO MY:SOURCE FILES BY DOING RIGHT CLICK ON IT > ADD EXISTING FILES
extern int concatenateString(const char *, int, const char *, int, char *, int);


int inlineAssembly1(int);


int intSquareRoot(int intNumber)
{
	/* Function to compute the sqr root
	math.h needs to be included
	it receives an int, it computes the sqrt as double and then
	it approx the double result into an integer
	REMEMBER: ARM Cortex M3 does NOT support double or float values!
	JUST RETURN INTEGERS!
	*/
	
	//AT THE TOP THE DISASSEMBLY CODE REVEALS HOW THE C CODE IS CONVERTED TO ASM
	//ASM HAS MORE INSTRUCTIONS
	//THE FIRST 2 CORRESPONDS TO 2 LDR TO LOAD THE PERAM
	double realNumber;
	int result;
	realNumber = sqrt(intNumber);
	result = floor(realNumber + 0.5);
	return result;
}


int main(void){
	/*main function
	2 strings, 1 not initialized
	I wanna take three characters from the first one four ch from the second one
	and concatenate them into the third string, by calling the concatenateString function
	This function return the numbers of copied chars (3+4=7 but it could be less if we reach MAX_LENGTH of string3)
	Its a function written in another file so I need its prototype (extern)
	*/
	//the compiler loads the adx of the strings in r0 and the stores r0 into te stack
	//it does so for the 2 strings
	//r0 is used for everything and the everything isa saves into the stack
	const char *string1 = "problem solving";
	const char *string2 = "grammar book";
	char string3[MAX_LENGTH];
	int len1 = 3, len2 = 4;
	int len3;	
	int myNumber;
	volatile int sumFirstAndLast;
	
	//we have BL.W in the disassebly to call the function
	//before it we have some instructions loading from the stack intio the registers r0, r1, r2, r3 the params to be passed to concatenateString
	len3 = concatenateString(string1, len1, string2, len2, string3, MAX_LENGTH);
	//concatenateString return the value in r0. This values is stored into the stack
	
	//Example to show the use of a variable
	for (int index = 0; index < len3; index++){
		string3[index] += 'A' - 'a';
	}
	
	//alternative:
	//I can define len3 as VOLATILE
	volatile int len3_v;
	//it means this variabe can be accessed somewehere else in my code
	//ex I can use it in an exception handler
	//I am telling the compiler this variables can be used somewhere else so the compiler cannot optimize this sariable
	len3_v = concatenateString(string1, len1, string2, len2, string3, MAX_LENGTH);
	
	myNumber = 0x7A30458D;
	sumFirstAndLast = inlineAssembly1(myNumber);
	
	
	//I need an infinte loop that replicates the b . (or stop b stop) loop in the assembly
	while(1); //move the infinite loop from reset handler to main
	//IN the future we will put the cpu in power saving mode, eliminating this
}


//IN-LINE ASM EXAMPLE
int inlineAssembly1(int value)
	/* IN LINE ASM
I PUT 3 INSTR IN THE C CODE, : AND, LSR, ADD
1)AND: 2 INPUT OPERANDS (asmVaue and #0x000000FF), 1 OUTPUT (asmVar2)
asmValue AND #0x000000FF -> result goes into asmVar2

2)LSR: LSR asmVar1, asmValue, #24
so asmValue shifted left by #24, result goes into asmVar1

3)ADD asmRes, asmVar1, asmVar2
asmRes = asmVar1 + asmVar2
so it is the sum of LSB + MSB
	*/
{
	int var1, var2, res;
	__asm__ volatile(
		"AND %[asmVar2], %[asmValue], #0x000000FF\n\t"
		"LSR %[asmVar1], %[asmValue], #24\n\t"
	  "ADD %[asmRes], %[asmVar1], %[asmVar2]"
	: [asmVar1] "=r" (var1),
	  [asmVar2] "=r" (var2),
	  [asmRes] "=r" (res)
	: [asmValue] "r" (value)
	);
	return res;
}