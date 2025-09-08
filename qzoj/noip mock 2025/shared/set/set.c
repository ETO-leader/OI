#include<stdio.h>
#include<stdlib.h>

typedef struct{
    int*data;
    int cap;
    int pos;
} vector_int;

vector_int construct_vector_int(){
    vector_int res;
    res.data=malloc(sizeof(int));
    res.cap=1;
    res.pos=0;
    return res;
}

void emplace_back(vector_int*a,int x){
    ++a->pos;
    if(a->pos>a->cap){
        a->data=realloc(a->data,sizeof(int)*a->cap*2);
        a->cap*=2;
    }
    a->data[a->pos-1]=x;
}

#define MAXN 15

vector_int vn[MAXN];

void initVN(){
    int p=0;
    loopInitArr:;
        vn[p]=construct_vector_int();
    if((++p)<MAXN) goto loopInitArr;
}

void main(int argc,char**argv){
    initVN();

    int n;scanf("%d",&n);
    vector_int vs=construct_vector_int();
    
    int s=0;
    loopInit:
    if(__builtin_popcount(s)==(n+1)/2) emplace_back(&vs,s);
    if((++s)<(1<<n)) goto loopInit;
    int ans=vs.pos;
    
    int i=0,j;
    loopProc:;
        j=0;
        loopProcInn:;
            if((vs.data[i]>>j)&1) emplace_back(&vn[j],i);
        if((++j)<n) goto loopProcInn;
    if((++i)<ans) goto loopProc;

    printf("%d\n",ans);
    
    i=0;
    loopPrintSet:;
        printf("%d ",vn[i].pos);
        j=0;
        loopPrintSetInn:;
            printf("%d ",vn[i].data[j]+1);
        if((++j)<vn[i].pos) goto loopPrintSetInn; 
        printf("\n");
    if((++i)<n) goto loopPrintSet;

    i=0;
    loopPrintMethod:;
        printf("%d ",(n+1)/2);
        j=0;
        loopPrintMethodInn:;
            if((vs.data[i]>>j)&1) printf("%d ",j+1);
        if((++j)<n) goto loopPrintMethodInn;
        printf("\n");
    if((++i)<ans) goto loopPrintMethod;
}
