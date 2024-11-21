
extern char ROWS;
extern char COLUMNS;
extern int Matrix_Coordinates[];

extern int check_square(int, int, int);


extern float my_division(float*, float*);

int main(void){

	int r=3;	
	int s;
	int sumSquares = 0;
	for(s=0; s<(ROWS*COLUMNS); s=s+2){
		int x = Matrix_Coordinates[s];             // x-coordinate at index s
    int y = Matrix_Coordinates[s + 1];         // y-coordinate at index s + 1
       
		sumSquares += check_square(x,y,r);
	}

	// Calculate r^2
  float r_squared = (float)(r * r);
    // Now, divide sumSquares by r^2 using the my_division function
  float sumSquares_f = (float)sumSquares;  // Convert sumSquares to float
  float result = my_division(&sumSquares_f, &r_squared);

	while(1);
}
