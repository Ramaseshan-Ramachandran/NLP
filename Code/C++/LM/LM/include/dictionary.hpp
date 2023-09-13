/*
 * File: dictionary.hpp
 * Project: include
 * Created Date: Tuesday, November 26th 2019, 8:28:41 pm
 * Author: Ramaseshan Ramachandran
 * -----
 * Last Modified: Thursday, 28th November 2019 8:42:57 pm
 * Modified By: Ramaseshan Ramachandran
 * -----
 * Copyright (c) 2019 JCR Labz
 * blah
 * -----
 * HISTORY:
 * Date      	By	Comments
 * ----------	---	----------------------------------------------------------
 */



#ifndef __DICTIONARY_HPP__
#define __DICTIONARY_HPP__
#include <string>
#include <unordered_map>
#include <utility>
#include <map>
#include <vector>

using namespace std;

class dictionary {
protected:
    std::unordered_map<std::string,int> tf_p;
public:
    dictionary();
    ~dictionary();
    pair<string,int> tf_pair;
    void add(pair<string,int> tfp);
    bool find(pair<string,int> tfp);
    map<string,int> freq_dist(vector<string> const &t, int cut_off);
    map<string,int> freq_dist(vector<string> tokens);
    void write(string filename);

};
#endif // !__DICTIONARY_HPP__
