#include<stdint.h>
#include"testlib.h"
#include"grader-lib.h"

int nowLang;

int succeedCount;

extern int language(int langid){
    if(langid==nowLang) ++succeedCount;
    return nowLang;
}

extern void excerpt(int*);

const int qNumber=10000;

int main(int argc,char*argv[]){
    registerTestlibCmd(argc,argv);
    for(int i=0;i<qNumber;++i){
        const int lang=rnd.next(4);
        const int siz=Articals[lang].size();
        const int Left=rnd.next(0,siz-100);
        nowLang=lang;
        excerpt(std::vector<int>(Articals[lang].begin()+Left,Articals[lang].begin()+Left+100).data());
    }
    int score=round(succeedCount*1.0/qNumber*114);
    // if(score>99) quitf(_ok,"accepted.\n");
    /*else */if(score>0) quitf(_pc(score)," partically correct.\n");
    else quitf(_wa,"wrong answer.\n");
}
