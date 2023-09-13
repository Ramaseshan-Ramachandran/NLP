/*
 * File: ngrams.hpp
 * Project: include
 * Created Date: Thursday, November 28th 2019, 11:21:49 pm
 * Author: Ramaseshan Ramachandran
 * -----
 * Last Modified: Friday, 29th November 2019 12:08:10 pm
 * Modified By: Ramaseshan Ramachandran
 * -----
 * Copyright (c) 2019 JCR Labz
 * blah
 * -----
 * HISTORY:
 * Date      	By	Comments
 * ----------	---	----------------------------------------------------------
 */

#ifndef __NGRAMS_HPP__

#define __NGRAMS_HPP__
#include <vector>
#include <string>
#include <regex>

#include "../include/utils.hpp"

using namespace std;
class ngrams {
protected:
    vector<vector<string>> _extract(int n, vector<string> const &v);
public:
    ngrams();
    ~ngrams();
    ngrams(bool stopwords = false);
    
    pair<vector<ngrams_info>, vector<ngrams_info>> ngrams_context_pair;

    pair<vector<ngrams_info>, vector<ngrams_info>> get(const string&, int);
    unordered_map<string, int> get_ngram_freq(const string& text, int n);
    vector<vector<string>> extract(int n, vector<string> const &v, bool padding=false);
    bool exists(const ngrams_info&, const std::vector<ngrams_info>&);
    vector<ngrams_info> update(const vector<ngrams_info>&, const vector<ngrams_info>&);
    bool remove_stopwords = true;
    
    pair<vector<ngrams_info>, vector<ngrams_info>> ngrams_and_context(const std::string&, int);
    const string get(long);
    vector<ngrams_info> search(const vector<ngrams_info>& ngrams_data, const string& search_prefix);

};
#endif // !__NGRAMS_HPP__
