#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
const vector<lint> M_Days{0,31,28,31,30,31,30,31,31,30,31,30,31};
struct Date{
    lint Ju,Y,M,D;
    //Julian Day;Year;Month;Day
};
ostream&operator<<(ostream&os,Date d){
    return (os<<d.D<<' '<<d.M<<' '<<abs(d.Y)<<(d.Y<0?" BC":""));
}
const int date_max=2.6e6+7;
vector<Date> DT(date_max);
const int InJulian=1582;
const int JulLastM=10,JulLastD=4;
bool IsLeap(lint x){
    if(x<0) return !((-x-1)%4);
    if(x<=InJulian) return !(x%4);
    return (!(x%400))||((!(x%4))&&x%100);
}
Date NewDay(const Date&st){
    Date Nd=st;Nd.Ju++,Nd.D++;
    if(st.Y==InJulian&&st.M==JulLastM&&st.D==JulLastD){
        //Delete Days;
        Nd.D=15;
    }
    if(Nd.D-(Nd.M==2&&IsLeap(Nd.Y))>M_Days[Nd.M]){
        Nd.D=1;
        if((++Nd.M)>12) Nd.Y+=1+(Nd.Y==-1),Nd.M=1;
    }
    return Nd;
}
int Ju16,Ju20;
Date solve(lint D){
    if(D<Ju16) return DT[D];
    int D400=Ju20-Ju16;
    Date ret=DT[Ju16+(D-Ju16)%D400];
    ret.Y+=400*((D-Ju16)/D400);
    return ret;
}
void init(){
    DT[0]={0,-4713,1,1};
    cir(i,1,date_max){
        auto&dt=DT[i];
        dt=NewDay(DT[i-1]);
        if(dt.Y==1600&&(!Ju16)) Ju16=dt.Ju;
        if(dt.Y==2000&&(!Ju20)) Ju20=dt.Ju;
    }
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    init();lint Q,d;cin>>Q;
    while(Q--) cin>>d,cout<<solve(d)<<endl;
    return 0;
}