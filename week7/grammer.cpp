//grammer.cpp
#include <algorithm> //find()
#include <cstdlib> //RAND_MAX정의
#include <stdexcept> //domain_error, ...
#include <ctime>

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>

#include "split.h"

using namespace std;

typedef vector<string> Rule;
typedef vector<Rule> Rule_collection;
typedef map<string, Rule_collection> Grammer;

//주어진 입력 스트림으로 문법 테이블 읽음
Grammer read_grammer(istream& in) {
	Grammer ret;
	string line;

	ifstream grammer_file("grammar.txt"); //에런 추가

	//입력 데이터를 읽음
	while (getline(grammer_file, line)) {
		//입력 데이터를 단어로 나눔
		vector<string> entry = split(line);
		if (!entry.empty()) {
			//카테고리 및 연관된 규칙을 맵에 저장
			ret[entry[0]].push_back(Rule(entry.begin() + 1, entry.end()));
		}
	}
	return ret;
}

//꺽쇠호 있는지 확인
bool bracketed(const string& s) {
	//<...>? = true
	return s.size() > 1
		&& s[0] == '<' && s[s.size() - 1] == '>';
}

//[0, n)범위에서 임의의 정수 하나를 반환
int nrand(int n) {
	if (n <= 0 || n > RAND_MAX)
		throw domain_error("nrand is out of range!");

	const int bucket_size = RAND_MAX / n;
	int r;
	do r = rand() / bucket_size; //무조건 한번 이상 실행
	while (r >= n);

	return r;
}

//문법 사용하고 문장 생성하기
void gen_aux(const Grammer& g, const string& word, vector<string>& ret) {
	if (!bracketed(word))
		ret.push_back(word); //일반적인 단어

	else{ // <있는 단어(문법 규칙)
		//word와 연관된 규칙을 찾음
		Grammer::const_iterator it = g.find(word);

		if (it == g.end())//벌써 끝나요?
			throw logic_error("Empty rule!");

		//선택 가능한 규칙을 모아 놓은 벡터를 가져옴
		const Rule_collection& c = it->second;

		//임의로 하나를 선택
		const Rule& r = c[nrand(c.size())];

		//선택한 규칙을 재귀적으로 확장
		for (Rule::const_iterator i = r.begin();
			i != r.end(); ++i) {
			gen_aux(g, *i, ret); //재귀적 호출
		}
	}
}

//일반적으로 문장 생성하기
vector<string> gen_sent(const Grammer& g) {
	vector<string> ret;
	gen_aux(g, "<sentence>", ret);
	return ret;
}

//MAIN
int main(){
	//send the random number generator with current time
	srand(static_cast<unsigned int> (time(0)));

	//문장 생성
	vector<string> sentence = gen_sent(read_grammer(cin));

	//첫번째 단어 출력
	vector<string>::const_iterator it = sentence.begin();
	if (!sentence.empty()) {
		cout << *it;
		++it;
	}
	//공백과 함께 나머지 단어 출력
	while (it != sentence.end()) {
		cout << " " << *it;
		++it;
	}
	cout << endl;

	return 0;
}