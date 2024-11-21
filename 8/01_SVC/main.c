
__attribute__((naked)) call_svc();

int main() {
	
	call_svc();
	
	while(1){};
	
	return 0;
}