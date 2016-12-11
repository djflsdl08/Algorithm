#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void insertion_sort(int list[], int s,int e) {
	int i,j;
	int item;
	
	for(i=s+1;i<=e;i++){
		item=list[i];
	  	for(j=i-1;j>=s &&list[j]>item; j--)
			list[j+1]=list[j];
	  	list[j+1]=item;
	}
}

void sort_Hash(int A[], int s, int e) {
	if(e <= s)	return;

	if(e-s+1<=5){
		insertion_sort(A, s, e);
		return;
	}

	int	i,j,k,index;
	double	a, b, min, max;
	int y;

	min = max = A[s];

	for(i=s+1;i<=e;i++){
		if(A[i] < min)	min= A[i];
		if(A[i] > max)	max= A[i];
	}

	a = ((double)(e-s))/(max-min);
	b = -min*a;

	printf("a = %lf, b = %lf\n",a, b);
	for(i=0;i<=e;i++){
       y=(int)(a*A[i]+b);
       printf("y = %d\n",y);
    }  
	int	*locn = (int *)malloc(sizeof(int)*(e-s+1));	//count
	int	*loce = (int *)malloc(sizeof(int)*(e-s+1));	//start index

	for(i=0;i<e-s+1;i++)
		locn[i] = 0;

	for(i=0;i<e-s+1;i++) {
		y=(int)(a*A[i]+b);
		locn[y]++;
	}

	loce[0] = 0;
	for(i=0;i<e-s;i++) {
		loce[i+1] = locn[i] + loce[i];
	}

	for(j=s;j<=e;j++) {
		y = (int)(a*A[j]+b);
		index = loce[y]+e+1;
		for(k=0;k<locn[y];k++){
			if(A[index]!=0) {
				index ++;
			}
			else break;
		}
		A[index] = A[j];
		for(int l=e+1;l<2*(e+1);l++)
			printf("%d ",A[l]);
		printf("\n");
	}
	
	
	for(i=0;i<e-s+1;i++) {
		printf("%d ~ %d \n",e+1+loce[i],e+1+locn[i]+loce[i]-1);
		sort_Hash(A,e+1+loce[i],e+1+locn[i]+loce[i]-1);
	}
	
}

int main() {
	int A[20];
	int i,j;

	srand(time(NULL));
	for(i=0;i<10;i++) {
		A[i]=rand()%99+1;
	}

	for(i=10;i<20;i++)
		A[i] = 0;

	for(i=0;i<10;i++)
		printf("%3d",A[i]);
	
	printf("\n");
	sort_Hash(A,0,9);

	for(i=0;i<20;i++) {
		printf("%3d",A[i]);
		if(i==9)
			printf("\n");
	}
}