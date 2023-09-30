#include<iostream>
#include<string>
#include<unordered_map>
#include<algorithm>
using namespace std;

unordered_map<string, string> u = {
	{"ADD" ,"00000" },
	{"ADDC" ,"00001" },
	{"SUB" ,"00010" },
	{"SUBC" ,"00011" },
	{"MOV" ,"00100" },
	{"MOVC" ,"00101" },
	{"AND" ,"00110" },
	{"ANDC" ,"00111" },
	{"OR" ,"01000" },
	{"ORC" ,"01001" },
	{"NOT" ,"01010" },
	{"MULT" ,"01100" },
	{"MULTC" ,"01101" },
	{"LSFTL" ,"01110" },
	{"LSFTLC" ,"01111" },
	{"LSFTR" ,"10000" },
	{"LSFTRC" ,"10001" },
	{"ASFTR" ,"10010" },
	{"ASFTRC" ,"10011" },
	{"RL" ,"10100" },
	{"RLC" ,"10101" },
	{"RR" ,"10110" },
	{"RRC" ,"10111" },
};
string makebinary(int a, int size) {
	string tmp = "";
	while (a) {
		if (a & 1) {
			tmp += '1';
		}
		else {
			tmp += '0';
		}
		a = a >> 1;
	}
	reverse(tmp.begin(), tmp.end());
	while (tmp.size() < size) {
		tmp.insert(0, "0");
	}
	return tmp;
}
int main() {
	
	int tc;
	scanf("%d", &tc);
	for (int T = 0; T < tc; T++) {
		string result = "";
		string opcode = "";
		int rD, rA, rBorC;
		cin >> opcode >> rD >> rA >> rBorC;

		result += u[opcode]; // 0 ~ 4
		result += '0'; // 5
		result += makebinary(rD,3); // 6 ~ 8
		result += makebinary(rA,3); // 9 ~ 11
		if (result[4] == '0') { // 12 ~ 15
			result += makebinary(rBorC,3);
			result += '0';
		}
		else {
			result += makebinary(rBorC,4);
		}

		cout << result << endl;

	}



}
