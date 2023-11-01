//
//  ngram_lm.cpp
//  test
//
//  Created by Ramaseshan Ramachandran on 07/08/23.
//

#include "../include/ngram_lm.hpp"
#include "../include/mt_read.hpp"
#include "../include/ngrams.hpp"
#include "../include/utils.hpp"
ngram_lm::ngram_lm(){
    
}

ngram_lm::~ngram_lm(){
    
}

const vector<probability> ngram_lm::probability_distribution(const string& search_str,
                                                             vector<ngrams_info>& ngs_info,
                                                             vector<ngrams_info>& context_list,
                                                             int count){
    ngrams ng(false);
    utils u;
    
    vector<probability> prob_dist;

    //get n-1 grams count from context_info
    //get all the ngrams_info record where the starting ngrams = str
    vector<ngrams_info> ngrams_list = ng.search(ngs_info, search_str);
    
    if ( size(ngrams_list) > 0) {
        
        for (auto it = ngrams_list.begin(); it != ngrams_list.end();) {
            if (search_str != u.get_context(it->ngrams)) {
                it = ngrams_list.erase(it);
            } else {
                ++it;
            }
        }
        
        vector<ngrams_info> context_info = ng.search(context_list, search_str);
        
        for (auto it = context_info.begin(); it != context_info.end();) {
            if (search_str != it->ngrams) {
                it = context_info.erase(it);
            } else {
                ++it;
            }
        }
        for (auto info: ngrams_list){
            probability p(info.ngrams, ((float)info.frequency/(float)context_info.data()[0].frequency));
            prob_dist.push_back(p);
        }
    }
    else {
        cout << "The ngram is not found in the corpus " << endl;
    }
    //for all the ngrams starting with context, get the frequency
    //find the conditional probability score count(ngrams)/count(context)
    //for the given ngram, return the probability distribution
    return utils::most_common(prob_dist,count);
}

void ngram_lm::build_model(){
    mt_read mt;
//    string path = "/Users/ram/Documents/GitHub/LanguageModels/DemoCode/Corpus/txt/";
    // string path = "/Users/ram/Documents/GitHub/Corpus";
    //get ngrams and context in pair
    pair<vector<ngrams_info>, vector<ngrams_info>> info_pair;
    const string content = mt.read(path);
    ngrams ng(false); //do not remove stopwords
    //get ngrams freq and the context freq
    info_pair = ng.get(content,3); //getting trigrams and bigras as context
    ngrams_info info;
    info.write(info_pair.first, "/tmp/ngrams.txt");
    info.write(info_pair.second, "/tmp/context.txt");
}

void ngram_lm::predict_next_word(){
    
    string input;
    
    utils u;
    cout << "Reading ngrams and context files..." << endl;
    vector<ngrams_info> ngs_info = u.read_csv("/tmp/ngrams.txt");
    vector<ngrams_info> context_list = u.read_csv("/tmp/context.txt");
    while (1) {
        cin.ignore();
        cout << "Input two words: ";
        getline(cin,input);
        const vector<probability>& pd = probability_distribution(input, ngs_info, context_list, 5);
        if (size(pd) > 0){
            cout << "Probrability distribution for the next word " << input << "." << endl;

            for (auto info : pd){
                if (info.prob > 0.0)
                    cout << info.ngrams << " : " << info.prob << endl;
            }
        }
        else {
            cout << "Probrability distribution is not found for these words " << input << "." << endl;
        }
    }
}
int main(int argc, char *argv[]){
    mt_read mt;
    ngram_lm lm;
    
    int build = 0;
    cout << "Enter 0 predict 1 for build and predict ";
    cin >> build;
    if (!build)
        lm.predict_next_word();
    else
        lm.build_model();
}
//vector<ngrams_info> ngram_lm::get_ngrams(ngrams_info context){
//    vector<ngrams_info> ngrams;
//    for (const auto& ngram : ngrams) {
//            if (ngram.ngram.find(context) == 0) {
//                matching_ngrams.push_back(ngram);
//            }
//        }
//}


