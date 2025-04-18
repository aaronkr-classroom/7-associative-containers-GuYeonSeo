#include <cctype> //isspace()
#include <iostream>
#include <string>
#include <vector>

using namespace std;

typedef string::size_type str_sz;

vector<string> split(const string& s) {
	vector<string> ret;
	str_sz i = 0;

	//불변성 : 지금까지 [원래의 i, 현재의 i]범위에 있는 문자영을 처리
	while (i != s.size()) {
		//선행하는 공백들을 무시
		//불변성 : 지금까지 [원래의 i, 현재의 i]범위에 있는 문자들은 모두 공백
		while (i != s.size() && isspace(s[i])) {
			++i;
		}
		//순서상 다음 단어의 끝을 처음
		str_sz j = i;
		//불변성 : 지금까지 [원래의 j, 현재의 j]범위에 있는 문자들은 모두 공백이 아님
		while (j != s.size() && !isspace(s[j])) {
			j++;
		}
		//공백이 아닌 문자들을 찾았을때
		if (i != j) {
			//i에서부터 j-i개의 문자들을 s에 복사
			ret.push_back(s.substr(i, j - i));
			i = j;
		}
	}
	return ret;
}
