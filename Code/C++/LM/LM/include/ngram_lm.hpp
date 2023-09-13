//
//  ngram_lm.hpp
//  test
//
//  Created by Ramaseshan Ramachandran on 07/08/23.
//

#ifndef ngram_lm_hpp
#define ngram_lm_hpp

#include "../include/utils.hpp"

using namespace std;

class probability{
public:
    string ngrams;
    float prob;
    probability(const string& str, float p):ngrams(str),prob(p){}
};

class ngram_lm{
public:
    ngram_lm();
    ~ngram_lm();
    
    const vector<probability> probability_distribution(const string& str,
                                                       vector<ngrams_info>& ngs_info,
                                                       vector<ngrams_info>& context_list,
                                                       int count=10);
    void build_model();
    const string& get_content(const string& path);
    void predict_next_word();

};
#endif /* ngram_lm_hpp */
