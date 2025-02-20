#include<bits/stdc++.h>
using namespace std;

auto split(string s){
    auto id=0;
    while(isdigit(s.front())){
        (id*=10)+=(s.front()-'0');
        s.erase(s.begin());
    }
    return pair(id,s);
}

auto cf_URL(int cid,string pid){
    return format("codeforces.com/contest/{}/problem/{}",cid,pid);
}

auto luogu_URL(int cid,string pid){
    return format("luogu.com.cn/problem/CF{}{}",cid,pid);
}

auto open_edge(string s){
    return system(format("msedge.exe {}",s).data());
}

int main(int argc,char*argv[]){
    assert(argc>1);
    ifstream inf(argv[1]);
    string u;
    while(inf>>u){
        const auto[cid,pid]=split(u);
        open_edge(cf_URL(cid,pid));
        open_edge(luogu_URL(cid,pid));
    }
}
