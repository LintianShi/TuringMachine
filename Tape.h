#ifndef __TAPE_H_
#define __TAPE_H_

#include <string>
#include <vector>
using namespace std;

class Tape {
	public Tape(string s);
	
	private string data[2];
	private char Blank;
	private void expand(int i);
	
	public char read(int i);
	public void write(char c, int i);
};

#endif
