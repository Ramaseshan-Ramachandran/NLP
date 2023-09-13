//
//  mt_read.cpp
//  test
//
//  Created by Ramaseshan Ramachandran on 05/08/23.
//

#include "../include/mt_read.hpp"
#include "../include/ngrams.hpp"
#include <unordered_map>

vector<ngrams_info> ngram_freq;;
vector<ngrams_info> context_freq;;

//class NGramsInfo {
//public:
//    std::string ngrams;
//    int frequency;
//
//    NGramsInfo(const std::string& ngrams, int frequency) : ngrams(ngrams), frequency(frequency) {}
//};
mt_read::mt_read() {
    
}

mt_read::~mt_read(){
//    content.clear();
}

void mt_read::progress_bar(double progress, double max_progress){
    int width = 40;
      int filled_chars = (progress * width) / max_progress;
      int empty_chars = width - filled_chars;
      std::cout << "[";
      for (int i = 0; i < filled_chars; i++) {
        std::cout << "=";
      }
      for (int i = 0; i < empty_chars; i++) {
        std::cout << " ";
      }
    std::cout << "] " << static_cast<int>(progress) << std::setw(1)<<"% - #files " << number_of_files_processed << "\r";
    std::cout.flush();
}
void mt_read::update_progress() {
    std::lock_guard<std::mutex> lock(progressMutex);
    number_of_files_processed++;
    double progress = static_cast<double>(number_of_files_processed) / files_count * 100;
//    std::cout << "\rProgress: " << std::setw(10) << filesProcessed << " files processed." ;
    progress_bar(progress,100);

}

void mt_read::process_file(const std::string& filename) {
    utils u;
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    std::string _content;
    _content.assign(std::istreambuf_iterator<char>(file),
                    std::istreambuf_iterator<char>());

    std::lock_guard<std::mutex> lock(c_mutex);
    //write all the other required operations - tokenization,
    std::replace(_content.begin(), _content.end(), '\n', ' ');
    std::replace(_content.begin(), _content.end(), '\f', ' ');

    if ( _content.size() < 20)
        return;
    
    content += u.to_lower(_content);
//    ngrams ng(false);
//    pair<vector<ngrams_info>, vector<ngrams_info>> ng_f = ng.get(_content, 3);
//
//    ngram_freq = ng.update(ngram_freq, ng_f.first);
//    context_freq = ng.update(context_freq, ng_f.second);

    update_progress();

}

const string& mt_read::read(const string&path) {

    std::string output_file = "/tmp/content.txt";

    // Create a vector to store file path
    std::vector<std::string> file_paths;

    // Populate the vector with file paths from the folder
    for (const auto& entry : fs::directory_iterator(path)) {
        if (entry.is_regular_file() && entry.path().extension() == ".txt") {
            file_paths.push_back(entry.path().string());
        }
    }

    files_count = (int)file_paths.size();

    // Number of threads you want to use
    //int NUM_THREADS = std::thread::hardware_concurrency(); // Use the number of available cores

    // Split the work among threads
    std::vector<std::thread> threads;
    int files_per_thread = files_count / NUM_THREADS;
    int remainder_files = files_count % NUM_THREADS;
    int start_index = 0;
    for (int i = 0; i < NUM_THREADS; ++i) {
            int end_index = start_index + files_per_thread + (i < remainder_files ? 1 : 0);
        threads.emplace_back([start_index, end_index, &file_paths, this]() {
                for (int j = start_index; j < end_index; ++j) {
                    this->process_file(file_paths[j]);
                }
            });
            start_index = end_index;
        }

        // Join the threads back to the main thread
        for (auto& thread : threads) {
            thread.join();
        }
        std::cout << std::endl;

        // Write all content to the output file
        std::ofstream output(output_file);
        if (output.is_open()) {
            output << content;
            output.close();
        } else {
            std::cerr << "Error opening the output file: " << output_file << std::endl;
        }
    
//    //save ngrams and context files
//    ngrams_info ng_info;
//    ng_info.write(ngram_freq, "/tmp/ngrams_freq.txt");
//    ng_info.write(context_freq, "/tmp/ontextc_freq.txt");

    
    return content;
//    return content;
    }


// Function to create n-grams from a given string and update the ngrams_info map
void createNGrams(std::string& content, int start, int end, std::unordered_map<std::string, int>& ngramsInfoMap, std::mutex& mtx) {
    for (int i = start; i < end; ++i) {
        std::string ngram = content.substr(i, 2); // Change the "2" to the desired n-gram size

        std::lock_guard<std::mutex> lock(mtx);
        ngramsInfoMap[ngram]++;
    }
}

//int ng_main(const string& content) {
////    std::string content = ""; // Your large 2GB string here
//
//    // Divide the content into smaller chunks for parallel processing
//    int numChunks = (content.size() + BUFFER_SIZE - 1) / BUFFER_SIZE;
//
//    // Container to store n-grams and their frequencies
//    std::unordered_map<std::string, int> ngramsInfoMap;
//
//    // Mutex to synchronize access to the ngramsInfoMap
//    std::mutex mtx;
//
//    // Create threads and distribute the work among them
//    std::vector<std::thread> threads;
//    int chunkSize = content.size() / NUM_THREADS;
//    for (int i = 0; i < NUM_THREADS; ++i) {
//            int start = i * chunkSize;
//            int end = (i == NUM_THREADS - 1) ? content.size() : (i + 1) * chunkSize;
//
//            threads.emplace_back(createNGrams, std::ref(content), start, end, std::ref(ngramsInfoMap), std::ref(mtx));
//        }
//
//        // Join the threads back to the main thread
//        for (auto& thread : threads) {
//            thread.join();
//        }
//
//        // Create ngrams_info objects from the ngramsInfoMap
//        std::vector<NGramsInfo> ngramsInfoVec;
//        for (const auto& entry : ngramsInfoMap) {
//            ngramsInfoVec.emplace_back(entry.first, entry.second);
//        }
//
//        // Now you have the ngramsInfoVec containing ngrams and their frequencies
//
//        return 0;
//    }

//int main(){
//    mt_read mt;
//    std::string path = "/Users/ram/Documents/GitHub/LanguageModels/DemoCode/Corpus/txt";
//    const string& content = mt.read(path);
//    pair<vector<ngrams_info>, vector<ngrams_info>> info_pair;
//    ngrams ng(false); //do not remove stopwords
//    info_pair = ng.get(content,3);
//    ngrams_info info;
//    info.write(info_pair.first, "ngrams.txt");
//    info.write(info_pair.second, "context.txt");
//
//    vector<ngrams_info> results = ng.search(info_pair.first, "budget speech");
//
//    for (const ngrams_info& info : results) {
//        cout << info.ngrams << ":" << info.frequency << ":" << info.index << endl;
//    }
//
//}
//
