#include <string>
#include <vector>
#include <cstdint>
#include <type_traits>
#include <algorithm>
#include <set>

#include "timing_assist.hpp"

template <typename Container>
auto constant_complexity(Container&& container) {
    return container[0];
}

template <typename Container>
auto quadratic_complexity(Container&& container) {
    for (std::size_t i = 0; i < container.size(); ++i) {
        for (std::size_t j = 0; j < container.size(); ++j) {
            container[j] = container[i];
        }
    }
}

template <typename Container>
auto my_sort(Container&& container) {
    for (std::size_t i = 1; i < container.size(); ++i) {
        for (std::size_t j = 1; j < container.size(); ++j) {
            if (container[j - 1] < container[j]) {
                std::swap(container[j - 1], container[j]);
            }
        }
    }
}

/*void func_1(){
    double value = 2.034;
    std::vector<double> v(10);
    for(int i = 0; i < v.size(); ++i){
        v.push_back(value += value - 0.233);
    }
}*/

int main(int argc, char** argv) {

    if (2 != argc) {
        std::cout << "Incorrect number of arguments" << std::endl;
        return 0;
    }

    std::vector<int> my_vec(std::stoll(argv[1]));

    //time_and_print("O(1)", constant_complexity<decltype(my_vec)&>, my_vec);          //decltype ??
    //time_and_print("O(1)", constant_complexity<decltype(my_vec)>, std::vector<int>{5});

    //time_and_print("O(N)", std::fill<decltype(my_vec.begin()), int>, my_vec.begin(),
    //    my_vec.end(), 20);

    //for (std::size_t i = 0; i < my_vec.size(); ++i) {
    //    my_vec[i] = 35635ll * i % 8321283ll;
    //}

    time_and_print("O(N)", std::fill<decltype(my_vec.begin()), int>, my_vec.begin(),
        my_vec.end(), 20);
    //time_and_print("O(N * Log(N))", std::sort<decltype(my_vec.begin())>, my_vec.begin(),
    //    my_vec.end());

    //for (std::size_t i = 0; i < my_vec.size(); ++i) {
    //    my_vec[i] = 35635ll * i % 8321283ll;
    //}

    //time_and_print("O(N * N)", my_sort<decltype(my_vec)&>, my_vec);

    return 0;
}
