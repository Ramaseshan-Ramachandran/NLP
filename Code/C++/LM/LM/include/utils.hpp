//
//  utils.hpp
//  test
//
//  Created by Ramaseshan Ramachandran on 05/08/23.
//

#ifndef utils_hpp
#define utils_hpp

#include <string>
#include <filesystem>
#include <sstream>
#include <fstream>
#include "../include/constants.hpp"
#include "../include/ngrams_info.hpp"

using namespace std;
namespace fs = std::filesystem;

class utils{
public:
    utils();
    ~utils();
    bool is_directory(const string&);
    
//    vector<string> tokenize(const string&, bool);
    
    string to_lower(const string& str) ;
//    bool is_bigger(const ngrams_info& a, const ngrams_info& b);
    bool is_delimiter(char c);
    

    vector<string> tokenize(const string& text, bool remove_stopwords=false);
    bool is_stopword(const string& word, const vector<string>& sw);
    
    vector<ngrams_info> read_csv(const string&);
    bool starts_with(const string& str, const string& sub_string);
    
    template <typename T>
    static bool is_bigger(const T& a, const T& b) {
            return a.frequency > b.frequency;
    }
    
    const string get_context(const string& str){
        const string& sub = str.substr(0, str.rfind(' '));
        return sub;
    }
    template <typename T>
    static vector<T> most_common(vector<T> all_entries, const int count) {
        // Get the top count number of entries.
        vector<T> top_entries;
        //Make sure that number of entries is more than the count, else initialize num_entries usinf count
        //This ensures that the push_back stops at whichever is lower
        int num_entries = size(all_entries);
        if (num_entries > count) {
            num_entries = count;
        }
        if (size(all_entries) > 0 ){
            for (int i = 0; i < num_entries; i++) {
                top_entries.push_back(all_entries[i]);
            }
        }
        return top_entries;
    }
};
#endif /* utils_hpp */
