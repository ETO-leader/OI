#include<bits/stdc++.h>

#if not defined(__GRADER_CPP)

#define __GRADER_CPP 1

#if defined FILE_LOG
    std::ofstream Info("grader.log");
#else
    #define Info std::clog
#endif

extern void Coins();

std::string col;

extern std::vector<bool> Relation(std::vector<std::pair<int,int>> x){
    const int n=x.size();
    std::vector<bool> res(n);
    for(auto c=-1;auto&[a,b]:x){
        res[++c]=(col[a]==col[b]);
    }
    return res;
}

extern void Answer(){
    
}

int main(){
    std::ios::sync_with_stdio(false),std::cin.tie(0);
    int T;std::cin>>T;
    while(T--){
        std::cin>>col;
    }
    return 0;
}

#endif