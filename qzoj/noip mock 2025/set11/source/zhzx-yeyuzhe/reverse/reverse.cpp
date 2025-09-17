#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn=1000005;
int id,N,A[maxn];
int tr1[maxn],tr2[maxn];
LL K,cur;
void add1(int x,int y){for(;x;x-=x&-x) tr1[x]+=y;}
int que1(int x){int ret=0;for(;x<=N;x+=x&-x) ret+=tr1[x];return ret;}
void add2(int x,int y){for(;x<=N;x+=x&-x) tr2[x]+=y;}
int que2(int x){int ret=0;for(;x;x-=x&-x) ret+=tr2[x];return ret;}
void add(int x){cur+=que1(x);add1(x,1);add2(x,1);}
void del(int x){add1(x,-1);add2(x,-1);cur-=que2(x);}
bool solve1(){
    int R=0;cur=0;
    for(int L=1;L<=N;L++){
        while(R+1<=N&&cur<K) add(A[++R]);
        if(cur==K){
            printf("1\n%d %d\n",L,R);
            return 1;
        }
        del(A[L]);
    }
    return 0;
}
int tr[maxn];
void add(int x,int y){for(;x;x-=x&-x) tr[x]+=y;}
int que(int x){int ret=0;for(;x<=N;x+=x&-x) ret+=tr[x];return ret;}
void solve2(){
    memset(tr,0,sizeof tr);
    for(int i=1;i<=N;i++){
        int c=que(A[i]);add(A[i],1);
        if(K>=c) K-=c;
        else{
            puts("2");
            printf("%d %d\n",1,i-1);
            printf("%d %d\n",i-(int)K,i);
            break;
        }
    }
}
int main(){
    freopen("reverse.in","r",stdin);
    freopen("reverse.out","w",stdout);
    cin.tie(0)->sync_with_stdio(0);
    cin>>id>>N>>K;K=-K;
    for(int i=1;i<=N;i++) cin>>A[i],K+=que(A[i]),add(A[i],1);
    if(K==0) puts("0");
    else if(!solve1()) solve2();
    return 0;
}