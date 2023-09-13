//
//  utils.cpp
//  test
//
//  Created by Ramaseshan Ramachandran on 05/08/23.
//

#include "../include/utils.hpp"

utils::utils(){
    
}
utils::~utils(){
    
}
string utils::to_lower(const string& str) {
    string result;
    for (char c : str) {
        result += tolower(c);
    }
    return result;
}

bool utils::is_delimiter(char c){
    return default_delimiters.find(c) != std::string::npos;
}

bool utils::is_directory(const string& path){
    // Check if the path exists
    if (!fs::exists(path)) {
        return false;
    }
    // Check if it represents a directory
    if (fs::is_directory(path)) {
        return true;
    } else {
        return false;
    }
    return false;
}




vector<string> utils::tokenize(const string& text, bool remove_stopwords) {
    vector<string> tokens;
    istringstream iss(text);
    vector<string> sw = stopwords;
    std::string delimiters = "',.\"%?()[]!;:-_“‘–";//".,!%?\n\";

    string token;
    while (getline(iss, token, ' ')) {
        // Check if the token ends with a delimiter
        
        token.erase(std::remove_if(token.begin(), token.end(),
                                   [&delimiters](char c) {
            return delimiters.find(c) != std::string::npos;}),
                    token.end());
//        if (!token.empty() && is_delimiter(token.back())) {
//            // Remove the last character from the token if it's a delimiter
//            token.pop_back();
//        }
        // Replace each removed delimiter with a space
        for (char &c : token) {
            if (delimiters.find(c) != std::string::npos) {
                c = ' ';
            }
        }
        // Add the token to the vector (ignoring empty tokens)
            if (!token.empty() ) {
//                if (!is_stopword(token, sw))
                    tokens.push_back(token);
            }
    }
//    cout << tokens.size() << " Tokens processed" << endl;
    return tokens;
}

bool utils::is_stopword(const string& word, const vector<string>& sw) {
    auto it = find(sw.begin(), sw.end(), word);
    if (it != sw.end())
        return true;
    else
        return false;
    return false;
}

vector<ngrams_info> utils::read_csv(const string& filename){
    
    ifstream input(filename);
    
    std::vector<ngrams_info> ngrams_data;
    std::string line;
    
    if (!input.is_open()) {
        std::cerr << "Failed to open file!" << std::endl;
        return ngrams_data;
    }
    
    //get it line-by-line
    while (std::getline(input, line)) {
        ngrams_info ngram_info;
        std::istringstream iss(line);
        // Parse the line and populate ngram_info
        std::getline(iss, ngram_info.ngrams, ',');
        iss >> ngram_info.frequency;
        
        ngrams_data.push_back(ngram_info);
    }
    input.close();

    return ngrams_data;
}

bool utils::starts_with(const string& sub_str, const string& str){
    return str.find(sub_str) == 0;
}
