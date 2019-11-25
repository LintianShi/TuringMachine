#ifndef __TMPARSER_H_
#define __TMPARSER_H_

#include <string>
#include <vector>
using namespace std;
#include "TM.h"

vector<char> parserChar(string str);
vector<string> parserString(string str);
bool parser(TM& tm, string str);

#endif
