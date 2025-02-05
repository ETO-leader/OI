#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;

ifstream inf("celeste.in");
ofstream ouf("celeste.out");
class fileio{
public:
    ~fileio(){
        inf.close();ouf.close();
    }
} use_fileio;

using pos_t=long double;
using move_t=long double;
using ptime_t=long double;
using point_t=complex<pos_t>;
using vector_t=complex<move_t>;

constexpr auto gx(point_t x){
    return real(x);
}
constexpr auto gy(point_t x){
    return imag(x);
}

class wall;
class player;
class gameCore;

enum playerStatu{hangInAir,touchdown,stickToWall};

class wall{
private:
    pos_t lefRange,rigRange,upRange,downRange;
public:
    void updateStatu(player&) const;
    pair<ptime_t,int> maxMoveTime(player&) const;
    wall(point_t,point_t);
};

class player{
private:
    int totalShiftCount,curShiftCount,jumpCount;
    playerStatu statu;
    bool isShift,isShiftDrop,isJumping;
    vector_t speed,shiftDirect,wallNorm;
    point_t u;
    friend class wall;
    friend class gameCore;
    int checkDirects(vector_t);
    void setJumpStatu();
    void unsetJumpStatu();
    void setShiftStatu(vector_t);
    void stopShift();
    void updateCounts();
public:
    void jump();
    void shift(vector_t);
    void checkShift();
    void normalMove(move_t);
    void drop();
    void setShiftDrop();
    void unsetShiftDrop();
    void move(ptime_t);
    void calculate();
    player(point_t);
};

class gameCore{
private:
    vector<wall> walls;
    player user;
    void updateStatu();
    void move();
public:
    void insertWall(wall);
    point_t operation(string);
    gameCore(point_t);
};

enum speedNumbers{
    normalDropSpeedMax=160,
    shiftDropSpeedMax=240,
    shiftOneDirectSpeed=240,
    shiftTwoDirectSpeed=169,
    stopShiftOneDirectSpeed=160,
    stopShiftTwoDirectSpeed=113,
};

namespace realOperations{

    static constexpr auto infTime=1e10l;
    static constexpr auto eps=1e-8l;

    constexpr auto same(auto x,auto y){
        return abs(x-y)<eps;
    }
    constexpr auto lesseqthan(auto x,auto y){
        return x<y+eps;
    }
    constexpr auto fitZero(auto&x){
        if(same(x,0)) x=0;
    }
    constexpr auto sign(auto x){
        return (!iszero(x))*(x<0?-1:1);
    }

}

namespace vectorOperations{

    auto operator*(vector_t x,move_t w){
        return x*vector_t(w,0);
    }

}

using namespace realOperations;
using namespace vectorOperations;

void wall::updateStatu(player&p) const{
    if(p.statu!=hangInAir) return;
    if(same(gy(p.u),this->upRange)&&lesseqthan(this->lefRange,gx(p.u))&&lesseqthan(gx(p.u),this->rigRange)){
        p.statu=touchdown;
        return;
    }
    if(same(gx(p.u),this->lefRange)||same(gx(p.u),this->rigRange)) [&](){
        if(!(lesseqthan(this->upRange,gy(p.u))&&lesseqthan(gy(p.u),this->downRange))) return;
        p.statu=stickToWall;
        p.wallNorm=(same(gx(p.u),this->lefRange)?vector_t(-1,0):vector_t(1,0));
    }();
}

pair<ptime_t,int> wall::maxMoveTime(player&p) const{
    auto res=pair(infTime,-1);
    for(auto dir=1;auto rg:{this->lefRange,this->rigRange}) [&](){
        dir*=-1;
        if((!sign(gx(p.speed)))||sign(gx(p.speed))==sign(dir)) return;
        auto tx=(rg-gx(p.u))/gx(p.speed);
        fitZero(tx);
        if(tx<0) return;
        const auto py=gy(p.u)+tx*gy(p.speed);
        if(lesseqthan(py,this->upRange)||lesseqthan(this->downRange,py)) return;
        res=min(res,pair(tx,0));
    }();
    for(auto dir=1;auto rg:{this->upRange,this->downRange}) [&](){
        dir*=-1;
        if((!sign(gy(p.speed)))||sign(gy(p.speed))==sign(dir)) return;
        auto ty=(rg-gy(p.u))/gy(p.speed);
        fitZero(ty);
        if(ty<0) return;
        const auto px=gx(p.u)+ty*gx(p.speed);
        if(lesseqthan(px,this->lefRange)||lesseqthan(this->rigRange,px)) return;
        res=min(res,pair(ty,1));
    }();
    return res;
}

wall::wall(point_t lu,point_t rd):
    lefRange(gx(lu)),rigRange(gx(rd)),
    upRange(gy(lu)),downRange(gy(rd)){}

void player::setJumpStatu(){
    this->speed=vector_t(gx(this->speed),-105);
    if(this->statu==stickToWall){
        const auto k=gx(wallNorm);
        this->speed=vector_t(gx(this->speed)+130*k,gy(this->speed));
    }
    --this->jumpCount;
    this->isJumping=true;
}

void player::unsetJumpStatu(){
    this->isJumping=false;this->jumpCount=0;
}

void player::jump(){
    if(this->isShift) return;
    if(this->statu==hangInAir&&this->jumpCount){
        return this->setJumpStatu();
    }
    if(this->statu==touchdown){
        this->jumpCount=12;
        return this->setJumpStatu();
    }
    if(this->statu==stickToWall){
        this->jumpCount=1;
        return this->setJumpStatu();
    }
    this->unsetJumpStatu();
}

void player::setShiftStatu(vector_t dir){
    isShift=true;
    this->shiftDirect=dir;
    if(this->curShiftCount==10){
        if(this->checkDirects(dir)==1) this->speed=dir*shiftOneDirectSpeed;
        else this->speed=dir*shiftTwoDirectSpeed;
    }
    --this->curShiftCount;
}

void player::updateCounts(){
    if((!this->isJumping)&&(!this->isShift)){
        this->curShiftCount=0;this->jumpCount=0;
    }
}

void player::checkShift(){
    if(this->curShiftCount) this->setShiftStatu(this->shiftDirect);
    else if(this->isShift) this->stopShift();
}

void player::shift(vector_t dir){
    if(this->isShift) return;
    assert(this->totalShiftCount);
    --this->totalShiftCount;
    this->shiftDirect=dir;
    this->curShiftCount=10;
    this->setShiftStatu(dir);
}

int player::checkDirects(vector_t x){
    return (int)(!iszero(gx(x)))+(!iszero(gy(x)));
}

void player::stopShift(){
    this->isShift=false;
    if(this->checkDirects(this->shiftDirect)==1){
        this->speed=this->shiftDirect*stopShiftOneDirectSpeed;
    }else{
        this->speed=this->shiftDirect*stopShiftTwoDirectSpeed;
    }
}

void player::normalMove(move_t k){
    if(this->isShift) return;
    const auto p=sign(gx(this->speed));
    if(iszero(k)){
        const auto lasSpeedX=gx(this->speed);
        const auto deltaSpeed=((this->statu==touchdown)?16.7l:10.8l);
        auto newSpeedX=gx(this->speed)-deltaSpeed*p;
        if(sign(lasSpeedX)!=sign(newSpeedX)) newSpeedX=0;
        this->speed=vector_t(newSpeedX,gy(this->speed));
    }else if((p*k>0)&&lesseqthan(90+eps,abs(gx(this->speed)))){
        const auto lasSpeedX=gx(this->speed);
        const auto deltaSpeed=((this->statu==touchdown)?6.7l:4.3l);
        auto newSpeedX=gx(this->speed)-deltaSpeed*k;
        if(sign(lasSpeedX-90*k)!=sign(newSpeedX-90*k)) newSpeedX=90*k;
        this->speed=vector_t(newSpeedX,gy(this->speed));
    }else{
        const auto lasSpeedX=gx(this->speed);
        const auto deltaSpeed=((this->statu==touchdown)?45.0l:30.0l);
        auto newSpeedX=gx(this->speed)+deltaSpeed*k;
        if(sign(lasSpeedX-90*k)!=sign(newSpeedX-90*k)) newSpeedX=90*k;
        this->speed=vector_t(newSpeedX,gy(this->speed));
    }
}

void player::drop(){
    if(this->isShift) return;
    if(this->statu==touchdown) return;
    const auto deltaSpeedY=(this->statu==hangInAir?15.0l:1.9l);
    const auto limit=(this->isShiftDrop?shiftDropSpeedMax:normalDropSpeedMax);
    this->speed=vector_t(gx(this->speed),min<move_t>(gy(this->speed)+deltaSpeedY,limit));
}

void player::setShiftDrop(){
    this->isShiftDrop=true;
}

void player::unsetShiftDrop(){
    this->isShiftDrop=false;
}

void player::move(ptime_t t){
    this->u+=(this->speed*t);
}

void player::calculate(){
    if(this->statu==touchdown) this->totalShiftCount=2;
}

player::player(point_t ux):
    u(ux),
    totalShiftCount(2),curShiftCount(0),jumpCount(0),
    statu(hangInAir),
    isJumping(false),isShift(false),isShiftDrop(false),
    shiftDirect(vector_t(0,0)),
    speed(vector_t(0,0)),
    wallNorm(vector_t(0,0)){}

void gameCore::updateStatu(){
    this->user.statu=hangInAir;
    this->user.checkShift();
    for(auto&x:this->walls) x.updateStatu(this->user);
    this->user.updateCounts();
}

void gameCore::move(){
    auto mv=pair(1.0l,-1);
    for(auto&x:this->walls) mv=min(mv,x.maxMoveTime(this->user));
    this->user.move(mv.first);
    if(!mv.second) this->user.speed=vector_t(0,gy(this->user.speed));
    if(mv.second==1) this->user.speed=vector_t(gx(this->user.speed),0);
    this->user.calculate();
}

point_t gameCore::operation(string str){
    const auto exists=[&](const char c){
        return (bool)(count(str.begin(),str.end(),c));
    };
    if(!exists('K')) this->user.unsetJumpStatu();
    this->updateStatu();
    auto moved=false;
    if(exists('A')) this->user.normalMove(-1),moved=true;
    if(exists('D')) this->user.normalMove(1),moved=true;
    if(!moved) this->user.normalMove(0);
    if(exists('S')) this->user.setShiftDrop();
    this->user.drop();
    if(exists('K')) this->user.jump();
    if(exists('L')) [&](){
        if((!this->user.isShift)&&(!this->user.totalShiftCount)) return;
        auto movdir=vector_t(0,0);
        if(exists('A')) movdir+=vector_t(-1,0);
        if(exists('D')) movdir+=vector_t(1,0);
        if(exists('W')) movdir+=vector_t(0,-1);
        if(exists('S')) movdir+=vector_t(0,1); 
        this->user.shift(movdir);
    }();
    const auto lu=this->user.u;
    this->move();
    if(exists('S')) this->user.unsetShiftDrop();
    return this->user.u;
}

void gameCore::insertWall(wall x){
    this->walls.push_back(x);
}

gameCore::gameCore(point_t u):user(u){}

int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int m;inf>>m;vector<pair<point_t,point_t>> px(m);
    for(auto&[lu,rd]:px){
        pos_t xl,yl,xr,yr;inf>>xl>>yl>>xr>>yr;
        lu=point_t(xl,yl);rd=point_t(xr,yr);
    }
    pos_t ux,uy;inf>>ux>>uy;
    gameCore game(point_t(ux,uy));
    for(auto&[lu,rd]:px) game.insertWall(wall(lu,rd));
    int q;inf>>q;
    ouf<<fixed<<setprecision(15);
    cir(i,0,q){
        string s;inf>>s;
        const auto pos=game.operation(s);
        ouf<<gx(pos)<<' '<<gy(pos)<<'\n';
    }
    return 0;
}
