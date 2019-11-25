#ifndef __TM_H_
#define __TM_H_

#include <string>
#include <vector>
#include <iostream>
using namespace std;
#include "Transition.h"
#include "Tape.h"

class TM {
	private: 
		vector<string> Q;
		vector<char> S;
		vector<char> G;
		string q0;
		char B;
		vector<string> F;
		int N;
		vector<Transition> transition;
		vector<int> head;
		vector<Tape> tape;
		string curState;
		bool isEqual(string a, string b);
		bool isFinal(string state);
		bool isLegal(string str);
		bool isContain(char c);
		
	public:
		string judge(string str);
		bool transit(int step);
		void setTape(string str);
		void addTransition(Transition t);
		void setB(char blank) { B = blank; }
		void addQ(string state) { Q.push_back(state); }
		void addS(char symbol) { S.push_back(symbol); }
		void addG(char symbol) { G.push_back(symbol); }
		void addF(string state) { F.push_back(state); }
		void setN(int n) { N = n; };
		void setq0(string state) { q0 = state; }
		void print();	
};

#endif
