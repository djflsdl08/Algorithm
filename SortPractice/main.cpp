#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 10
#define SWAP(x,y,t) ((t)=(x),(x)=(y),(y)=(t))

int n;
int sorted[MAX_SIZE];

void selection_sort(int list[],int n){      //선택정렬
    int i,j,least,temp;
    for(i=0;i<n-1;i++){
        least = i;
        for(j=i+1;j<n;j++){
            if(list[least]>list[j])
                least = j;
        }
        SWAP(list[i],list[least],temp);
    }
}
void insertion_sort(int list[],int n){      //삽입정렬
    int i,j,key;
    for(i=1;i<n;i++){
        key = list[i];
        for(j=i-1;j>=0&&list[j]>key;j--)
            list[j+1] = list[j];
        list[j+1] = key;
    }
}
void bubble_sort(int list[],int n){        //버블정렬
    int i,j,temp;
    for(i=n-1;i>0;i--){
        for(j=0;j<i;j++)
            if(list[j]>list[j+1])
                SWAP(list[j],list[j+1],temp);
    }
}
void inc_insertion_sort(int list[],int first,int last,int gap){
    int i,j,key;
    for(i=first+gap;i<=last;i++){
        key = list[i];
        for(j=i-gap;j>=first&&key<list[j];j=j-gap)
            list[j+gap] = list[j];
        list[j+gap] = key;
    }
}
void shell_sort(int list[],int n){      //쉘정렬
    int i,gap;
    for(gap=n/2;gap>0;gap/=2){
        if((gap%2)==0) gap++;
        for(i=0;i<gap;i++)
            inc_insertion_sort(list,i,n-1,gap);
    }
}
void merge(int list[],int left,int mid,int right){
    int i,j,k,l;
    i=left;j=mid+1;k=left;

    while(i<=mid&&j<=rignt){
        if(list[i]<=list[j])
            sorted[k++] = list[i++];
        else sorted[k++] = list[j++];
    }
    if(i>mid)
        for(l=j;l<=right;l++)
            sorted[k++] = list[l];
    else
        for(l=i;l<=mid;l++)
            sorted[k++] = list[l];
    for(l=left;l<=right;l++)
        list[l] = sorted[l];
}
void merge_sort(int list[],int left,int right){     //합병정렬
    int mid;
    if(left<right){
        mid = (left+right)/2;           //리스트 균등 분할
        merge_sort(list,left,mid);
        merge_sort(list,mid+1,right);   //부분 리스트 정렬
        merge(list,left,mid,right);     //합병
    }
}
int main(){
    int i;
    int list[MAX_SIZE] = {3,9,10,8,2,6,4,5,7,1};
    int list2[MAX_SIZE] = {3,9,10,8,2,6,4,5,7,1};
    int list3[MAX_SIZE] = {3,9,10,8,2,6,4,5,7,1};
    int list4[MAX_SIZE] = {3,9,10,8,2,6,4,5,7,1};
    n = MAX_SIZE;
    printf("Original list\n");
    for(i=0;i<n;i++)
        printf("%d\t",list[i]);
    selection_sort(list,n);
    printf("\n\nAfter Selection Sort\n");
    for(i=0;i<n;i++)
        printf("%d\t",list[i]);

    printf("\nAfter Insertion Sort\n");
    insertion_sort(list2,n);
    for(i=0;i<n;i++)
        printf("%d\t",list2[i]);
    printf("\nAfter Bubble Sort\n");
    bubble_sort(list3,n);
    for(i=0;i<n;i++)
        printf("%d\t",list3[i]);
    printf("\nAfter Shell Sort\n");
    shell_sort(list4,n);
    for(i=0;i<n;i++)
        printf("%d\t",list4[i]);
}