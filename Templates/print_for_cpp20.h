#include<format>
#include<iostream>

#ifndef __glibcxx_print

#ifndef ETOEXTLIB_PRINT

#define ETOEXTLIB_PRINT 1

namespace std{
    template<typename... _Args>
    auto print(ostream&os,const char*fmt,_Args... args){
        os<<vformat(std::string_view(fmt),std::make_format_args(args...));
    }
    template<typename... _Args>
    auto println(ostream&os,const char*fmt,_Args... args){
        os<<vformat(std::string_view(fmt),std::make_format_args(args...))<<'\n';
    }
    template<typename... _Args>
    auto print(const char*fmt,_Args... args){
        cout<<vformat(std::string_view(fmt),std::make_format_args(args...));
    }
    template<typename... _Args>
    auto println(const char*fmt,_Args... args){
        cout<<vformat(std::string_view(fmt),std::make_format_args(args...))<<'\n';
    }
}

#endif

#endif
