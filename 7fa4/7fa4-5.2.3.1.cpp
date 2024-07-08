#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
template<typename T,size_t mem,int mxr>
class segments{
private:
    struct node{
        node*ls,*rs;T w;
        void merge(node*n,int l,int r){
            if(l==r) return w+=n->w,void();
            const int mid=(l+r)/2;
            if(ls&&(n->ls)) merge(ls,n->ls,l,mid);
            else ls=n->ls;
            if(rs&&(n->rs)) merge(rs,n->rs,mid+1,r);
            else rs=n->rs;
        }
    };
    array<node,mem> vmmem;
    stack<int> stmem;
    node*newnode(){
        node*res=&vmmem[stmem.top()];
        stmem.pop();
        return res;
    }
    node*go(node*&x){
        if(!x) x=newnode();
        return x;
    }
    void update(node*u,int l,int r,int p,T w){
        if(l==r) u->w+=w;
        const int mid=(l+r)/2;
        if(p<mid+1) update(go(u->ls),l,mid,p,w);
        else update(go(u->rs),mid+1,r,p,w);
    }
    vector<node*> rts;
public:
    void merge(int u,int v){
        rts[u]->merge(rts[v],0,mxr-1);
    }
    void update(int u,int p,T w){
        update(rts[u],0,mxr-1,p,w);
    }
    segments(int nsum){
        cir(i,0,mem) stmem.push(i);
        cir(i,0,nsum) rts[i]=newnode();
    }
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    
    return 0;
}
