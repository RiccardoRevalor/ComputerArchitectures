
//extern int call_svc(void);
extern void __attribute__((naked)) call_scv(void);
int main(void){
	call_svc();
	
	
	while(1);
}