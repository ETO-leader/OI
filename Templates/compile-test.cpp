#include"print_for_cpp20.hpp"
#include<numbers>

int main(){
    std::println("{}, to {}","TEST","stdout");
    std::print("GCC Version {:.1f}\n",14.0);
    std::println(std::cout,"Certain {} test","stream");
    std::print(std::cout,"PI={:.12f}\n",std::numbers::pi);
}
