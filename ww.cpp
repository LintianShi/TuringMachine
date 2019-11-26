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
		if (input[i] != '*')
			tape[i].write(input[i], head[i]);
	}
}

int fib(string str) {
	vector<Tape> tape;
	Tape temp1(str);
	Tape temp2;
	Tape temp3;
	Tape temp4;
	tape.push_back(temp1);
	tape.push_back(temp2);
	tape.push_back(temp3);
	tape.push_back(temp4);
	vector<int> head;
	head.push_back(0);
	head.push_back(0);
	head.push_back(0);
	head.push_back(0);
	
	string curState = "init";
	while (curState != "halt_accept" && curState != "halt_reject" ) {
//		int x;
//		cin>>x;
		tape[0].print(0, head[0]);
		tape[1].print(1, head[1]);
		tape[2].print(0, head[2]);
		tape[3].print(1, head[3]);
		if (curState == "init") {
			if (isEqual("____", getTape(tape, head))) {
				curState = "reject";
			} else if (isEqual("0___", getTape(tape, head))) {
				curState = "cmp";
				writeTape("0000", tape, head);
			}
		} else if (curState == "cmp") {
			if (isEqual("0**0", getTape(tape, head))) {
				curState = "cmp";
				head[0]++;
				head[3]++;
			} else if (isEqual("_**0", getTape(tape, head))) {
				curState = "ready_reject";
				head[0]--;
			} else if (isEqual("0**_", getTape(tape, head))) {
				curState = "move_2_1";
				head[3]--;
			} else if (isEqual("_**_", getTape(tape, head))) {
				curState = "ready_accept";
				head[0]--;
				head[3]--;
			} 
		} else if (curState == "move_2_1") {
			if (isEqual("*0**", getTape(tape, head))) {
				curState = "move_2_1";
				head[1]--;
			} else if (isEqual("*_**", getTape(tape, head))) {
				curState = "move_2_1_1";
				head[1]++;
			}
		} else if (curState == "move_2_1_1") {
			if (isEqual("**0*", getTape(tape, head))) {
				curState = "move_2_1_1";
				head[2]--;
			} else if (isEqual("**_*", getTape(tape, head))) {
				curState = "move_2_1_2";
				head[2]++;
			}
		} else if (curState == "move_2_1_2") {
			if (isEqual("**0*", getTape(tape, head))) {
				curState = "move_2_1_2";
				writeTape("*00*", tape, head);
				head[1]++;
				head[2]++;
			} else if (isEqual("**_*", getTape(tape, head))) {
				curState = "move_3_2";
				head[1]--;
				head[2]--;
			}
		} else if (curState == "move_3_2") {
			if (isEqual("**0*", getTape(tape, head))) {
				curState = "move_3_2";
				head[2]--;
			} else if (isEqual("**_*", getTape(tape, head))) {
				curState = "move_3_2_1";
				head[2]++;
			}
		} else if (curState == "move_3_2_1") {
			if (isEqual("***0", getTape(tape, head))) {
				curState = "move_3_2_1";
				head[3]--;
			} else if (isEqual("***_", getTape(tape, head))) {
				curState = "move_3_2_2";
				head[3]++;
			}
		} else if (curState == "move_3_2_2") {
			if (isEqual("***0", getTape(tape, head))) {
				curState = "move_3_2_2";
				writeTape("**00", tape, head);
				head[2]++;
				head[3]++;
			} else if (isEqual("***_", getTape(tape, head))) {
				curState = "add";
				head[2]--;
				//head[3]--;
			}
		} else if (curState == "mh_cmp") {
			if (isEqual("***0", getTape(tape, head))) {
				curState = "mh_cmp";
				head[3]--;
			} else if (isEqual("***_", getTape(tape, head))) {
				curState = "mh_cmp1";
				head[3]++;
			}
		} else if (curState == "mh_cmp1") {
			if (isEqual("0***", getTape(tape, head))) {
				curState = "mh_cmp1";
				head[0]--;
			} else if (isEqual("_***", getTape(tape, head))) {
				curState = "cmp";
				head[0]++;
			}
		} else if (curState == "add") {
			if (isEqual("*0**", getTape(tape, head))) {
				curState = "add";
				head[1]--;
			} else if (isEqual("*_**", getTape(tape, head))) {
				curState = "add1";
				head[1]++;
			}
		} else if (curState == "add1") {
			if (isEqual("*0**", getTape(tape, head))) {
				curState = "add1";
				writeTape("***0", tape, head);
				head[1]++;
				head[3]++;
			} else if (isEqual("*_**", getTape(tape, head))) {
				curState = "mh_cmp";
				head[1]--;
				head[3]--;
			}
		} else if (curState == "ready_accept") {
			if (isEqual("0**0", getTape(tape, head))) {
				curState = "ready_accept";
				writeTape("_**_", tape, head);
				head[0]--;
				head[3]--;
			} else if (isEqual("_**_", getTape(tape, head))) {
				curState = "ready_accept1";
				head[0]++;
				head[3]++;
			}
		} else if (curState == "ready_accept1") {
			if (isEqual("*0**", getTape(tape, head))) {
				curState = "ready_accept1";
				writeTape("*_**", tape, head);
				head[1]--;
			} else if (isEqual("*_**", getTape(tape, head))) {
				curState = "ready_accept2";
				head[1]++;
			}
		} else if (curState == "ready_accept2") {
			if (isEqual("**0*", getTape(tape, head))) {
				curState = "ready_accept2";
				writeTape("**_*", tape, head);
				head[2]--;
			} else if (isEqual("**_*", getTape(tape, head))) {
				curState = "accept";
				head[2]++;
			}
		} else if (curState == "ready_reject") {
			if (isEqual("0***", getTape(tape, head))) {
				curState = "ready_reject";
				writeTape("_***", tape, head);
				head[0]--;
			} else if (isEqual("_***", getTape(tape, head))) {
				curState = "ready_reject1";
				head[0]++;
			}
		} else if (curState == "ready_reject1") {
			if (isEqual("*0**", getTape(tape, head))) {
				curState = "ready_reject1";
				writeTape("*_**", tape, head);
				head[1]--;
			} else if (isEqual("*_**", getTape(tape, head))) {
				curState = "ready_reject2";
				head[1]++;
			}
		} else if (curState == "ready_reject2") {
			if (isEqual("**0*", getTape(tape, head))) {
				curState = "ready_reject2";
				writeTape("**_*", tape, head);
				head[2]--;
			} else if (isEqual("**_*", getTape(tape, head))) {
				curState = "ready_reject3";
				head[2]++;
			}
		} else if (curState == "ready_reject3") {
			if (isEqual("***0", getTape(tape, head))) {
				curState = "ready_reject3";
				head[3]++;
			} else if (isEqual("***_", getTape(tape, head))) {
				curState = "ready_reject4";
				head[3]--;
			}
		} else if (curState == "ready_reject4") {
			if (isEqual("***0", getTape(tape, head))) {
				curState = "ready_reject4";
				writeTape("***_", tape, head);
				head[3]--;
			} else if (isEqual("***_", getTape(tape, head))) {
				curState = "reject";
				head[3]++;
			}
		} else if (curState == "accept") {
			if (isEqual("____", getTape(tape, head))) {
				curState = "accept1";
				writeTape("T___", tape, head);
				head[0]++;
			}
		} else if (curState == "accept1") {
			if (isEqual("____", getTape(tape, head))) {
				curState = "accept2";
				writeTape("r___", tape, head);
				head[0]++;
			}
		} else if (curState == "accept2") {
			if (isEqual("____", getTape(tape, head))) {
				curState = "accept3";
				writeTape("u___", tape, head);
				head[0]++;
			}
		} else if (curState == "accept3") {
			if (isEqual("____", getTape(tape, head))) {
				curState = "halt_accept";
				writeTape("e___", tape, head);
			}
		} else if (curState == "reject") {
			if (isEqual("____", getTape(tape, head))) {
				curState = "reject1";
				writeTape("F___", tape, head);
				head[0]++;
			}
		} else if (curState == "reject1") {
			if (isEqual("____", getTape(tape, head))) {
				curState = "reject2";
				writeTape("a___", tape, head);
				head[0]++;
			}
		} else if (curState == "reject2") {
			if (isEqual("____", getTape(tape, head))) {
				curState = "reject3";
				writeTape("l___", tape, head);
				head[0]++;
			}
		} else if (curState == "reject3") {
			if (isEqual("____", getTape(tape, head))) {
				curState = "reject4";
				writeTape("s___", tape, head);
				head[0]++;
			}
		} else if (curState == "reject4") {
			if (isEqual("____", getTape(tape, head))) {
				curState = "halt_reject";
				writeTape("e___", tape, head);
			}
		}
	}
	tape[0].print(0, head[0]);
		tape[1].print(1, head[1]);
		tape[2].print(0, head[2]);
		tape[3].print(1, head[3]);
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
