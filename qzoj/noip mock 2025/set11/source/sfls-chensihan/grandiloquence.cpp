#include<cstdio>
#include<random>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
typedef long long LL;
const int N=4e5+9;
int SJQ,n,Q,k,dep[N],mo[100];
mt19937 rnd(random_device{}());
struct node{
    int l,r,p,sz,dep,col,tag; unsigned val;
    int cnt[10],res[10];
}tr[N*2]; int rt,dl,dm,dr;
void pushup(int u){
    tr[u].sz=tr[tr[u].l].sz+1+tr[tr[u].r].sz;
    for(int i=0;i<k;i++) tr[u].cnt[i]=tr[tr[u].l].cnt[i]+tr[tr[u].r].cnt[i],tr[u].res[i]=tr[tr[u].l].res[i]+tr[tr[u].r].res[i];
    tr[u].cnt[tr[u].dep]++;
    if(~tr[u].col) tr[u].res[tr[u].col]++;
}
void pushdown(int u,int tag){
    if(!u) return;
    tr[u].tag=tag;
    tr[u].col=mo[tr[u].dep+tag];
    for(int i=0;i<k;i++) tr[u].res[mo[i+tag]]=tr[u].cnt[i];
}
void pushdown(int u){
    if(~tr[u].tag){
        pushdown(tr[u].l,tr[u].tag);
        pushdown(tr[u].r,tr[u].tag);
        tr[u].tag=-1;
    }
}
void split(int u,int k,int &l,int &r){
    if(!u){
        l=r=0;
        return;
    }
    pushdown(u);
    if(tr[tr[u].l].sz+1<=k) l=u,split(tr[l].r,k-tr[tr[u].l].sz-1,tr[l].r,r),tr[tr[l].r].p=l;
    else r=u,split(tr[r].l,k,l,tr[r].l),tr[tr[r].l].p=r;
    pushup(u);
}
int merge(int x,int y){
    if(!x||!y) return x|y;
    pushdown(x),pushdown(y);
    if(tr[x].val<=tr[y].val){
        tr[x].r=merge(tr[x].r,y);
        tr[tr[x].r].p=x;
        pushup(x); return x;
    }
    else{
        tr[y].l=merge(x,tr[y].l);
        tr[tr[y].l].p=y;
        pushup(y); return y;
    }
}
int get_rk(int x){
    int res=1+tr[tr[x].l].sz;
    while(tr[x].p){
        int p=tr[x].p;
        if(tr[p].r==x) res+=tr[tr[p].l].sz+1;
        x=p;
    }
    return res;
}
void out(int u){
    if(!u) return;
    pushdown(u);
    if(tr[u].l){
        if(tr[tr[u].l].p!=u) printf("(no %d %d)",tr[u].l,u);
    }
    out(tr[u].l);
    printf("(%d,%d)",u,tr[u].col);
    if(tr[u].r){
        if(tr[tr[u].r].p!=u) printf("(no %d %d)",tr[u].r,u);
    }
    out(tr[u].r);
}
int main(){
    freopen("grandiloquence.in","r",stdin);
    freopen("grandiloquence.out","w",stdout);
    scanf("%d%d%d%d",&SJQ,&n,&Q,&k); SJQ=SJQ&1^1;
    for(int i=0;i<100;i++) mo[i]=i%k;
    for(int i=1,p;i<=n;i++){
        scanf("%d",&p);
        tr[i*2-1].dep=tr[i*2].dep=dep[i]=(dep[p]+1)%k;
        tr[i*2-1].col=tr[i*2].col=-1;
        tr[i*2-1].val=tr[i*2].val=rnd();
        tr[i*2-1].tag=tr[i*2].tag=-1;
        tr[i*2-1].cnt[dep[i]]++,tr[i*2].cnt[dep[i]]++;
        tr[i*2-1].sz=tr[i*2].sz=1;
        if(!p) rt=merge(1,2);
        else{
            // printf("get_rk %d %d\n",2*p,get_rk(2*p));
            split(rt,get_rk(2*p)-1,dl,dr);
            // printf("dl: "); out(dl); puts("");
            // printf("dr: "); out(dr); puts("");
            rt=merge(merge(dl,2*i-1),merge(2*i,dr));
        }
        // out(rt); puts("");
    }
    int lastans=0,op,u,c;
    while(Q--){
        scanf("%d%d",&op,&u);
        if(SJQ) u^=lastans;
        // printf("op u = %d %d\n",op,u);
        if(op==1){
            scanf("%d",&c);
            if(SJQ) c^=lastans;
            // printf("c = %d\n",c);
            split(rt,get_rk(2*u),dl,dr);
            // printf("dl: "); out(dl); puts("");
            // printf("get_rk %d %d\n",2*u-1,get_rk(2*u-1));
            split(dl,get_rk(2*u-1)-1,dl,dm);
            // printf("subtree %d: ",u); out(dm); puts("");
            pushdown(dm,(-dep[u]+c-1+k+k)%k);
            rt=merge(merge(dl,dm),dr);
        }
        else if(op==2){
            scanf("%d",&c);
            if(SJQ) c^=lastans;
            // printf("c = %d\n",c);
            split(rt,get_rk(2*u),dl,dr);
            split(dl,get_rk(2*u-1)-1,dl,dm);
            // printf("subtree %d: ",u); out(dm); puts("");
            printf("%d\n",lastans=tr[dm].res[c-1]>>1);
            rt=merge(merge(dl,dm),dr);
        }
        else{
            n++;
            tr[n*2-1].dep=tr[n*2].dep=dep[n]=(dep[u]+1)%k;
            tr[n*2-1].col=tr[n*2].col=-1;
            tr[n*2-1].val=tr[n*2].val=rnd();
            tr[n*2-1].tag=tr[n*2].tag=-1;
            tr[n*2-1].cnt[dep[n]]++,tr[n*2].cnt[dep[n]]++;
            tr[n*2-1].sz=tr[n*2].sz=1;
            split(rt,get_rk(2*u)-1,dl,dr);
            // printf("dl: "); out(dl); puts("");
            // printf("dr: "); out(dr); puts("");
            rt=merge(merge(dl,2*n-1),merge(2*n,dr));
        }
        // printf("rt: "); out(rt); puts("");
    }
    return 0;
}