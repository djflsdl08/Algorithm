#include <stdio.h>
#include <stdlib.h>
#define SIZE 9
int sorted[SIZE];
int ksort[SIZE];

void merge(int arr[],int left,int mid,int right) {
	int i,j,k,l;
	i = left; j=mid+1; k=left;

	while(i<=mid && j<=right) {
		if(arr[i]<=arr[j]) {
			sorted[k++] = arr[i++];
		}
		else {
			sorted[k++] = arr[j++];
		}
	}
	if(i>mid) {
		for(l=j;l<=right;l++) {
			sorted[k++] = arr[l];
		}
	}
	else {
		for(l=i;l<=mid;l++) {
			sorted[k++] = arr[l];
		}
	}
	for(l=left;l<=right;l++) {
		arr[l] = sorted[l];
	}
}

void merge_sort(int arr[],int left,int right) {
	int mid;

	if(left<right) {
		mid = (left+right)/2;
		merge_sort(arr,left,mid);
		merge_sort(arr,mid+1,right);
		merge(arr,left,mid,right);
	}
}
int min(int arr[],int indexL[],int k) {
	int i=0,least;

	if(indexL[i]!=SIZE)
		least = indexL[i];
	else {
		while(1){
			i++;
			if(indexL[i]!=SIZE){
				least = indexL[i];
				break;
			}
		}
	}
	for(i=1;i<k;i++) {
		if(indexL[i]!=SIZE) {
			if(arr[indexL[i]]<arr[least]) {
				least = indexL[i];
			}
		}
	}

	return least;
}

void kmerge(int arr[],int left,int right,int k,int n[]) {
	int indexR[k],i,check=0,sub=n[0];		//sub : 갯수-1
	int indexL[k];
	int x=0,indexMin;

	if(right-left<=(k-1)) {
		merge_sort(arr,left,right);
	}
	else {
		for(i=0;i<k-1;i++) {
			indexR[i] = n[i];
			indexL[i] = n[i]-sub;
		}
		indexR[i] = right;
		indexL[i] = n[i-1]+1;

		while(check!=SIZE) {
			indexMin = min(arr,indexL,k);
			ksort[x++] = arr[indexMin];

			for(i=0;i<k;i++) {
				if(indexMin == indexL[i]) {
					if(indexL[i]!=indexR[i])
						indexL[i]++;
					else indexL[i] = SIZE;
				}
			}
			check++;
		}
		
		for(i=0;i<SIZE;i++) {
			arr[i] = ksort[i];
		}
	}
}

void kmerge_sort(int arr[],int left,int right,int k) {
	int *n,i,num,Fleft=left,num2;

	if((right-left) >= k-1) {
		n = (int *)malloc(sizeof(int)*(k-1));
		if(right-left==k-1) {
			num = left;
			for(i=0;i<(k-1);i++)
				n[i] = num++;
		}
		else {
			num = (int)((left+right+1)/k);
			num2 = num;
			for(i=0;i<(k-1);i++) {
				n[i] = num-1;
				num+=num2;
			}
		}
		i=0;
		while(i!=(k-1)) {
			kmerge_sort(arr,Fleft,n[i],k);
			Fleft = n[i]+1;
			i++;
		}
		kmerge_sort(arr,Fleft,right,k);
	}
	printf("left index : %d , right index : %d\n",left,right);
	kmerge(arr,left,right,k,n);
	for(i=0;i<SIZE;i++)
		printf("%d ",arr[i]);
	printf("\n");
}

int main() {
	int arr[SIZE] = {9,2,4,1,8,6,29,3,15};
	kmerge_sort(arr,0,8,3);
}