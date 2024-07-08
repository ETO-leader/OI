#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
template<typename T>
class odt{
private:
	struct Node{
		int l,r;mutable T v;
		bool operator<(const Node&n) const{
			return l<n.l;
		}
	};
	set<Node> Sn;int n;
	auto split(int k){
		if(k>n) return Sn.end();
		auto it=--Sn.upper_bound({k,0,0});
		if(it->l==k) return it;
		auto l=it->l,r=it->r,v=it->v;
		Sn.erase(it);Sn.insert({l,k-1,v});
		return Sn.insert({k,r,v}).first;
	}
public:
    odt(int _n=0):n(_n){
		Sn.insert({0,n,0});
	}
	void resize(int n){(*this)=odt(n);}
	void assign(int l,int r,T v){
		auto ir=split(r+1),il=split(l);
        assert((il->l)==l);
		Sn.erase(il,ir);Sn.insert({l,r,v});
	}
	void update(int l,int r,T v){
        auto ir=split(r+1),il=split(l);
        for(;il!=ir;++il) il->v+=v;
    }
    T range(int l,int r){
        auto ir=split(r+1),il=split(l);
        T res=0;
        for(;il!=ir;++il) res+=(il->r-il->l+1)*(il->v);
        return res;
    }
};
template<typename T>
class strange{
private:
    vector<T> tags,vals;int n;
public:
    void update(int l,int r,T v){
        tags[l]+=v;tags[r+1]-=v;
    }
    void assign(int l,int r,T v){
        T tgcnt=0;
        cir(i,0,l) vals[i]+=(tgcnt+=tags[i]);
        cir(i,l,r+1) vals[i]=v,(tgcnt+=tags[i]);
        cir(i,r+1,n+1) vals[i]+=(tgcnt+=tags[i]);
    }
    T range(int l,int r){
        assign(0,0,0);T res=0;
        cir(i,l,r+1) res+=vals[i];
        return res;
    }
    T&operator[](size_t x){return vals[x];}
    strange(int _n):n(_n+1),vals(_n+5),tags(_n+5){}
};
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,q,x;cin>>n>>q;odt<lint> cht(n+3);
    strange<lint> str(n+1);
    cir(i,1,n+1) cin>>x,cht.assign(i,i,x),str[i]=x;
    stringstream ss;int cnt=0;
    cir(i,0,q){
        int op;cin>>op;ss<<op<<' ';
        cnt+=(op==1);
        if(op==1||op==2){
            int l,r;lint v;cin>>l>>r>>v;
            ss<<l<<' '<<r<<' '<<v<<' ';
        }else{
            int l,r;cin>>l>>r;ss<<l<<' '<<r<<' ';
        }
    }
    if(cnt>=(n/3)*2){
        cir(i,0,q){
            int op;ss>>op;
            if(op==1){
                int l,r;lint v;ss>>l>>r>>v;
                str.update(l,r,v);
            }else if(op==2){
                int l,r;lint v;ss>>l>>r>>v;
                str.assign(l,r,v);
            }else{
                int l,r;ss>>l>>r;
                cout<<str.range(l,r)<<'\n';
            }
        }
    }else{
        cir(i,0,q){
            int op;ss>>op;
            if(op==1){
                int l,r;lint v;ss>>l>>r>>v;
                cht.update(l,r,v);
            }else if(op==2){
                int l,r;lint v;ss>>l>>r>>v;
                cht.assign(l,r,v);
            }else{
                int l,r;ss>>l>>r;
                cout<<cht.range(l,r)<<'\n';
            }
        }
    }
    return 0;
}