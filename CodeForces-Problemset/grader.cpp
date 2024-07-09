#include<bits/stdc++.h>

#if not defined(__GRADER_H)

#define __GRADER_H 1

#if defined FILE_LOG
    std::ofstream Info("grader.log");
#else
    #define Info std::clog
#endif

extern void findTreasure();

const std::string
    Closer="QwQ",
    Further="QAQ",
    Same="TAT",
    Found="Meow!",
    NotFound="^V^";

int lasx=-1,lasy=-1,ansx,ansy;

static constexpr double eps=1e-10;

double dist(int x,int y){
    return sqrt(1ll*(x-ansx)*(x-ansx)+1ll*(y-ansy)*(y-ansy));
}

bool same(double a,double b){
    return fabs(a-b)<eps;
}

bool Correct=false;
int Askcnt=0;

std::string Ask(int x,int y){
    if(Correct) return Found;
    Info<<"Ask "<<x<<' '<<y<<", Result=";
    ++Askcnt;
    if(ansx==x&&ansy==y) return Info<<"Found.\n",Correct=true,Found;
    if(lasx<0&&lasy<0) return lasx=x,lasy=y,Info<<"NotFound.\n",NotFound;
    const auto lasdis=dist(lasx,lasy);
    const auto nwdis=dist(x,y);
    lasx=x;lasy=y;
    if(same(lasdis,nwdis)) return Info<<"Same.\n",Same;
    if(lasdis<nwdis) return Info<<"Further.\n",Further;
    return Info<<"Closer.\n",Closer;
}

extern void findTreasure();

int main(){
    std::ios::sync_with_stdio(false),std::cin.tie(0);
    std::cin>>ansx>>ansy;
    findTreasure();
    if(!Correct) std::cerr<<"Not Correct.\n",exit(3);
    std::cerr<<"Correct, ask time = "<<Askcnt<<'\n';
    return 0;
}

#endif