#ifndef __TRANSITION_H_
#define __TRANSITION_H_

#include <string>
#include <vector>
using namespace std;

class Transition {
	public Transition(string oldState, vector<char> oldSymbols, vector<char> newSymbols, string newState, vector<char> directions);
	private string newState;
	private string oldState;
	private vector<char> oldSymbols;
	private vector<char> newSymbols;
	private vector<char> directions;
};

#endif
