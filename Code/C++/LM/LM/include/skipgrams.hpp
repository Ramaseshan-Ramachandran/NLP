/*
 * File: skipgrams.hpp
 * Project: include
 * Created Date: Monday, December 2nd 2019, 9:22:33 am
 * Author: Ramaseshan Ramachandran
 * -----
 * Last Modified: Monday, 2nd December 2019 9:59:49 am
 * Modified By: Ramaseshan Ramachandran
 * -----
 * Copyright (c) 2019 JCR Labz
 * blah
 * -----
 * HISTORY:
 * Date      	By	Comments
 * ----------	---	----------------------------------------------------------
 */

#ifndef __SKIPGRAM_HPP__
#define __SKIPGRAM_HPP__

#include <vector>
#include <string>

using namespace std;

class skipgrams
{
protected:
    vector<vector<string>> _extract(int n, vector<string> const &v);

public:
    skipgrams();
    ~skipgrams();
    vector<vector<string>> extract(int n, vector<string> const &v, bool padding = false);
};
#endif // !__SKIPGRAM_HPP
