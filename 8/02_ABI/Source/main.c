#define RADIUS 5	//radius is fixed

extern double *Matrix_Coordinates; //DCD = double. Coordinate Matrix. It's also the first value of the matrix, -5
extern char ROWS; 								//DBD = char
extern char COLUMNS;


//define the functions: checkCoordinates(int, int, int) and calculatePI(float *, float *)
//MOCK UP CODE, USELESS extern int ASM_funct(int, int, int, int, int, int, int*);

int main(void){

	int i, x, y;
	int dim = ROWS * COLUMNS;
	
	//I put volatile to tell the compiler not to modify these variables
	volatile float pi = 0.0;
	volatile float Area = 0.0;
	
	//Algorithm: scan all the points of the squares that go from -r to + r, appy the circle condition and sum all of them to approximate tha Area
	
	float den = (float) RADIUS * RADIUS;
	for (i = 0; i < dim; i++){
		//row-major scanning of the matrix
		//matrix: x,y,x,y,x,y ecc
		x = Matrix_Coordinates[i];
		y = Matrix_Coordinates[i+1];
		
		//Area += checkCoordinates(x, y, RADIUS); //update te total area of the circle by adding the area of the squares that fits in the circle
	
	}
	
	//calculate the final value of pi
	
	//pi = calculatePI(&Area, &den);
	
	//r0 stores the calculated value of PI
		
	while(1);
}
