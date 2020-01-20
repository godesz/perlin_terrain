#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define hash_size 256

int SEED = 1;
int hash_array[256];

void generate_hash(int hash_s)
{
FILE *f;
char fullfilename[50];
sprintf(fullfilename,"hash_%d.txt",hash_s);
f=fopen(fullfilename,"w");

int i;
int mixing_number = 1000000; // mixing number
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

fclose(f);
}

void read_hash(int hash_s, int *poi)
{
FILE *f;
int i,tmp;
char fullfilename[50];
sprintf(fullfilename,"hash_%d.txt",hash_s);
f=fopen(fullfilename,"r");

for(i=0;i<hash_s;i++) 
	{
		fscanf(f,"%d",&tmp);
		printf("%d ",tmp);
		poi[i] = tmp;
	}
fclose(f);
}

int noise2(int x, int y)
{
    int tmp = hash_array[(y + SEED) % 256];
    return hash_array[(tmp + x) % 256];
}

float lin_inter(float x, float y, float s)
{
    return x + s * (y-x);
}

float smooth_inter(float x, float y, float s)
{
    return lin_inter(x, y, s * s * (3-2*s));
}

float noise2d(float x, float y)
{
    int x_int = x;
    int y_int = y;
    float x_frac = x - x_int;
    float y_frac = y - y_int;
    int s = noise2(x_int, y_int);
    int t = noise2(x_int+1, y_int);
    int u = noise2(x_int, y_int+1);
    int v = noise2(x_int+1, y_int+1);
    float low = smooth_inter(s, t, x_frac);
    float high = smooth_inter(u, v, x_frac);
    return smooth_inter(low, high, y_frac);
}

float perlin2d(float x, float y, float freq, int depth)
{
    float xa = x*freq;
    float ya = y*freq;
    float amp = 1.0;
    float fin = 0;
    float div = 0.0;

    int i;
    for(i=0; i<depth; i++)
    {
        div += 256 * amp;
        fin += noise2d(xa, ya) * amp;
        amp /= 2;
        xa *= 2;
        ya *= 2;
    }

    return fin/div;
}


int main(int argc, char *argv[] )
{
srand(time(NULL));


printf("Generating hash file with size %d...\n",hash_size);
generate_hash(hash_size);

printf("Reading hash file\n");
read_hash(hash_size,&(hash_array[0]));

printf("%d\n",hash_array[20]);

FILE *ki,*be;
ki = fopen("perlin_out.txt","w");
be = fopen("parameterek.txt","r");
int N,M, DEPTH;
double FREQ;
fscanf(be,"%d %d %lf %d %d",&N,&M,&FREQ,&DEPTH,&SEED);
printf("Generating Pnoise\n");
printf("x: %d, y:%d\n",N,M);
    int x, y;
    for(y=0; y<M; y++)
        for(x=0; x<N; x++)
            { 
			 fprintf(ki,"%d %d %lf\n",x,y,perlin2d(x, y, FREQ, DEPTH));
			}

fclose(ki);
fclose(be);



return 0;
}
