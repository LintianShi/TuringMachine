#include "Utils.h"

string intToString(int i) {
	stringstream ss;
	string str;
	ss<<i;
	ss>>str;
	return str;
}
