#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream fcin("community.in");
ofstream fcout("community.out");
class fileio{
public:
    ~fileio(){
        fcin.close();fcout.close();
    }
} set_fileio;
using lint=long long;
using VI=vector<lint>;
class blocks{
private:
    int blcsiz;VI b,arr;
    struct node{
        int l,r;bool fx;
        lint sum,ftag;
        void fill(lint x){
            sum=(r-l+1)*x;ftag=x;fx=true;
        }
    };
    vector<node> blc;
    void push_down(node&p){
        if(p.fx) cir(i,p.l,p.r+1)
            arr[i]=p.ftag;
        p.fx=false;
    }
    void initblocks(int n){
        blcsiz=sqrt(n)+7;
        for(int l=0;l<n;l+=blcsiz){
            blc.push_back({
                l,min(l+blcsiz-1,n),0});
            cir(i,l,l+blcsiz){
                b[i]=blc.size()-1;
            }
        }
    }
    auto bfsum(int l,int r){
        auto&n=blc[b[l]];push_down(n);
        lint x=0;
        cir(i,l,r) x+=arr[i];
        return x;
    }
    auto bfupd(int l,int r,lint x){
        auto&n=blc[b[l]];push_down(n);
        cir(i,l,r+1){
            n.sum+=(x-arr[i]);arr[i]=x;
        }
    }
public:
    auto get(int l,int r){
        const auto bl=b[l],br=b[r];
        if(bl==br) return bfsum(l,r);
        lint res=bfsum(l,blc[bl].r)+
            bfsum(blc[br].l,r);
        cir(i,l+1,r) res+=blc[i].sum;
        return res;
    }
    auto update(int l,int r,lint x){
        const auto bl=b[l],br=b[r];
        if(bl==br) return bfupd(l,r,x);
        bfupd(l,blc[bl].r,x);
        bfupd(blc[br].l,r,x);
        cir(i,l+1,r) blc[i].fill(x);
    }
    auto at(int x){
        push_down(blc[b[x]]);
        return arr[x];
    }
    blocks(int n):b(n),arr(n){initblocks(n);}
};
auto process(string&s){
    string res("!");
    for(auto&i:s) (res+='#')+=i;
    return (res+='#');
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    string s;int k;cin>>s>>k;
    s=process(s);
    blocks chr(s.size()),sum(s.size());
    auto manacher=[&](int l,int r){
        VI p(r-l+1);int maxr=l,pos=l;
        cir(i,l,r+1){
		    if(i<maxr){
                p[i-l]=min<int>(p[(pos<<1)-i],maxr-i);
            }
		    while(chr.at(i-p[i-l]-1)==chr.at(i+p[i-l]+1))
                ++p[i-l];
		    if(i+p[i-l]>maxr) maxr=i+p[i-l],pos=i;
	    }
        return p;
    };
    cir(i,0,s.size()) chr.update(i,i,s[i]);
    [&](){
        auto px=manacher(0,s.size()-1);
        cir(i,0,s.size()) sum.update(i,i,px[i]);
    }();

    return 0;
}
