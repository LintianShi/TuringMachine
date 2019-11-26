#include "TM.h"
#include "Utils.h"
#include <iostream>
#include <algorithm>
using namespace std;

bool compareTransition(Transition a, Transition b) {
	int count_a = 0;
	int count_b = 0;
	string symbol_a = a.getOldSymbols();
	string symbol_b = b.getOldSymbols();
	for (int i = 0; i < symbol_a.length(); i++) {
		if (symbol_a[i] == '*') {
			count_a++;
		}
	}
	for (int i = 0; i < symbol_b.length(); i++) {
		if (symbol_b[i] == '*') {
			count_b++;
		}
	}
	return count_a < count_b;
}

bool TM::isContain(char c) {
	for (int i = 0; i < S.size(); i++) {
		if (S[i] == c) {
			return true;
		}
	}
	
	return false;
}

bool TM::isLegal(string str) {
	for (int i = 0; i < str.length(); i++) {
		if (!isContain(str[i])) {
			return false;
		}
	}
	
	return true;
}

bool TM::isFinal(string state) {
	for (int i = 0; i < F.size(); i++) {
		if (F[i] == state) {
			return true;
		}
	}
	return false;
}

bool isEqual(string a, string b) {
	if (a.length() != b.length()) {
		return false;
	}
	
	for (int i = 0; i < a.length(); i++) {
		if (!(a[i] == b[i] || a[i] == '*' || b[i] == '*')) {
			return false;
		}
	}
	return true;
}

string TM::judge(string str) {
	int step = 0;
	sort(transition.begin(), transition.end(), compareTransition);
	cout<<"Input: "+str<<endl;
	if (isLegal(str)) {
		cout<<"=========================RUN=========================\n";
	} else {
		cout<<"=========================ERR=========================\n";
		cout<<"The input \"" + str + "\" is iilegal\n";
		cout<<"=========================END=========================\n";
		return "Error";
	}
	setTape(str);
	curState = q0;
	int xx;
	while (transit(step++)) {
//		cin>>xx;
	}
	cout<<"Result: "+tape[0].toString()<<endl;
	cout<<"=========================END=========================\n";
	if (isFinal(curState)) {
		return "True";
	} else {
		return "False";
	}
}

void TM::setTape(string str) {
	tape.clear();
	head.clear();
	for (int i = 0; i < N; i++) {
		if (i == 0) {
			Tape temp(str);
			tape.push_back(temp);
		} else {
			Tape temp;
			tape.push_back(temp);
		}
		
		head.push_back(0);
	}
}

bool TM::transit(int step) {
	string curTape(N, '0');
	cout<<"Step\t"<<":\t"<<intToString(step)<<endl;
	for (int i = 0; i < N; i++) {
		curTape[i] = tape[i].read(head[i]);
		tape[i].print(i, head[i]);
	}
	cout<<"--------------------------------------------------------------\n";
	
	for (int i = 0; i < transition.size(); i++) {
		if (isEqual(transition[i].getOldState(), curState) && isEqual(transition[i].getOldSymbols(), curTape)) {
			curState = transition[i].getNewState();
			for (int j = 0; j < N; j++) {
				if (transition[i].getNewSymbols()[j] != '*') {
					tape[j].write(transition[i].getNewSymbols()[j], head[j]);
				}
			}
			for (int j = 0; j < N; j++) {
				if (transition[i].getDirections()[j] == 'l') {
					head[j]--;
				} else if (transition[i].getDirections()[j] == 'r') {
					head[j]++;
				}
			}
			return true;
		}
	}
	return false;
}

void TM::addTransition(Transition t) {
	transition.push_back(t);
}


void TM::print() {
	string state = "State: { ";
	for (int i = 0; i < Q.size(); i++) {
		state += Q[i] + "  ";
	}
	state += "}\n";
	cout<<state;
	
	string sigmaSymbol = "Sigma Symbol: { ";
	for (int i = 0; i < S.size(); i++) {
		string temp(1, S[i]);
		sigmaSymbol += temp + "  ";
	}
	sigmaSymbol += "}\n";
	cout<<sigmaSymbol;
	
	string gammaSymbol = "Gamma Symbol: { ";
	for (int i = 0; i < G.size(); i++) {
		string temp(1, G[i]);
		gammaSymbol += temp + "  ";
	}
	gammaSymbol += "}\n";
	cout<<gammaSymbol;
	
	string initialState = "Initial State: " + q0 + "\n";
	cout<<initialState;
	
	//string blank(1, B);
	string blank = "Blank Symbol: ";
	cout<<blank;
	cout<<B<<endl;
	
	string finalState = "Final State: { ";
	for (int i = 0; i < F.size(); i++) {
		finalState += F[i] + "  ";
	}
	finalState += "}\n";
	cout<<finalState;
	
	string tapeNumber = "Tape Number: ";
	cout<<tapeNumber;
	cout<<N<<endl;
	
	cout<<"Transition: \n";
	for (int i = 0; i < transition.size(); i++) {
		cout<<transition[i].toString()<<endl;
	}
	
	
}
