#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
using namespace std;
#include "Transition.h"
#include "TMParser.h"
#include "TM.h"

int main() {
	TM tm;
	ifstream fin("palindrome_detector_2tapes.tm");
	string str;
	while (getline(fin, str)) {
		if (str != "" && str[0] != ';') {
			parser(tm, str);
		}
	}
	//tm.print();
	string input;
	cin>>input;
	cout<<tm.judge(input)<<endl;
}

vector<char> parserChar(string str) {
	int begin = 0;
	int end = 0;
	for (int i = 0; i < str.length(); i++) {
		if (str[i] == '{') {
			begin = i;
		} else if (str[i] == '}') {
			end = i;
			break;
		}
	}
	string content = str.substr(begin + 1, end - begin - 1);
	for (int i = 0; i < content.length(); i++) {
		if (content[i] == ',') {
			content[i] = ' ';
		}
	}
	
	vector<char> symbol;
	stringstream ss;
	ss<<content;
	char temp;
	while (ss>>temp) {
		symbol.push_back(temp);
	}
	
	return symbol;
}

vector<string> parserString(string str) {
	int begin = 0;
	int end = 0;
	for (int i = 0; i < str.length(); i++) {
		if (str[i] == '{') {
			begin = i;
		} else if (str[i] == '}') {
			end = i;
			break;
		}
	}
	string content = str.substr(begin + 1, end - begin - 1);
	for (int i = 0; i < content.length(); i++) {
		if (content[i] == ',') {
			content[i] = ' ';
		}
	}
	
	vector<string> state;
	stringstream ss;
	ss<<content;
	string temp;
	while (ss>>temp) {
		state.push_back(temp);
	}
	
	return state;
}

bool parser(TM& tm, string str) {
	if (str[0] == '#') {
		if (str[1] == 'Q') {
			vector<string> state = parserString(str);
			for (int i = 0; i < state.size(); i++) {
				tm.addQ(state[i]);
			}
		} else if (str[1] == 'S') {
			vector<char> symbol = parserChar(str);
			for (int i = 0; i < symbol.size(); i++) {
				tm.addS(symbol[i]);
			}
		} else if (str[1] == 'G') {
			vector<char> symbol = parserChar(str);
			for (int i = 0; i < symbol.size(); i++) {
				tm.addG(symbol[i]);
			}
		} else if (str[1] == 'B') {
			tm.setB('_');
		} else if (str[1] == 'F') {
			vector<string> state = parserString(str);
			for (int i = 0; i < state.size(); i++) {
				tm.addF(state[i]);
			}
		} else if (str[1] == 'N') {
			int begin = 0;
			for (int i = 0; i < str.length(); i++) {
				if (str[i] == '=') {
					begin = i;
					break;
				}
			}
			string s = str.substr(begin + 1, str.length() - begin);
			stringstream ss;
			ss<<s;
			int n;
			ss>>n;
			tm.setN(n);
		} else if (str[1] == 'q' && str[2] == '0') {
			int begin = 0;
			for (int i = 0; i < str.length(); i++) {
				if (str[i] == '=') {
					begin = i;
					break;
				}
			}
			string s = str.substr(begin + 1, str.length() - begin);
			stringstream ss;
			ss<<s;
			string q0;;
			ss>>q0;
			tm.setq0(q0);
		} else {
			return false;
		}
	} else {
		stringstream ss;
		ss<<str;
		string oldState;
		ss>>oldState;
		string oldSymbols;
		ss>>oldSymbols;
		string newSymbols;
		ss>>newSymbols;
		string directions;
		ss>>directions;
		string newState;
		ss>>newState;
		
		Transition t(oldState, oldSymbols, newSymbols, directions, newState);
		tm.addTransition(t);
	}
	return true;
}




