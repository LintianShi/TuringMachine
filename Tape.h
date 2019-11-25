#ifndef __TAPE_H_
#define __TAPE_H_

#include <string>
#include <vector>
using namespace std;

class Tape {
	public: 
		Tape();
		Tape(string s);
		char read(int i);
		void write(char c, int i);
		void print(int index, int head);
		string toString();
		
	private: 
		string blanks;
		string data[2];
		char blank;
		void expand(int i);
};

#endif
