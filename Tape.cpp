#include "Tape.h"
#include "Utils.h"
#include <iostream>
using namespace std;

string reverse(string str) {
	int begin = 0;
	int end = str.length() - 1;
	while (begin < end) {
		char temp = str[begin];
		str[begin] = str[end];
		str[end] = temp;
		begin++;
		end--;
	}
	return str;
}

Tape::Tape() {
	data[0] = "________";
	data[1] = "________";
	blank = '_';
	blanks = "________";
}

Tape::Tape(string s) {
	data[0] = s;
	data[1] = "________";
	blank = '_';
	blanks = "________";
}

void Tape::expand(int i) {
	if (i >= 0) {
		while (i >= data[0].length()) {
			data[0] += blanks;
		}
	} else {
		i = -i - 1;
		while (i >= data[1].length()) {
			data[1] += blanks;
		}
	}
}

char Tape::read(int i) {
	if (i >= 0) {
		if (i >= data[0].length()) {
			expand(i);
			return data[0][i];
		} else {
			return data[0][i];
		}
	} else {
		int k = -i - 1;
		if (k >= data[1].length()) {
			expand(i);
			return data[1][k];
		} else {
			return data[1][k];
		}
	}
}

void Tape::write(char c, int i) {
	if (i >= 0) {
		if (i >= data[0].length()) {
			expand(i);
			data[0][i] = c;
		} else {
			data[0][i] = c;
		}
	} else {
		int k = -i - 1;
		if (k >= data[1].length()) {
			expand(i);
			data[1][k] = c;
		} else {
			data[1][k] = c;
		}
	}
}

void Tape::print(int index, int head) {
	int left = -data[1].length();
	int right = data[0].length() - 1;
	if (head < left) {
		expand(head);
		left = head;
	} else if (head > right) {
		expand(head);
		right = head;
	}
	
	int begin = 0;
	int end = 0;
	for (int i = left; i < 0; i++) {
		if (read(i) != '_') {
			begin = i;
			break;
		}
	}
	
	for (int i = right; i >= 0; i--) {
		if (read(i) != '_') {
			end = i;
			break;
		}
	}
	begin = begin < head ? begin : head;
	end = end > head ? end : head;
	
	
	string s1 = "Index" + intToString(index) + "\t" + ":";
	string s2 = "Tape" + intToString(index) + "\t" + ":";;
	string s3 = "Head" + intToString(index) + "\t" + ":";;
	for (int i = begin; i <= end; i++) {
		
		string temp1 = intToString(i >= 0 ? i : -i);
		string temp2(1, read(i));
		string temp3(1, (i == head ? '^' : ' '));
		s1 += "\t" + temp1;
		s2 += "\t" + temp2;
		s3 += "\t" + temp3;
	}
	
	cout<<(s1 + "\n" + s2 + "\n" + s3 + "\n");
}

string Tape::toString() {
	string result = reverse(data[1]) + data[0];
	int begin = 0;
	int end = 0;
	for (int i = 0; i < result.length(); i++) {
		if (result[i] != '_') {
			begin = i;
			break;
		}
	}
	
	for (int i = result.length() - 1; i >= 0; i--) {
		if (result[i] != '_') {
			end = i;
			break;
		}
	}
	
	return result.substr(begin, end - begin + 1);
}
