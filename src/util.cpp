#pragma once

#include <string>
#include <vector>
using namespace std;

// malloc, exit:
#include <cstdlib>
// strcmp
#include <string.h>
#include <regex.h>

#include "util.hpp"

bool assert(bool test, char* what) {// bool nix gut
	printf("----\nTEST ");
	printf(what);
	if (test) {
		printf(" OK\n");
		flush();
	}
	if (!test) {
		printf(" Failed\n");
		printf(" runs : ");
		pi(runs);
		flush();
		if (exitOnFailure != false)exit(1);
	}
	recursions = 0; // reset!
	return test;
}

bool isNumber(char* buf) {
	return strlen(buf) == strspn(buf, "0123456789,.");
}

string next(string data) {
	int spc = data.find(" ");
	if (spc >= 0)
		return data.substr(spc + 1);
	return data;
}

char* substr(char* what, int from, int to) {
#ifndef DEBUG
	if (from > to)
		return what; // ERROR!!
#endif
	char *result = (char*) malloc(to - from + 1);
	strncpy(result, what + from, to - from);
	result[to - from] = 0; // In case of unclean malloc
	return result;
}

char* tolower(const char* x) {
	char* neu = (char*) malloc(strlen(x));
	for (int i = 0; i < strlen(x); i++) {
		neu[i] = tolower(x[i]);
	}
	return neu;
}

bool contains(const char* x, char y) {
	for (int i = 0; i < strlen(x); i++)
		if(x[i]==y)return true;
	return false;
}


bool contains(const char* x, const char* y, bool ignoreCase) {
	// Sonderfall: contains("abc","")==false
	if (strlen(y) == 0)return false;
	if (ignoreCase)return strstr(tolower(x), tolower(y));
	return strstr(x, y);
}

template<typename T>
void empty(vector<T, std::allocator<T> > &v) {
	v.erase(v.begin(), v.end());
}

template void empty(vector<Statement*, std::allocator<Statement* > > &v);
//bool contains(vector<Node*>& all,Node* node){
//    for(int i=0;i<all.size();i++){
//      if((Node*)all[i]==node)return true;
//    }
//    return false;
//}

bool contains(vector<Node*> all, Node* node) {
	for (int i = 0; i < all.size(); i++) {
		if ((Node*) all[i] == node)return true;
		if (eq(all[i], node))return true;
	}
	return false;
}

bool contains(vector<char*>& all, char* node) {
	for (int i = 0; i < all.size(); i++) {
		char* ali = all[i];
		if (eq(ali, node))return true;
	}
	return false;
}

bool contains(string x, const char* y) {
	return x.find(string(y)) != string::npos;
}

string replace_all(string str, string what, string with) {
	int idx = 0;
	while ((idx = str.find(what, idx)) >= 0) {
		str.replace(idx, what.length(), with);
		idx = idx + with.length() + 1;
	}
	return str;
}

bool quiet = false;

//void flush(){
//   fflush(stdout);
//}

bool isInteger(char* buf) {
	return strlen(buf) == strspn(buf, "0123456789");
}

bool startsWith(const char* x, const char* y) {
	for (int i = 0; i < min(strlen(x), strlen(y)); i++) {
		if (x[i] != y[i])return false;
	}
	return true;
}

bool startsWith(string* x, const char* y) {
	return x->find(y) >= 0;
}

// tolower

bool eq(const char* x, const char* y, bool ignoreCase) {

	if (!x && !y)return true; //danger better: undefined?
	if (!x || !y)return false; //danger better: undefined?
	if(x==0 || y==0)return false;
	//	Context* c=currentContext();
	//	if(x<c->nodeNames || x >c->nodeNames+c->currentNameSlot){
	//		p("corrupt name!");
	//		return false;
	//	}
	//	if(y<c->nodeNames || y >c->nodeNames+c->currentNameSlot){
	//		p("corrupt name!");
	//		return false;
	//	}
	if (x && x[0] == 0 && y == 0)return true; // 0=='' danger!
	if (y && y[0] == 0 && x == 0)return true; // 0=='' danger!
	if (x == 0 || !y)return false;
	if (strcmp(x, y) == 0)return true;
	if (!ignoreCase)return false;
	int xl = strlen(x);
	if (xl != strlen(y))return false; // xl!=strlen(y) != !xl==strlen(y) !!!!!
	int i = 0;
	for (; i < xl; i++) {
		if (y[i] == 0 || tolower(x[i]) != tolower(y[i]))
			return false;
	}
	//    for(int i=0;i<strlen(y);i++)y0[i]=tolower(y[i]);
	//    return(strcmp(x0,y0)==0);// free?
	return true;
}

string join(char** argv, int argc) {
	string a;
	int i = 1;
	for (; i < argc; i++) {
		a = a + argv[i] + " ";
	}
	return a;
}

Node* eq(Node* x, Node* y) {
	return isEqual(x, y);
}

bool eq(string x, const char* y) {
	return (strcmp(x.c_str(), y) == 0);
}

bool eq(string* x, const char* y) {
	return (strcmp(x->c_str(), y) == 0);
}

void ps(string s) {// string geht nicht!?!
	if (quiet)return;
	printf("%s\n", s.c_str());
	fflush(stdout);
}

void ps(NodeVector v) {
	if (quiet)return;
	for (int i = 0; i < v.size(); i++)
		show(v[i]);
}

void ps(string* s) {
	if (quiet)return;
	printf("%s\n", s->c_str());
	fflush(stdout);
}

void ps(char* s) {
	if (quiet)return;
	printf("%s\n", s);
	fflush(stdout);
}

void pi(int i) {
	if (quiet)return;
	printf("%i\n", i);
	fflush(stdout);
}

void pl(long l) {
	if (quiet)return;
	printf("%lu\n", l);
	fflush(stdout);
}

// 64 bit hex value

void px(void* p) {
	if (quiet)return;
	printf("%016llX\n", p);
	fflush(stdout);
}

void p(char* s) {
	if (quiet)return;
	printf("%s\n", s);
	fflush(stdout);
}

void p(Node* n) {
	show(n);
}

void p(Query& q) {
	p("Query:");
	show(q.keyword);
	ps(q.keywords);
}


// todo: presorted jumplists

NodeVector intersect(NodeVector a, NodeVector b) {
	NodeVector c;
	for (int i = 0; i < a.size(); i++) {
		Node* n = a[0];
		if (contains(b, n))c.push_back(n);
	}
}

vector<char*>& splitString(string line0, const char* separator) {
	return splitString(line0.data(), separator);
	;
}

vector<char*>& splitString(const char* line0, const char* separator) {
	char * token;
	vector<char*>& v = *new vector<char*>;
	if (line0 == 0) {
		ps("empty splitString!");
		return v;
	}
	char* line = (char*) malloc(strlen(line0)*2 + 1); //dont free!
	strcpy(line, line0);
	token = strtok(line, separator);
	int row = 0;
	while (token != NULL) {
		v.push_back(token);
		token = strtok(NULL, separator);
	}
	//free(line);// ja? NEIN: incorrect checksum for freed object - object was probably modified after being freed.
	return v;
}


// no empty fields: treats a||b as a|b -- !
int splitStringC2(char* str, char** tokens, const char* separators, int count) {
	int row = 0;
//	printf("Splitting string \"%s\" into tokens:\n", str);
	char * token;
	token = strtok(str, separators);
	while (token != NULL) {
		tokens[row++] = token;
		token = strtok(NULL, separators);
	}
	return row + 1; //s
}

int splitStringC(char* line, char** tokens, const char* separators, int count) {
	char * token;
	//  token = strtok (line,separator);
	int row = 0;
	int len = strlen(line);
	char* lastgood = line;
	for (int i = 0; i < count; i++)tokens[i] = 0;
	int i = 0;
	while (i < len) {
		if (contains(separators, line[i])) {//(const char*) (line + i)
			token = lastgood;
			line[i] = 0; // cut c style
			lastgood = &line[i + 1];
			tokens[row] = token;
			//        token = strtok (NULL, separator);
			row++;
		}
		i++;
	}
	tokens[row] = lastgood;
	return row + 1; //s
}

inline int normChar(int c) {
	switch (c) {
		case '_':return 0;
			break;
		case ' ':return 0;
			break;
		case '-':return 0;
			break;
		default: return tolower(c);
	}
}

//unsigned long hash(const char *str) {// unsigned

unsigned int hash(const char *str) {// unsigned
	if (!str)return 0;
	unsigned long hash = 5381;
	int c;
	while (c = *str++) hash = ((hash << 5) + hash) + normChar(c); /* hash * 33 + c */
	int pos = hash % maxNodes;
	return abs(pos);
}

string stem(string word) {
	word = "|^" + word + "$|";
	word = replace_all(word, "_", " ");
	word = replace_all(word, "s$", "$");
	word = replace_all(word, "$|", "");
	word = replace_all(word, "|^", "");
	return word;
}


// call by object => destination unmodified!   (how) expensive?!

void addRange(NodeVector& some, NodeVector more) {// bool keep destination unmodified=TRUE
	for (int i = 0; i < more.size(); i++) {
		if (!contains(some, (Node*) more[i]))
			some.push_back(more[i]);
	}
}

NodeVector mergeVectors(NodeVector some, NodeVector more) {// bool keep destination unmodified=TRUE
	for (int i = 0; i < more.size(); i++) {
		if (!contains(some, (Node*) more[i]))
			some.push_back(more[i]);
	}
	return some;
}


//bool contains(NodeVector v, Node* o) {
//    for (int i = 0; i < v.size(); i++) {
//        Node* n = (Node*) v[i];
//        if (n == o)return true;
//    }
//    return false;
//}

int charCount(char*__, char c) {
	int ___ = 0;
	while (*__)___ = c == *__++ ? ___ + 1 : ___;
	return ___;
}//lol


// for non-greedy use something like <([^>]+)>
// or this: //#define MINMOD	29	/* no	Next operator is not greedy. */
// USE [a-z] instead of \\w !!!

char* match(char* input, char* pattern) {
	int groups = charCount(pattern, '(');
	regmatch_t matches[groups + 1]; // matches[0] == whole pattern
	regex_t regex;
	int error = regcomp/*ile*/(&regex, pattern, REG_EXTENDED);
	if (error)return 0; //perror("regcomp failed");//regerror(status,REG_NOSUB)
	error = regexec(&regex, input, groups + 1, &matches[0], 0);
	if (error)return 0; //perror("regexec failed");
	int from = matches[groups].rm_so;
	int to = matches[groups].rm_eo;
	if (from > to)return 0;
	char *group = substr(input, from, to);
	regfree(&regex);
	return group;
}