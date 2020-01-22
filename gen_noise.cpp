// https://imagetostl.com/
// https://www.viewstl.com/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define N 400
#define M 400
#define iterations 500

/*****************************************************************************************/
int main()
{
srand(time(NULL));

int i, j;
// forrásmap, NxM-es, [0.0,1.0] kitöltéssel
float map[N][M];
for(i=0;i<N;i++) for(j=0;j<M;j++) map[i][j] = (1.0*rand()/RAND_MAX);

//tempmap, innen mindig visszaírásra kerül
float map2[N][M];
for(i=0;i<N;i++) for(j=0;j<M;j++) map2[i][j] = 0;

// db-nyiszor a cellába belevenni a szomszédcellákat
int db = iterations, x,y,k;
for(k=0;k<db;k++)
{
for(i=0;i<N;i++) for(j=0;j<M;j++)
{
x=i;
y=j;
map2[x][y] = 0.2 * (map[x][y] ) + 0.2 * ( map[((x-1)+N)%N][y] + map[((x+1)+N)%N][y] + map[x][((y-1)+M)%M] + map[x][((y-1)+M)%M] );
//if (map2[x][y] > 1000) printf("%f ",map2[x][y]);
}

//eredeti mapra visszaírni
for(i=0;i<N;i++) for(j=0;j<M;j++) map[i][j] = map2[i][j];
}

// z-range keresés, max-min
float min, max;
min = map[0][0];
max = map[0][0];
for(i=0;i<N;i++) for(j=0;j<M;j++)
			{
			if (map[i][j] > max) max = map[i][j];
			if (map[i][j] < min) min = map[i][j];
			}
printf("%f %f\n",min,max);

//normalizálás
for(i=0;i<N;i++) for(j=0;j<M;j++)
					map[i][j] = (map[i][j] - min) / (max - min) ;

FILE *ki;
ki = fopen("noise_map.txt","w");
for(i=0;i<N;i++) for(j=0;j<M;j++)
						fprintf(ki,"%d %d %lf\n",i,j,map[i][j]);


fclose(ki);
return 0;
}
/*****************************************************************************************/
