#include <stdio.h>
#define MAX_NAME 20
#define MAX 100

typedef struct {
	int id;
	char name[MAX_NAME];
}element;

void print(element arr[],int num) {
	int i;
	for(i=0;i<num;i++) {
		printf("%d : %s\n",arr[i].id,arr[i].name);
	}
	printf("\n");
}

char SortPrint() {
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

void selection_sort(element arr[],int num,int n) {
	int i,j,least;
	element temp;
	for(i=0;i<num;i++) {
		least = i;
		for(j=i+1;j<num;j++) {
			if(n==1) {
				if(arr[least].id>arr[j].id)
					least = j;
			}
			else if(n==2) {
				if(arr[least].id<arr[j].id)
					least = j;
			}
		}
		temp = arr[i];
		arr[i] = arr[least];
		arr[least] = temp;
	}
}

void insertion_sort(element arr[],int num,int n) {
	int i,j;
	element key;

	for(i=1;i<num;i++) {
		key = arr[i];
		if(n==1) {
			for(j=i-1;j>=0&&arr[j].id>key.id;j--) {
				arr[j+1] = arr[j];
			}
		}
		else if(n==2) {
			for(j=i-1;j>=0&&arr[j].id<key.id;j--) {
				arr[j+1] = arr[j];
			}
		}
		arr[j+1] = key;
	}
}

void bubble_sort(element arr[], int num,int n) {
	int i,j;
	element temp;

	for(i=num-1;i>0;i--) {
		for(j=0;j<i;j++) {
			if(n==1) {
				if(arr[j].id>arr[j+1].id) {
					temp = arr[j];
					arr[j] = arr[j+1];
					arr[j+1] = temp;
				}
			}
			else if(n==2) {
				if(arr[j].id<arr[j+1].id) {
					temp = arr[j];
					arr[j] = arr[j+1];
					arr[j+1] = temp;
				}
			}
		}
	}
}

void inc_insertion_sort(element arr[],int first,int last,int gap,int n) {
	int i,j;
	element key;

	for(i=first+gap;i<=last;i+=gap) {
		key = arr[i];
		if(n==1) {
			for(j=i-gap;j>=first&&key.id<arr[j].id;j-=gap) {
				arr[j+gap] = arr[j];
			}
		}
		else if(n==2) {
			for(j=i-gap;j>=first&&key.id>arr[j].id;j-=gap) {
				arr[j+gap] = arr[j];
			}
		}
		arr[j+gap] = key;
	}
}

void shell_sort(element arr[],int num,int n) {
	int i,gap;

	for(gap=num/2;gap>0;gap/=2) {
		if(gap%2==0) gap++;
		for(i=0;i<gap;i++) {
			inc_insertion_sort(arr,i,num-1,gap,n);
		}
	}
}

void merge(element arr[],int left,int mid,int right,int n) {
	int i,j,k,l;
	element sort[MAX];
	i = left, j=mid+1,k=left;

	while(i<=mid &&j<=right) {
		if(n==1) {
			if(arr[i].id<=arr[j].id)
				sort[k++] = arr[i++];
			else 
				sort[k++] = arr[j++];
		}
		else if(n==2) {
			if(arr[i].id>=arr[j].id)
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

void merge_sort(element arr[],int left,int right,int n) {
	int mid;

	if(left<right) {
		mid = (left+right)/2;
		merge_sort(arr,left,mid,n);
		merge_sort(arr,mid+1,right,n);
		merge(arr,left,mid,right,n);
	}
}

int partition(element arr[],int left,int right,int n) {
	element pivot,temp;
	int low,high;

	low = left;
	high = right+1;
	pivot = arr[left];

	do {
		if(n==1) {
			do
				low++;
			while(low<=right && arr[low].id<pivot.id);
			do 
				high--;
			while(high>=left && arr[high].id>pivot.id);
		}
		else if(n==2) {
			do
				low ++;
			while(low<=right && arr[low].id>pivot.id);
			do
				high--;
			while(high>=left && arr[high].id<pivot.id);
		}
		if(low<high) {
			temp = arr[low];
			arr[low] = arr[high];
			arr[high] = temp;
		}
	}while(low<high);
	temp = arr[left];
	arr[left] = arr[high];
	arr[high] = temp;

	return high;
}

void quick_sort(element arr[],int left,int right,int n) {
	int p;

	if(left<right) {
		p = partition(arr,left,right,n);
		quick_sort(arr,left,p-1,n);
		quick_sort(arr,p+1,right,n);
	}
}

void file() {

}

void keyboard() {
	element arr[MAX];
	int num,n;
	int i=0;
	char sort;
	printf("데이터의 갯수는? >> ");
	scanf("%d",&num);
	printf("id, 이름 순으로 데이터를 입력하라.\n");
	
	while(num!=i) {
		scanf("%d %s",&arr[i].id,arr[i].name);
		i++;
	}

	printf("오름차순 : 1\n내림차순 : 2 \n >> ");
	scanf("%d",&n);

	sort = SortPrint();

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