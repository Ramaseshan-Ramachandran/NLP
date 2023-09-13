//
//  ngram_info.cpp
//  test
//
//  Created by Ramaseshan Ramachandran on 05/08/23.
//

#include "../include/ngrams_info.hpp"


ngrams_info::ngrams_info(){
    
}
ngrams_info::~ngrams_info(){
    
}

ngrams_info::ngrams_info(const string& ng, int freq) : ngrams(ng), frequency(freq){
    
}
void ngrams_info::write(const vector<ngrams_info>& ngrams_data, const string& filename){
    std::ofstream out(filename);
    if (out.is_open()) {
        for (const auto& info : ngrams_data)
            out << info.ngrams << "," << info.frequency << "," <<  endl;
        out.close();
    } else {
        std::cerr << "Error opening the output file: " << filename << std::endl;
    }
}

