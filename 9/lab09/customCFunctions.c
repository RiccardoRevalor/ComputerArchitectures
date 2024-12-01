

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