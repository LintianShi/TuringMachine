#include "Transition.h"
#include <iostream>
using namespace std;

Transition::Transition(string oldState, string oldSymbols, string newSymbols, string directions, string newState) : 
	oldState(oldState), oldSymbols(oldSymbols), newSymbols(newSymbols), newState(newState), directions(directions) {
	;
}


string Transition::toString() {
	string str1 = oldState;
	string str2(oldSymbols.begin(), oldSymbols.end());
	string str3(newSymbols.begin(), newSymbols.end());
	string str4 = newState;
	string str5(directions.begin(), directions.end());
	
	return str1 + " " + str2 + " " + str3 + " " + str4 + " " + str5;
}
