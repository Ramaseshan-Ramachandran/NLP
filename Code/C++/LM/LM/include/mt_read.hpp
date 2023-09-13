//
//  mt_read.hpp
//  test
//
//  Created by Ramaseshan Ramachandran on 05/08/23.
//

#ifndef mt_read_hpp
#define mt_read_hpp

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <thread>
#include <algorithm>
#include <mutex>
#include <filesystem>
#include "../include/utils.hpp"
#include "../include/constants.hpp"

namespace fs = std::filesystem;
using namespace std;

class mt_read{
protected:
    std::mutex progressMutex;
    int files_count = 0;
    int number_of_files_processed = 0;
    std::mutex c_mutex;
    std::string content;
    void update_progress();
    void process_file(const std::string&);
    void progress_bar(double, double);
public:
    mt_read();
    ~mt_read();
    const string& read(const string&);
};
#endif /* mt_read_hpp */
