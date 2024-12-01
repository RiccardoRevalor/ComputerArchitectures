# 1 "customCFunctions.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 393 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "customCFunctions.c" 2


void ledsFromState(unsigned char state){
 int i;
 for(i=0; i<8; i++){
  if (state & (1 << i)) {
   LED_On(i);
    } else {
      LED_Off(i);
    }
 }

}
