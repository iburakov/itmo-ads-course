#include "edx-io.hpp"
#include <queue>
#include <vector>
#include <string>
#include <map>
#include <tuple>
#include <fstream>
#include <assert.h>

using namespace std;

typedef uint16_t val_t;

// registers
vector<val_t> reg('z' - 'a' + 1, 0);

// (machine) queue
auto mqueue = queue<val_t>();

// loaded program (instructions reside here)
auto prog = vector<string>(100000);

// instruction pointer (index of "prog")
int ip = 0;

// mapping of labels to their target ip (index of "prog")
auto labels = map<string, int>();

// terminator flag
bool is_terminating = false;


tuple<val_t, val_t> pop_two() {
	val_t a = mqueue.front();
	mqueue.pop();
	val_t b = mqueue.front();
	mqueue.pop();

	return { a, b };
}

val_t pop_one() {
	val_t a = mqueue.front();
	mqueue.pop();
	return a;
}

#define cmd_reg(pos) (reg[instr[pos] - 'a'])
#define cmd_label_ip(pos) (labels[instr.substr(pos)])

void exec(string instr) {
	// if whole instruction is a number
	if (find_if(instr.begin(), instr.end(), [](char c) {return !isdigit(c); }) == instr.end()) {
		mqueue.push(stoi(instr));
		return;
	}

	// process general instructions
	val_t a, b;
	switch (instr[0]) {
		case '+': {
			tie(a, b) = pop_two();
			mqueue.push(a + b);
		} break;
		case '-': {
			tie(a, b) = pop_two();
			mqueue.push(a - b);
		} break;
		case '*': {
			tie(a, b) = pop_two();
			mqueue.push(a * b);
		} break;
		case '/': {
			tie(a, b) = pop_two();
			val_t result = (b == 0) ? 0 : a / b;
			mqueue.push(result);
		} break;
		case '%': {
			tie(a, b) = pop_two();
			val_t result = (b == 0) ? 0 : a % b;
			mqueue.push(result);
		} break;
		case '>': {
			cmd_reg(1) = pop_one();
		} break;
		case '<': {
			mqueue.push(cmd_reg(1));
		} break;
		case 'P': {
			val_t printed = (instr.size() == 1) ? pop_one() : cmd_reg(1);
			io << printed << '\n';
		} break;
		case 'C': {
			char printed = (instr.size() == 1) ? pop_one() : cmd_reg(1);
			io << printed;
		} break;
		case ':': {
			// pass (no need to execute a label definition)
		} break;
		case 'J': {
			ip = cmd_label_ip(1);
		} break;
		case 'Z': {
			if (cmd_reg(1) == 0) {
				ip = cmd_label_ip(2);
			}
		} break;
		case 'E': {
			if (cmd_reg(1) == cmd_reg(2)) {
				ip = cmd_label_ip(3);
			}
		} break;
		case 'G': {
			if (cmd_reg(1) > cmd_reg(2)) {
				ip = cmd_label_ip(3);
			}
		} break;
		case 'Q': {
			is_terminating = true;
		} break;
	}
}


int main() {
	auto cin = ifstream("input.txt");

	// load program and mark labels (first pass)
	string instr;
	int i = 0;
	while (cin >> instr) {
		if (instr[0] == ':') {
			labels[instr.substr(1)] = i + 1;
		}
		prog[i++] = instr;
	}

	// i is now size of the program
	// start executing it
	while (!is_terminating) {
		instr = prog[ip++];
		exec(instr);
		if (ip == i) {
			// reached end of program
			break;
		}
	}

	cin.close();
	return 0;
}
