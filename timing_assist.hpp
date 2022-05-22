#ifndef __TIMING_ASSISTANCE_HPP__
#define __TIMING_ASSISTANCE_HPP__

#include <cmath>
#include <cstdint>
#include <chrono>
#include <iostream>
#include <algorithm>
#include <vector>


constexpr auto min_n_run = 100;
constexpr double min_exec_time = 0.1;

struct timing_results {
    double mean_time;
    double std_dev;
    std::size_t n_run;
};

template <typename Func, typename ... Args>
auto timing_function(Func&& func, Args&&... args) {
    double mean = 0.0;             
    double std_dev = 0.0;
    double mean_first = 0.0;
    std::vector<double> my_vec;
    // Perform multiple runs to get more stable result
    for (size_t i = 0; i < min_n_run; ++i) {
        auto start = std::chrono::steady_clock::now();
        // Function call
        std::forward<Func>(func) (std::forward<Args>(args)...); //Func(args);     
        auto end = std::chrono::steady_clock::now();							
        auto time_elapsed = std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();
        my_vec.push_back(time_elapsed);
    }
    //sortting my_vec & creating new vector my_vec_2
    std::sort(my_vec.begin(), my_vec.end());
    int _10_percent = my_vec.size() * 0.1;
    std::vector<double> my_vec_2(0);
    //inserting data from my_vec to my_vec_2
    for (int i = 0; i < _10_percent * 5; ++i){
        my_vec_2.push_back(my_vec[i + _10_percent]);     
    }						
    //calculation mean time & std_dev
    for (int i = 0; i < _10_percent * 5; ++i){
        mean += my_vec_2[i];
        std_dev += my_vec_2[i] * my_vec_2[i];
    }
    // Calculate statistics
    size_t run_qty = _10_percent * 5;
    mean /= run_qty;
    std_dev -= run_qty * mean * mean;
    std_dev /= run_qty - 1;
    std_dev = std::sqrt(std_dev);
    
    timing_results results = {mean, std_dev, run_qty};
    return results;
}

template <typename Printable, typename Res>
auto print_timing_res(Printable&& test_name, Res&& results) {
    std::cout << test_name << std::endl << "Average time: " << results.mean_time << std::endl <<
        "Instability level: " << (results.std_dev / results.mean_time * 100) << " %" << std::endl << std::endl;
}

template <typename Printable, typename Func, typename ... Args>
auto time_and_print(Printable&& test_name, Func&& func, Args&& ... args) {
    auto res = timing_function(std::forward<Func>(func), std::forward<Args>(args)...);
    print_timing_res(test_name, res);
}

#endif // __TIMING_ASSISTANCE_HPP__





/*0.0037

10% = 0.0004

0.0037 - 0.0004 + 0.= 0.0033
0.0037 + 0.0004 = 0.0041*/
