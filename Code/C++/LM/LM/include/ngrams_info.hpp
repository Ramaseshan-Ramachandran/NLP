//
//  ngram_info.hpp
//  test
//
//  Created by Ramaseshan Ramachandran on 05/08/23.
//

#ifndef ngrams_info_hpp
#define ngrams_info_hpp

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <filesystem>
#include <fstream>


using namespace std;

class ngrams_info{
protected:
public:
    string ngrams="";
    int frequency=0;
//    long index=-1;
    ngrams_info();
    ~ngrams_info();
    ngrams_info(const string&, int freq);
    void write(const vector<ngrams_info>&, const string& filename);

};

#endif /* ngrams_info_hpp */
