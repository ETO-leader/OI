#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
//第一维存 "xy",即有一条 x->y 的边
map<string,int> cnt;
//rev[str1] -> str1 的反向,如 rev["ab"]="ba"
//chg[str1] -> str1 的转换,即 chg["ab"]="bc"
//rec[str1] -> str1 转换后可删的边,即 rec["ab"]="bc"
map<string,string> rev,chg,rec;
//操作的人 id
map<string,vector<int>> idx;
//转换无法进行 "ab"->"ba" 操作的状态
//返回增加的值
int change(string s,stringstream&sout){
    int cnx=min(cnt[s],cnt[rec[s]]);
    cnt[chg[s]]+=cnx;cnt[s]-=cnx;cnt[rec[s]]-=cnx;
    cir(i,0,cnx){
        sout<<idx[s].back()<<' '<<s[0]<<' '
            <<idx[rec[s]].back()<<' '<<s[1]<<'\n';
        auto rex=idx[rec[s]].back();
        idx[s].pop_back();idx[rec[s]].pop_back();
        idx[chg[s]].push_back(rex);
    }
    return cnx;
}
//初始化 rev,rec,chg
void init(){
    rev["wi"]="iw";rev["iw"]="wi";
    rev["wn"]="nw";rev["nw"]="wn";
    rev["in"]="ni";rev["ni"]="in";
    rec["wi"]="in";rec["iw"]="wn";
    rec["wn"]="ni";rec["nw"]="wi";
    rec["in"]="nw";rec["ni"]="iw";
    chg["wi"]="wn";chg["iw"]="in";
    chg["wn"]="wi";chg["nw"]="ni";
    chg["in"]="iw";chg["ni"]="nw";
}
void clear(){
    idx.clear();cnt.clear();
}
//读入，初始化
void scan(int n){
    cir(i,0,n){
        string s;cin>>s;
        int _w=0,_i=0,_n=0;
        for(auto&j:s)
            (j=='w'?_w++:(j=='n'?_n++:_i++));
        if(_w>1){
            if(_i<1) cnt["wi"]++,idx["wi"].push_back(i+1);
            if(_n<1) cnt["wn"]++,idx["wn"].push_back(i+1);
        }
        if(_i>1){
            if(_w<1) cnt["iw"]++,idx["iw"].push_back(i+1);
            if(_n<1) cnt["in"]++,idx["in"].push_back(i+1);
        }
        if(_n>1){
            if(_i<1) cnt["ni"]++,idx["ni"].push_back(i+1);
            if(_w<1) cnt["nw"]++,idx["nw"].push_back(i+1);
        }
    }
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;init();
    while(T--){
        int n,ans=0;cin>>n;clear();
        scan(n);
        stringstream sout;
        while(true){
            bool brk=true;
            for(auto&i:cnt){
                auto mn=min(i.second,cnt[rev[i.first]]);
                ans+=mn;i.second-=mn;cnt[rev[i.first]]-=mn;
                cir(j,0,mn){
                    sout<<idx[i.first].back()<<' '<<i.first[0]<<' '
                        <<idx[rev[i.first]].back()<<' '<<i.first[1]<<'\n';
                    idx[i.first].pop_back();
                    idx[rev[i.first]].pop_back();
                }
            }
            for(auto&i:cnt) ans+=change(i.first,sout);
            for(auto&i:cnt) brk&=(!i.second);
            if(brk) break;
        }
        cout<<ans<<'\n'<<sout.str();
    }
    return 0;
}