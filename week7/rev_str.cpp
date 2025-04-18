//rev_str.cpp
#include <iostream>
#include <string>

using namespace std;

void rev_str(string & s, int start, int end) {
	if (start >= end) //Áß¾Ó À§Ä¡·ê ³Ñ¾úÀ½
		return;

	char temp = s[start];
	s[start] = s[end];
	s[end] = temp;

	//Àç±ÍÀû ´Ü°è
	rev_str(s, start + 1, end - 1);
}

int main() {
	string s;
	cout << "Enter a string : ";
	cin >> s;

	rev_str(s, 0, s.length() - 1);

	cout << "Reversed string : " << s << endl;
	
	return 0;
}