#include<stdio.h>
#include<unistd.h>

int main() {

	pid_t ret; 
	ret = fork();

	if(ret == 0){
		printf("bin der Sohn %d. Gehe für 5 sec schlafen\n", ret);
		sleep(5);
		printf("Bin da mein Vater\n");
	}
	else {
		printf("bin der Vater %d. Warte aufn Sohn\n", ret);
		wait(NULL);
		printf("gut dass du da bist mein Sohn\n");
	}
	return 0;
}	
