#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
template<typename T>
class segment{
private:
    vector<T> arr;
    struct node{
        int l,r;
        array<array<T,4>,4> D;
        node*ls,*rs;
        int length(){return r-l+1;}
        void bf_dp(int len,auto&ar){
            vector<array<T,4>> f(length()+1);
            T cnx=0;
            if(l+len-1>r) return;
            cir(i,l,l+len) cnx+=ar[i];
            f[len][len]=cnx;
            cir(i,len,length()) cir(w,0,4){
                f[i+1][0]=max(f[i+1][0],f[i][w]);
                if(w<3&&i!=len){
                    f[i][w+1]=max(f[i][w+1],f[i][w]);
                    f[i+1][w+1]=max(f[i+1][w+1],
                        f[i][w]+ar[l+i]);
                }
            }
            cir(w,0,4) D[len][w]=f[length()][w];
        }
        void set(T w){
            cir(i,0,4) cir(j,0,4)
                D[i][j]=w*(bool)(i)*(bool)(j);
        }
        void maintain(auto&ar){
            memset(D.begin(),0,sizeof(D));
            if(ls->length()<4||rs->length()<4){
                cir(w,0,4) bf_dp(w,ar);
                cir(i,0,4) cir(j,0,4){
                    if(i) D[i][j]=max(D[i][j],D[i-1][j]);
                    if(j) D[i][j]=max(D[i][j],D[i][j-1]);
                }
                return;
            }
            cir(i,0,4) cir(j,0,4) cir(k,0,4){
                D[i][k]=max(D[i][k],ls->D[i][j]+
                    rs->D[3-j][k]);
            }
        }
        void build(){
            ls=new node();rs=new node();
        }
        T calc(){
            T res=0;
            cir(i,0,4) cir(j,0,4)
                res=max(res,D[i][j]);
            return res;
        }
    };
    node*root;int n;
    void build(node*u,int l,int r){
        u->l=l;u->r=r;
        if(l==r) return u->set(arr[l]);
        u->build();
        const int mid=(l+r)/2;
        build(u->ls,l,mid);
        build(u->rs,mid+1,r);
        u->maintain(arr);
    }
    void update(node*u,int l,int r,int p){
        if(l==r) return u->set(arr[l]);
        const int mid=(l+r)/2;
        (mid<p)?update(u->rs,mid+1,r,p):
            update(u->ls,l,mid,p);
        u->maintain(arr);
    }
public:
    void update(int p,T w){
        arr[p]=w;
        update(root,0,n,p);
    }
    auto operator()(){return root->calc();}
    void reset(vector<T> v){
        (*this)=segment(v);
    }
    segment(vector<T> v=vector<T>()):arr(v){
        n=v.size()-1;
        if(!v.empty())
            build((root=new node()),0,n);
    }
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    freopen("poster.in","r",stdin);
    freopen("poster.out","w",stdout);
    int n;cin>>n;vector<lint> a(n);
    for(auto&i:a) cin>>i;
    array<array<segment<lint>,4>,4> D;
    cir(i,0,4) cir(j,0,4) if(i+j<4){
        const int l=i+1,r=n-j-2;
        if(r>l-1){
            D[i][j].reset(vector<lint>(
                a.begin()+l,a.begin()+r+1));
        }
    }
    auto sum=[&](int l,int r){
        lint res=0;
        cir(i,l,r+1) res+=a[i];
        return res;
    };
    auto getans=[&](){
        lint res=0;
        cir(i,0,4) cir(j,0,4) if(i+j<4){
            const int l=i+1,r=n-j-2;
            if(r>l-1){
                res=max(res,D[i][j]()+
                    sum(0,l-2)+sum(r+2,n-1));
            }else if(r>l){
                res=max(res,
                    sum(0,l-1)+sum(r+1,n-1));
            }
        }
        return res;
    };
    auto update=[&](int p,lint w){
        a[p]=w;
        cir(i,0,4) cir(j,0,4) if(i+j<4){
            const int l=i+1,r=n-j-2;
            if(l<p+1&&p-1<r&&r>l-1)
                D[i][j].update(p-l,w);
        }
    };
    cout<<getans()<<'\n';
    int q;cin>>q;
    while(q--){
        int p;lint w;cin>>p>>w;
        update(p-1,w);
        cout<<getans()<<'\n'<<flush;
    }
    return 0;
}
