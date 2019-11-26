#include "TM.h"
#include "Tape.h"

string getTape(vector<Tape>& tape, vector<int>& head) {
	string str(tape.size(), '0');
	for (int i = 0; i < tape.size(); i++) {
		str[i] = tape[i].read(head[i]);
	}
	
	return str;
}

void writeTape(string input, vector<Tape>& tape, vector<int>& head) {
	for (int i = 0; i < input.length(); i++) {
		//if (input[i] != '*')
			tape[i].write(input[i], head[i]);
	}
}

int ww(string str) {
	vector<Tape> tape;
	Tape temp1(str);
	Tape temp2;
	tape.push_back(temp1);
	tape.push_back(temp2);
	vector<int> head;
	head.push_back(0);
	head.push_back(0);
	
	string curState = "init";
	while (curState != "halt_accept" && curState != "halt_reject" ) {
//		int x;
//		cin>>x;
		tape[0].print(0, head[0]);
		tape[1].print(1, head[1]);
		if (curState == "init") {
			if (isEqual("__", getTape(tape, head))) {
				curState = "accept";
				writeTape("__", tape, head);
			} else if (isEqual("0_", getTape(tape, head))) {
				curState = "even";
				head[0]++;
			} else if (isEqual("1_", getTape(tape, head))) {
				curState = "even";
				head[0]++;
			}
		} else if (curState == "even") {
			if (isEqual("0_", getTape(tape, head))) {
				curState = "odd";
				head[0]++;
			} else if (isEqual("1_", getTape(tape, head))) {
				curState = "odd";
				head[0]++;
			} else if (isEqual("__", getTape(tape, head))) {
				curState = "even_reject";
				head[0]--;
			}
		} else if (curState == "odd") {
			if (isEqual("0_", getTape(tape, head))) {
				curState = "even";
				head[0]++;
			} else if (isEqual("1_", getTape(tape, head))) {
				curState = "even";
				head[0]++;
			} else if (isEqual("__", getTape(tape, head))) {
				curState = "even_accept";
				head[0]--;
			}
		} else if (curState == "fm_mh") {
			if (isEqual("00", getTape(tape, head))) {
				curState = "fm_mh";
				head[0]--;
				head[1]--;
			} else if (isEqual("11", getTape(tape, head))) {
				curState = "fm_mh";
				head[0]--;
				head[1]--;
			} else if (isEqual("__", getTape(tape, head))) {
				curState = "fm1";
				head[0]++;
				head[1]++;
			}
		} else if (curState == "fm1") {
			if (isEqual("_0", getTape(tape, head))) {
				curState = "find_mid";
				head[0]--;
			} else if (isEqual("_1", getTape(tape, head))) {
				curState = "find_mid";
				head[0]--;
			} else if (isEqual("*0", getTape(tape, head))) {
				curState = "fm2";
				head[1]++;
			} else if (isEqual("*1", getTape(tape, head))) {
				curState = "fm2";
				head[1]++;
			}
		} else if (curState == "fm2") {
			if (isEqual("0*", getTape(tape, head))) {
				curState = "fm3";
				head[0]++;
			} else if (isEqual("1*", getTape(tape, head))) {
				curState = "fm3";
				head[0]++;
			} 
		} else if (curState == "fm3") {
			if (isEqual("0*", getTape(tape, head))) {
				curState = "fm1";
				head[0]++;
			} else if (isEqual("1*", getTape(tape, head))) {
				curState = "fm1";
				head[0]++;
			}
		} else if (curState == "find_mid") {
			if (isEqual("0*", getTape(tape, head))) {
				curState = "find_mid";
				head[0]--;
			} else if (isEqual("1*", getTape(tape, head))) {
				curState = "find_mid";
				head[0]--;
			} else if (isEqual("_*", getTape(tape, head))) {
				curState = "cmp";
				head[0]++;
			}
		} else if (curState == "cmp") {
			if (isEqual("00", getTape(tape, head))) {
				curState = "cmp";
				head[0]++;
				head[1]++;
			} else if (isEqual("11", getTape(tape, head))) {
				curState = "cmp";
				head[0]++;
				head[1]++;
			} else if (isEqual("01", getTape(tape, head))) {
				curState = "mid_reject";
			} else if (isEqual("10", getTape(tape, head))) {
				curState = "mid_reject";
			} else if (isEqual("*_", getTape(tape, head))) {
				curState = "mid_accept";
				head[0]++;
			}
		} else if (curState == "mid_reject") {
			if (isEqual("0*", getTape(tape, head))) {
				curState = "mid_reject";
				head[0]++;
			} else if (isEqual("1*", getTape(tape, head))) {
				curState = "mid_reject";
				head[0]++;
			} else if (isEqual("_*", getTape(tape, head))) {
				curState = "mid_reject1";
				head[0]--;
			}
		} else if (curState == "mid_reject1") {
			if (isEqual("*1", getTape(tape, head))) {
				curState = "mid_reject1";
				head[1]++;
			} else if (isEqual("*0", getTape(tape, head))) {
				curState = "mid_reject1";
				head[1]++;
			} else if (isEqual("*_", getTape(tape, head))) {
				curState = "mid_reject2";
				head[1]--;
			}
		} else if (curState == "mid_reject2") {
			if (isEqual("__", getTape(tape, head))) {
				curState = "even_reject";
				head[0]++;
				head[1]++;
			} else if (isEqual("**", getTape(tape, head))) {
				writeTape("__", tape, head);
				curState = "mid_reject2";
				head[0]--;
				head[1]--;
			}
		} else if (curState == "mid_accept") {
			if (isEqual("1_", getTape(tape, head))) {
				curState = "mid_accept";
				head[0]++;
			} else if (isEqual("0_", getTape(tape, head))) {
				curState = "mid_accept";
				head[0]++;
			} else if (isEqual("__", getTape(tape, head))) {
				curState = "mid_rm";
				head[0]--;
				head[1]--;
			}
		} else if (curState == "mid_rm") {
			if (isEqual("11", getTape(tape, head))) {
				writeTape("__", tape, head);
				curState = "mid_rm";
				head[0]--;
				head[1]--;
			} else if (isEqual("00", getTape(tape, head))) {
				writeTape("__", tape, head);
				curState = "mid_rm";
				head[0]--;
				head[1]--;
			} else if (isEqual("__", getTape(tape, head))) {
				curState = "accept";
				head[0]++;
				head[1]++;
			}
		} else if (curState == "cp") {
			if (isEqual("0_", getTape(tape, head))) {
				curState = "cp";
				writeTape("00", tape, head);
				head[0]++;
				head[1]++;
			} else if (isEqual("1_", getTape(tape, head))) {
				curState = "cp";
				writeTape("11", tape, head);
				head[0]++;
				head[1]++;
			} else if (isEqual("__", getTape(tape, head))) {
				curState = "fm_mh";
				head[0]--;
				head[1]--;
			}
		} else if (curState == "even_accept") {
			if (isEqual("0_", getTape(tape, head))) {
				curState = "even_accept";
				head[0]--;
			} else if (isEqual("1_", getTape(tape, head))) {
				curState = "even_accept";
				head[0]--;
			} else if (isEqual("__", getTape(tape, head))) {
				curState = "cp";
				head[0]++;
			}
		} else if (curState == "accept") {
			if (isEqual("__", getTape(tape, head))) {
				curState = "accept1";
				writeTape("T_", tape, head);
				head[0]++;
			}
		} else if (curState == "accept1") {
			if (isEqual("__", getTape(tape, head))) {
				curState = "accept2";
				writeTape("r_", tape, head);
				head[0]++;
			}
		} else if (curState == "accept2") {
			if (isEqual("__", getTape(tape, head))) {
				curState = "accept3";
				writeTape("u_", tape, head);
				head[0]++;
			}
		} else if (curState == "accept3") {
			if (isEqual("__", getTape(tape, head))) {
				curState = "halt_accept";
				writeTape("e_", tape, head);
			}
		} else if (curState == "even_reject") {
			if (isEqual("0_", getTape(tape, head))) {
				curState = "even_reject";
				writeTape("__", tape, head);
				head[0]--;
			} else if (isEqual("1_", getTape(tape, head))) {
				curState = "even_reject";
				writeTape("__", tape, head);
				head[0]--;
			} else if (isEqual("__", getTape(tape, head))) {
				curState = "reject1";
				writeTape("F_", tape, head);
				head[0]++;
			}
		} else if (curState == "reject1") {
			if (isEqual("__", getTape(tape, head))) {
				curState = "reject2";
				writeTape("a_", tape, head);
				head[0]++;
			}
		} else if (curState == "reject2") {
			if (isEqual("__", getTape(tape, head))) {
				curState = "reject3";
				writeTape("l_", tape, head);
				head[0]++;
			}
		} else if (curState == "reject3") {
			if (isEqual("__", getTape(tape, head))) {
				curState = "reject4";
				writeTape("s_", tape, head);
				head[0]++;
			}
		} else if (curState == "reject4") {
			if (isEqual("__", getTape(tape, head))) {
				curState = "halt_reject";
				writeTape("e_", tape, head);
			}
		}
	}
	tape[0].print(0, head[0]);
	tape[1].print(1, head[1]);
	
	return 0;
}
