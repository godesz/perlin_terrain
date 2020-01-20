#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define hash_size 256

void generate_hash(int hash_s)
{
FILE *f;
char fullfilename[50];
sprintf(fullfilename,"hash_%d.txt",hash_s);
f=fopen(fullfilename,"w");

int i;
int mixing_number = 100000; // mixing number
int temp = 0;
int hash_map[hash_s];
for(i=0;i<hash_size;i++) hash_map[i]= i;

for(i=0;i<mixing_number;i++)
{
int n1,n2;
n1 = rand()%hash_s;
n2 = (n1+rand()%hash_s)%hash_s; // to get different n1 and n2
temp = hash_map[n1];
hash_map[n1] = hash_map[n2];
hash_map[n2] = temp; //change n1 n2
//printf("%d ,",n2);
}



for(i=0;i<hash_size;i++)   // output array
fprintf(f,"%d\n",hash_map[i]);

}

int main(int argc, char *argv[] )
{
srand(time(NULL));

printf("Generating hash file with size %d...\n",hash_size);
generate_hash(hash_size);

return 0;
}












