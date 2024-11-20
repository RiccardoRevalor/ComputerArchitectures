
//extern int call_svc(void);
__attribute__((naked)) int call_scv();
int main(void){
	call_svc();
	
	
	while(1);
}