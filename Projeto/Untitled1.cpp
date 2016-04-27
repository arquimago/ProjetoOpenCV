#include <stdio.h>
#include <stdlib.h>

int aleatorio(int seed) {
int maxI =1000;
int r[maxI];
unsigned int retorno;
int i;

r[0] = seed;
for (i=1; i<31; i++) {
  r[i] = (16807LL * r[i-1]) % 2147483647;
  if (r[i] < 0) {
    r[i] += 2147483647;
  }
}
for (i=31; i<34; i++) {
  r[i] = r[i-31];
}
for (i=34; i<344; i++) {
  r[i] = r[i-31] + r[i-3];
}
for (i=344; i<maxI; i++) {
  r[i] = r[i-31] + r[i-3];
  retorno = ((unsigned int)r[i]) >> 1;
  printf("%d\n", retorno);

}
return retorno;
}

int main(){
srand(5);
int i;
for(i=0;i<10;i++){
printf("%d \n", aleatorio(257)%256);
}

}
