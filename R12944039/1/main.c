#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

// Function to check if an array is beautiful
int isBeautiful(int arr[], int n) {
    if(n<=2){
        return 1;
    }
    for (int i = 0; i < n - 2; i++) {
        // long long result=(arr[i + 1] - arr[i]) * (arr[i + 2] - arr[i + 1]);
        // if (result >= 0) {
        //     return 0; // Not beautiful
        // }
        int front,rear;
        if(arr[i+1]>arr[i]){
            front=1;
        }else if(arr[i+1]<arr[i]){
            front=-1;
        }else{
            front=0;
        }
        if(arr[i+2]>arr[i+1]){
            rear=1;
        }else if(arr[i+2]<arr[i+1]){
            rear=-1;
        }else{
            rear=0;
        }
        if((front*rear)>=0) return 0;
    }
    return 1; // Beautiful
}

// Function to check if the given number exist in array.
int isExist(int arr[], int bound, int n){
	for (int i=0;i<bound;i++){
		if (arr[i]==n) return 1;
	}
	return 0;
}

// Recursion function to count all permutations.
void countPermut(int arr[], int visited[], int output[], int start, int end,int* cnt){
	if(!(isBeautiful(output,start))) return;
	if(start==end){
		(*cnt)++;
		return;
	}
	int picked[end];
	int count=0;
	if(start<2){
		for(int i=0;i<end;i++){
			if((count==0) && !(visited[i])){
				output[start]=arr[i];
				visited[i]=1;
				picked[count]=arr[i];
				count++;
				countPermut(arr,visited,output,start+1,end, cnt);
				visited[i]=0;
			}else if (!(isExist(picked,count,arr[i])) && !(visited[i])){
				output[start]=arr[i];
				visited[i]=1;
				picked[count]=arr[i];
				count++;
				countPermut(arr,visited,output,start+1,end, cnt);
				visited[i]=0;
			}
		}
		return;
	}else{
		for(int i=0;i<end;i++){
			if((count==0) && !(visited[i])){
				output[start]=arr[i];
				visited[i]=1;
				picked[count]=arr[i];
				count++;
				countPermut(arr,visited,output,start+1,end, cnt);
				visited[i]=0;
			}else if (!(isExist(picked,count,arr[i])) && !(visited[i])){
				output[start]=arr[i];
				visited[i]=1;
				picked[count]=arr[i];
				count++;
				countPermut(arr,visited,output,start+1,end, cnt);
				visited[i]=0;
			}
		}
		return;
	}	
}

// Recursion function to generate all permutations.
void genPermut(int arr[], int visited[], int output[], int start, int end){
	if(!(isBeautiful(output,start))) return;
	if(start==end){
		for (int i=0;i<end;i++){
			printf("%d ",output[i]);
		}
		printf("\n");
		return;
	}
	int picked[end];
	int count=0;
	if(start<2){
		for(int i=0;i<end;i++){
			if((count==0) && !(visited[i])){
				output[start]=arr[i];
				visited[i]=1;
				picked[count]=arr[i];
				count++;
				genPermut(arr,visited,output,start+1,end);
				visited[i]=0;
			}else if (!(isExist(picked,count,arr[i])) && !(visited[i])){
				output[start]=arr[i];
				visited[i]=1;
				picked[count]=arr[i];
				count++;
				genPermut(arr,visited,output,start+1,end);
				visited[i]=0;
			}
		}
		return;
	}else{
		for(int i=0;i<end;i++){
			if((count==0) && !(visited[i])){
				output[start]=arr[i];
				visited[i]=1;
				picked[count]=arr[i];
				count++;
				genPermut(arr,visited,output,start+1,end);
				visited[i]=0;
			}else if (!(isExist(picked,count,arr[i])) && !(visited[i])){
				output[start]=arr[i];
				visited[i]=1;
				picked[count]=arr[i];
				count++;
				genPermut(arr,visited,output,start+1,end);
				visited[i]=0;
			}
			
		}
		return;
	}	
}

// Comparation function to use qsort function.
int compare(const void *a, const void *b){
    return (*(int*) a-*(int*) b);
}

int main(){
	
	int N;
    scanf("%d", &N);

    int arr[N];
    for (int i = 0; i < N; i++) {
        scanf("%d", &arr[i]);
    }
	int visited[N];
    for (int i = 0; i < N; i++) {
        visited[i] = 0;
    }
	int output[N];
	qsort(arr,N,sizeof(int),compare);
	int count=0;
	countPermut(arr, visited, output, 0, N, &count);
	printf("%d\n",count);
	genPermut(arr, visited, output, 0, N);
	return 0;
}
