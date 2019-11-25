#ifndef __TM_H_
#define __TM_H_

#include <string>
#include <vector>
using namespace std;

class TM {
	private vector<string> Q;
	private vector<char> S;
	private vector<char> G;
	private string q0;
	private string B;
	private vector<string> F;
	private int N;
	private vector<Transition> transition;
	private vector<int> head;
	private vector<Tape> tape;
};

#endif
