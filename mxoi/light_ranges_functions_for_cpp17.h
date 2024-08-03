#include<algorithm>

#if __cplusplus < 202000L // C++14 / C++17

#if not defined(LIGHT_RANGES_FUNCTIONS_FOR_CPP17)

#define LIGHT_RANGES_FUNCTIONS_FOR_CPP17 1

namespace ranges{
    auto sort(auto&x){
        sort(x.begin(),x.end());
    }
    auto sort(auto&x,auto cmp){
        sort(x.begin(),x.end(),cmp);
    }
    auto nth_element(auto&x,auto it){
        nth_element(x.begin(),it,x.end());
    }
    auto nth_element(auto&x,auto it,auto cmp){
        nth_element(x.begin(),it,x.end(),cmp);
    }
    auto stable_sort(auto&x){
        stable_sort(x.begin(),x.end());
    }
    auto stable_sort(auto&x,auto cmp){
        stable_sort(x.begin(),x.end(),cmp);
    }
    auto unique(auto&x){
        return unique(x.begin(),x.end());
    }
    auto is_sorted(auto&x){
        return is_sorted(x.begin(),x.end());
    }
    auto is_sorted(auto&x,auto cmp){
        return is_sorted(x.begin(),x.end(),cmp);
    }
    auto reverse(auto&x){
        reverse(x.begin(),x.end());
    }
    auto iota(auto&x,auto w){
        iota(x.begin(),x.end(),w);
    }
    auto rotate(auto&x,auto it){
        rotate(x.begin(),it,x.end());
    }
    auto shuffle(auto&x){
        shuffle(x.begin(),x.end());
    }
    auto shuffle(auto&x,auto cmp){
        shuffle(x.begin(),x.end(),cmp);
    }
    auto accumulate(auto&x,auto w){
        return accumulate(x.begin(),x.end(),w);
    }
    auto accumulate(auto&x,auto w,auto f){
        return accumulate(x.begin(),x.end(),w,f);
    }
    auto count(auto&x,auto w){
        return count(x.begin(),x.end(),w);
    }
    auto find(auto&x,auto w){
        return find(x.begin(),x.end(),w);
    }
    auto lower_bound(auto&x,auto w){
        return lower_bound(x.begin(),x.end(),w);
    }
    auto lower_bound(auto&x,auto w,auto f){
        return lower_bound(x.begin(),x.end(),w,f);
    }
    auto upper_bound(auto&x,auto w){
        return upper_bound(x.begin(),x.end(),w);
    }
    auto upper_bound(auto&x,auto w,auto f){
        return upper_bound(x.begin(),x.end(),w,f);
    }
    auto max_element(auto&x){
        return max_element(x.begin(),x.end());
    }
    auto max_element(auto&x,auto f){
        return max_element(x.begin(),x.end(),f);
    }
    auto min_element(auto&x){
        return min_element(x.begin(),x.end());
    }
    auto min_element(auto&x,auto f){
        return min_element(x.begin(),x.end(),f);
    }
    auto fill(auto&x,auto w){
        fill(x.begin(),x.end(),w);
    }
    auto for_each(auto&x,auto f){
        for_each(x.begin(),x.end(),f);
    }
    
}

#endif

#endif
