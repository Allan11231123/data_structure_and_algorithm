#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
int d = 52;

void hashing(int* arr, int target[], int K, int N, int hash){
    for(int i=0;i<N;i++){
        int temp = 0;
        for(int j=0;j<K;j++){
            temp = (d*temp+arr[j*K+i])%hash;
        }
        target[i] = temp;
    }
    return;
}
int main(){
    int K,N,M,hash;
    scanf("%d %d %d %d",&K,&N,&M,&hash);
    printf("%d %d %d %d\n",K,N,M,hash);
    int t[K][N];
    int p[K][M];
    char temp;
    for(int i=0;i<K;i++){
        for(int j=0;i<N;j++){
            scanf("%c",&temp);
            // if(65<=temp<97) t[i][j] = temp-65;
            // else t[i][j] = temp-97+26;
            // printf("%d ",temp);
        }
        printf("\n");
    }
    for(int i=0;i<K;i++){
        for(int j=0;i<M;j++){
            scanf("%c",&temp);
            if(65<=temp<97) p[i][j] = temp-65;
            else p[i][j] = temp-97+26;
            printf("%d ",p[i][j]);
        }
        printf("\n");
    }

    int tPlon[N];
    int pPlon[M];
    hashing(&t[0][0],tPlon,K,N,hash);
    hashing(&p[0][0],pPlon,K,M,hash);
    for(int i=0;i<N;i++){
        printf("%d ",tPlon[i]);
    }
    printf("\n");
    for(int i=0;i<M;i++){
        printf("%d ",pPlon[i]);
    }
    return 0;
}