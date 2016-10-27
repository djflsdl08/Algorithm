#include <stdio.h>
#include <stdlib.h>
#define MAX 100

char sortPrint() {
	char ch;

	getchar();
	do {
		printf("s : 선택정렬\n");
		printf("i : 삽입정렬\n");
		printf("b : 버블정렬\n");
		printf("h : 쉘 정렬\n");
		printf("m : 합병정렬\n");
		printf("q : 퀵정렬\n");
		printf(" >> ");
		scanf("%c",&ch);
	}while(ch!='s'&&ch!='i'&&ch!='b'&&ch!='h'&&ch!='m'&&ch!='q');
	
	return ch;
}

void selection_sort(int arr[],int num,int n) {
	int i,j,least,temp;

	for(i=0;i<num;i++) {
		least = i;
		for(j=i+1;j<num;j++) {
			if(n==1){
				if(arr[least]>arr[j]) {
					least = j;
				}
			}
			else if(n==2) {
				if(arr[least]<arr[j]) {
					least = j;
				}
			}
		}
		temp = arr[i];
		arr[i] = arr[least];
		arr[least] = temp;
	}
}

void insertion_sort(int arr[],int num,int n) {
	int i,j,key;
	
	for(i=1;i<num;i++) {
		key = arr[i];
		if(n==1) {
			for(j=i-1;j>=0&&arr[j]>key;j--) {
				arr[j+1] = arr[j];
			}
		}
		else if(n==2) {
			for(j=i-1;j>=0&&arr[j]<key;j--) {
				arr[j+1] = arr[j];
			}
		}
		arr[j+1] = key;
	}
}

void bubble_sort(int arr[], int num,int n) {
	int i,j,temp;

	for(i=num-1;i>0;i--) {
		for(j=0;j<i;j++) {
			if(n==1) {
				if(arr[j]>arr[j+1]) {
					temp = arr[j+1];
					arr[j+1] = arr[j];
					arr[j] = temp;
				}
			}
			else if(n==2) {
				if(arr[j]<arr[j+1]) {
					temp = arr[j+1];
					arr[j+1] = arr[j];
					arr[j] = temp;
				}
			}
		}
	}
}

void inc_insertion_sort(int arr[],int first,int last, int gap,int n) {	// shell_sort()
	int i,j,key;

	for(i=first+gap;i<=last;i+=gap) {
		key = arr[i];
		if(n==1) {
			for(j=i-gap;j>=first && key<arr[j];j-=gap) {
				arr[j+gap] = arr[j];
			}
		}
		else if(n==2) {
			for(j=i-gap;j>=first && key>arr[j];j-=gap) {
				arr[j+gap] = arr[j];
			}	
		}
		arr[j+gap] = key;
	}
}

void shell_sort(int list[], int num,int n) {
	int i,gap;
	
	for(gap=num/2;gap>0;gap/=2) {
		if(gap%2==0)
			gap ++;
		for(i=0;i<gap;i++) {
			inc_insertion_sort(list,i,num-1,gap,n);
		}
	}
}

void merge(int arr[],int left,int mid,int right,int n) {		// merge_sort()
	int i,j,k,l;
	int sort[MAX];
	i = left, j = mid +1, k=left;

	while(i<=mid && j<=right) {
		if(n==1) {
			if(arr[i]<=arr[j])
				sort[k++] = arr[i++];
			else
				sort[k++] = arr[j++];
		}
		else if(n==2) {
			if(arr[i]>=arr[j])
				sort[k++] = arr[i++];
			else
				sort[k++] = arr[j++];	
		}
	}
	if(i>mid) {
		for(l=j;l<=right;l++) {
			sort[k++] = arr[l];
		}
	}
	else {
		for(l=i;l<=mid;l++) {
			sort[k++] = arr[l];
		}
	}
	for(l=left;l<=right;l++) {
		arr[l] = sort[l];
	}
}

void merge_sort(int arr[],int left,int right,int n) {
	int mid;

	if(left<right) {
		mid = (left+right)/2;
		merge_sort(arr,left,mid,n);
		merge_sort(arr,mid+1,right,n);
		merge(arr,left,mid,right,n);
	}
}

int partition(int arr[],int left,int right,int n) { 	// quick_sort()
	int pivot,tmp;
	int low,high;

	low = left;
	high = right + 1;
	pivot = arr[left];

	do {
		if(n==1) {
			do
				low ++;
			while(low<=right && arr[low]<pivot);
			do
				high --;
			while(high>=left && arr[high]>pivot);
		}
		else if(n==2) {
			do
				low ++;
			while(low<=right && arr[low]>pivot);
			do
				high --;
			while(high>=left && arr[high]<pivot);	
		}
		if(low<high) {
			tmp = arr[low];
			arr[low] = arr[high];
			arr[high] = tmp;
		}
	}while(low<high);
	tmp = arr[left];
	arr[left] = arr[high];
	arr[high] = tmp;

	return high;
}

void quick_sort(int arr[],int left,int right,int n) {
	int p;

	if(left<right) {
		p = partition(arr,left,right,n);
		quick_sort(arr,left,p-1,n);
		quick_sort(arr,p+1,right,n);
	}
}

void print(int arr[],int n) {
	int i;
	for(i=0;i<n;i++) {
		printf("%d\t",arr[i]);
	}
	printf("\n");
}

void sortSwitch(int arr[],int num) {
	int n;
	char sort;

	printf("오름차순 : 1\n내림차순 : 2 \n >> ");
	scanf("%d",&n);

	sort = sortPrint();

	printf("정렬 전 >> \n");
	print(arr,num);

	switch(sort) {
		case 's' : selection_sort(arr,num,n); break;
		case 'i' : insertion_sort(arr,num,n); break;
		case 'b' : bubble_sort(arr,num,n); break;
		case 'h' : shell_sort(arr,num,n); break;
		case 'm' : merge_sort(arr,0,num-1,n); break;
		case 'q' : quick_sort(arr,0,num-1,n); break;
	}

	printf("정렬 후 >> \n");
	print(arr,num);
}

void file() {
	FILE *fp;
	char *fileName;
	int num,arr[MAX],i=0,n;
	char sort;

	fileName = (char *)malloc(sizeof(char)*100);

	printf("파일 이름은?(확장자 명까지 입력) >> ");
	scanf("%s",fileName);

	fp = fopen(fileName,"r");
	if(fp==NULL) {
		printf("%s 이름의 파일이 없습니다.\n",fileName);
		exit(1);
	}
	fscanf(fp,"%d\n",&num);
	while(!feof(fp)) {
		fscanf(fp,"%d\n",&arr[i]);
		i++;
	}

	sortSwitch(arr,num);
	fclose(fp);
}

void keyboard() {
	int num,arr[MAX],n;
	int i=0;
	char sort;
	printf("데이터의 갯수는? >> ");
	scanf("%d",&num);
	printf("데이터를 입력하라.\n");
	
	while(num!=i) {
		scanf("%d",&arr[i]);
		i++;
	}
	
	sortSwitch(arr,num);
}

int main() {
	int n;
	printf("파일로 입력하길 원하면 1 을 입력하고, \n");
	printf("키보드로 입력하길 원하면 2 를 입력하라. \n");
	
	do {
		printf(" >> ");
		scanf("%d",&n);
		switch(n) {
			case 1 : file(); break;
			case 2 : keyboard(); break;
			default : printf("1 또는 2를 입력하라.\n"); break;
		}
	}while(n!=1&&n!=2);
}