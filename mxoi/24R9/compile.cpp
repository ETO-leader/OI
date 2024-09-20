#include<set>
#include<string>

const std::string compiler=" g++ ";

int main(int argc,char*argv[]){
    const auto fn=argv[1];
    std::set<std::string> args;
    for(int i=2;i<argc;++i){
        args.insert(argv[i]);
    }
    std::string santizer="";
    std::string outfile=" a.out ";
    std::string version=" -std=c++26 ";
    if(args.contains("-fs")) santizer=" -fsanitize=address,undefined -g ";
    if(args.contains("-o")) outfile=fn;
    if(args.contains("-c++98")) version=" -std=c++98 ";
    if(args.contains("-c++03")) version=" -std=c++03 ";
    if(args.contains("-c++11")) version=" -std=c++11 ";
    if(args.contains("-c++14")) version=" -std=c++14 ";
    if(args.contains("-c++17")) version=" -std=c++17 ";
    if(args.contains("-c++20")) version=" -std=c++20 ";
    if(args.contains("-c++23")) version=" -std=c++23 ";
    if(args.contains("-c++26")) version=" -std=c++26 ";
    return system((compiler+fn+".cpp"+" -Wall -Wextra -Wshadow -Wconversion -W "+santizer+" -o "+outfile+" -O2 "+version).data());
}