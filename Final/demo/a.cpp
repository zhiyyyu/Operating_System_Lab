#include<stdio.h>
#include<stdlib.h>
int main(){
	FILE* fp = open("./1.txt", "r");
	if(fp) fclose(fp);
	return 0;
}
