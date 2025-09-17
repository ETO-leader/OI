#include<cstdio>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
typedef long long LL;
const int N=1e6+9;
int SJQ,n,a[N],le[N]; LL k;
int tr[N];
void add(int x,int c){
    for(;x<=n;x+=x&-x) tr[x]+=c;
}
int qry(int x){
    int res=0;
    for(;x;x&=x-1) res+=tr[x];
    return res;
}
int main(){
    freopen("reverse.in","r",stdin);
    freopen("reverse.out","w",stdout);
    scanf("%d%d%lld",&SJQ,&n,&k); k=-k;
    for(int i=1;i<=n;i++) scanf("%d",&a[i]),k+=i-1-qry(a[i]),add(a[i],1);
    if(!k) return puts("0"),0;
    memset(tr,0,sizeof(tr));
    LL cur=0;
    for(int r=1,l=1;r<=n;r++){
        cur+=r-l-qry(a[r]);
        add(a[r],1);
        while(cur>k){
            add(a[l],-1);
            cur-=qry(a[l]);
            l++;
        }
        if(cur==k) return printf("1\n%d %d\n",l,r),0;
    }
    memset(tr,0,sizeof(tr));
    cur=0;
    for(int i=1;i<=n;i++){
        cur+=i-1-qry(a[i]);
        add(a[i],1);
        if(cur>=k){
            add(a[i],-1);
            cur-=i-1-qry(a[i]);
            printf("2\n%d %d\n",1,i-1);
            sort(a+1,a+i);
            printf("%d %d\n",i-(k-cur),i);
            return 0;
        }
    }
    return 0;
}