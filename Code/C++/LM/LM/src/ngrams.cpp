/*
 * File: ngrams.cpp
 * Project: src
 * Created Date: Thursday, November 28th 2019, 11:21:48 pm
 * Author: Ramaseshan Ramachandran
 * -----
 * Last Modified: Friday, 29th November 2019 12:27:31 pm
 * Modified By: Ramaseshan Ramachandran
 * -----
 * Copyright (c) 2019 JCR Labz
 * blah
 * -----
 * HISTORY:
 * Date      	By	Comments
 * ----------	---	----------------------------------------------------------
 */

#include "../include/ngrams.hpp"
#include <list>
#include <algorithm>
#include "../include/utils.hpp"
template <typename T>
bool is_bigger(const T& a, const T& b) {
        return a.frequency < b.frequency;
}

bool is_punct(char c) {
    // Define your criteria for punctuation characters here
    return std::ispunct(static_cast<unsigned char>(c));
}
ngrams::ngrams()
{
}
ngrams::ngrams(bool del_stopwords){
    remove_stopwords = del_stopwords;
}

ngrams::~ngrams()
{
}

vector<vector<string>> ngrams::_extract(int n, vector<string> const &v)
{
    vector<vector<string>> ngrams_array;
    vector<string> vec;
    auto first = v.begin();
    auto last = v.end();
    for (auto i = first; i < (last - n+1); i++)
    {
            vec.assign(i, i + n);
            ngrams_array.push_back(vec);
    }
    return ngrams_array;
}

vector<vector<string>> ngrams::extract(int n, vector<string> const &content,bool padding)
{
    vector<string> dest;
    if ( !padding )
        return _extract(n,content);
    else
    {
        //insert markers
        for (int i= 0; i < n-1; i++)
            dest.push_back(string("<S>"));
        move(content.begin(), content.end(), back_inserter(dest));
        for (int i= 0; i < n-1; i++)
            dest.push_back(string("<S>"));
    }  
    return _extract(n,dest);  
}


// Function to check if ngrams_info already exists in the vector based on ngrams content
bool ngrams::exists(const ngrams_info& info, const std::vector<ngrams_info>& vector) {
    return std::any_of(vector.begin(), vector.end(), [&](const ngrams_info& existing) {
        return existing.ngrams == info.ngrams;
    });
}

// Function to merge and update two vectors of ngrams_info
vector<ngrams_info> ngrams::update(const vector<ngrams_info>& vector1, const std::vector<ngrams_info>& vector2) {
    std::vector<ngrams_info> merged_vector = vector1;

    for (const ngrams_info& info : vector2) {
        if (exists(info, merged_vector)) {
            // If ngrams_info already exists in mergedVector, update its frequency
            auto it = std::find_if(merged_vector.begin(), merged_vector.end(), [&](const ngrams_info& existing) {
                return existing.ngrams == info.ngrams;
            });
            if (it != merged_vector.end()) {
                it->frequency += info.frequency;
            }
        } else {
            // If NGramsInfo does not exist in mergedVector, add it
            merged_vector.push_back(info);
        }
    }

    return merged_vector;
}

unordered_map<string, int> ngrams::get_ngram_freq(const string& text, int n){

    unordered_map<string, int> local_frequencies;

    vector<ngrams_info> result;
    utils u;
    unordered_map<string, int> ngram_token_map;
    unordered_map<string, int> context_token_map;
    // Remove punctuation and split text into words
    std::string delimiters = "',.\"%?()[]!;:-_“‘–";//".,!%?\n\";

    std::istringstream iss(text);
    std::vector<std::string> words(
        std::istream_iterator<std::string>{iss},
        std::istream_iterator<std::string>()
    );
    
//    for (char delimiter : delimiters) {
//        words.erase(std::remove(words.begin(), words.end(), delimiter), words.end());
//    }
    
    // Generate ngrams and count frequencies
    const int ngram_size = n; // Change this to the desired ngram size
    for (size_t i = 0; i <= words.size() - ngram_size; ++i) {
        std::string ngram;
        for (int j = 0; j < ngram_size; ++j) {
            ngram += words[i + j];
            if (j < ngram_size - 1) {
                ngram += " ";
            }
        }
        

        ++local_frequencies[ngram];
    }
    return local_frequencies;
}

pair<vector<ngrams_info>, vector<ngrams_info>> ngrams::get(const string& text, int n){
    
    vector<ngrams_info> result;
    utils u;
    unordered_map<string, int> ngram_token_map;
    unordered_map<string, int> context_token_map;
    // Remove punctuation and split text into words
    std::string delimiters = "',.\"%?()[]!;:-_“‘–";//".,!%?\n\";

    std::istringstream iss(text);
    std::vector<std::string> words(
        std::istream_iterator<std::string>{iss},
        std::istream_iterator<std::string>()
    );
    
    // Remove punctuation marks from each token
        for (std::string& word : words) {
            word.erase(std::remove_if(word.begin(), word.end(), is_punct), word.end());
        }
    
    // Generate n-grams and their frequencies
    
    const int ngram_size = n; // Change this to the desired ngram size
    for (size_t i = 0; i <= words.size() - ngram_size; ++i) {
        std::string ngram;
        for (int j = 0; j < ngram_size; ++j) {
            ngram += words[i + j];
            if (j < ngram_size - 1) {
                ngram += " ";
            }
        }
//        for (char delimiter : delimiters) {
//                words.erase(std::remove(words.begin(), words.end(), delimiter), words.end());
//        }
        if (i % 1000 == 0 ){
            cout << '\r' << i/1000 << "X1K Tokens processed ";
        }

        string context = ngram.substr(0, ngram.find_last_of(' '));

        ngram_token_map[ngram]++;
        context_token_map[context]++;
    }

    // Convert the tokenMap to a vector of TokenInfo objects
    vector<ngrams_info> ng_info;
    for (const auto& entry : ngram_token_map) {
        ng_info.emplace_back(ngrams_info({entry.first}, entry.second));
    }
    vector<ngrams_info> contexts_info;
    for (const auto& entry : context_token_map) {
        contexts_info.emplace_back(ngrams_info({entry.first}, entry.second));
    }
    // Sort the vector using the custom comparison function
    std::sort(ng_info.begin(), ng_info.end(), utils::is_bigger<ngrams_info>);
    std::sort(contexts_info.begin(), contexts_info.end(), utils::is_bigger<ngrams_info>);
    return make_pair(ng_info, contexts_info);
}

const string ngrams::get(long idx){
    //get the ngrams given the index from the list of ngrams
    string ng;
    return ng;
}

vector<ngrams_info> ngrams::search(const vector<ngrams_info>& ngrams_data, const string& search_prefix){
    vector<ngrams_info> results;
    utils u;
    
    for (const ngrams_info& ngram : ngrams_data) {
        if (u.starts_with(search_prefix, ngram.ngrams)) {
            results.push_back(ngram);
        }
            //else if (ngram.ngrams.compare(0, search_prefix.length(), search_prefix) > 0) {
//            // The list is sorted, so break if the prefix condition is no longer met
//            break;
//        }
    }
    return results;
}
//int update_test() {
//    // Sample vectors of NGramsInfo
//    vector<ngrams_info> vector1 = {
//        ngrams_info("hello world", 5),
//        ngrams_info("foo bar" , 3)
//    };
//
//    vector<ngrams_info> vector2 = {
//        ngrams_info( "hello world", 7),
//        ngrams_info("bazqux", 2)
//    };
//
//    // Merge the two vectors
//    ngrams ng(false);
//    vector<ngrams_info> merged_vector = ng.update(vector1, vector2);
//
//    // Print the merged result
//    for (const ngrams_info& info: merged_vector) {
//        std::cout << "NGrams: ";
//        std::cout << info.ngrams << " ";
//        std::cout << "Frequency: " << info.frequency << std::endl;
//    }
//
//    return 0;
//}
