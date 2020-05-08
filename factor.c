#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#include "fs.h"
//fungsi untuk menghitung faktorisasi bilangan prima
void primefact(int x);

int main (int arg1,char *arg2[])
{
  int x, faktor;

  for(x=1;x<arg1;x++){
	if(arg2[x][0]=='-'){
        printf(1,"Input anda berupa bilangan negatif. Masukkan bilangan positif!\n");
        exit();
    	}
    faktor = atoi(arg2[x]); //convert ke angka
      printf(1,"%d: ", faktor); //bisa input lebih dari 1
      primefact(faktor);
  }
  exit();
}


void primefact(int x)
{

int bil=2,i;
for (i=bil; x>1; i++){
     while(x % i == 0) {
      printf(1, "%d ", i);
      x = x/i; 
   }
}
    printf(1,"\n");
    return;
}
