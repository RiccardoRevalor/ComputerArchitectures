#define RADIUS 5	//radius is fixed

extern int Matrix_Coordinates; //DCD = words so 4 bytes = int in C. Coordinate Matrix. It's also the first value of the matrix, -5
extern char ROWS; 								//DBD = char (1 byte)
extern char COLUMNS;


//define the functions: checkCoordinates(int, int, int) and my_division(float *, float *)
//MOCK UP CODE, USELESS extern int ASM_funct(int, int, int, int, int, int, int*);
extern int checkCoordinates(int x_, int y_, int r);
extern float my_division(float *, float *);

int main(void){

	int i;
	int x, y;
	int dim = (int)ROWS * (int)COLUMNS;
	
	//I put volatile to tell the compiler not to modify these variables
	volatile float pi = 0.0;
	volatile float Area = 0.0;
	
	int *matrix = &Matrix_Coordinates;
	
	//Algorithm: scan all the points of the squares that go from -r to + r, appy the circle condition and sum all of them to approximate tha Area
	
	for (i = 0; i < dim; i+=2){
		//row-major scanning of the matrix
		//matrix: x,y,x,y,x,y ecc
		x = matrix[i];
		y = matrix[i+1];
		
		//For each iteration ot the cycle I call the checkCoordinates Assembly function
		//It stores x in R0, y in R1 and RADIUS in R3
		//It returns either 1 (point (x,y) belongs to the circle so I have to sum it to the total Area) or 0 (point (x,y) does not belong to the cicle)
		//The result is returned in register R0 and C autonomously add it to the Area variable.
		Area += checkCoordinates(x, y, RADIUS); //update te total area of the circle by adding the area of the squares that fits in the circle
	
	}
	
	//calculate the final value of pi
	float den = (float) RADIUS * RADIUS; //for simplicity it's better to calculate the den here and pass the pointer with the result
	
	//I also have to cast the area pointer from (volatile float *) to (float *)
	pi = my_division((float *) &Area, &den);
	
	//r0 stores the calculated value of PI
		
	while(1);
}
