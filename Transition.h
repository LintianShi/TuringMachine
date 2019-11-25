#ifndef __TRANSITION_H_
#define __TRANSITION_H_

#include <string>
#include <vector>
using namespace std;

class Transition {
	private:
		string newState;
		string oldState;
		string oldSymbols;
		string newSymbols;
		string directions;
		
	public: 
		Transition(string oldState, string oldSymbols, string newSymbols, string directions, string newState);
		string toString();
		string getNewState() { return newState; }
		string getOldState() { return oldState; }
		string getOldSymbols() { return oldSymbols; }
		string getNewSymbols() { return newSymbols; }
		string getDirections() { return directions; }
};

#endif
