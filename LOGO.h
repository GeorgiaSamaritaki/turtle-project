#include "hy352_gui.h"
#include <stdio.h>
#include <stdio.h>
#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <cstdarg>
#include <stack>

using namespace std;


#define START_PROGRAM int main(){ cout << "hello"; 
#define END_PROGRAM return 0;}
class array_l;

template <class T> T& get_l_type();

class l_types {
	string type;
public:
	l_types(string t = "undefined") : type(t) {}

	virtual l_types& get(int i = -1) = 0;
	virtual void set(int i, l_types* item) = 0;
	
	virtual l_types* clone() const = 0;
	virtual void print() const { std::cout << "Base"; }
	virtual ~l_types() {};
};


class l_NUMBER: public l_types{
	int number;
public:
	l_NUMBER(int a = 0) : l_types("Number"), number(a) {}
	
	operator int(){
		return number;
	}

	l_NUMBER& operator=(int i){
		number = i;
		return *this;
	}
	/*
	l_NUMBER operator+(const l_NUMBER i) {
		return this->number + i.number;
	}
	l_NUMBER operator-(const l_NUMBER i) {
		return this->number - i.number;
	}
	*/

	l_types& get(int i = -1) override {
		return *this;
	}
	virtual void set(int i, l_types* item) override{
		number = *dynamic_cast<l_NUMBER *> (item);
	}

	virtual void print() const override { std::cout << "Derived"; }

	l_types* clone() const override{
		return new l_NUMBER(this->number);  
	}
};

class l_BOOLEAN : public l_types{
	bool boolean;
public:
	l_BOOLEAN(bool b = NULL ) : l_types("Bool"), boolean(b) {}

	void operator= (void* i) { boolean = (int)i; }

	operator bool() {
		return boolean;
	}
	l_BOOLEAN& operator=(bool b) {
		boolean = b;
		return *this;
	}
	l_types& get(int i = -1) override {
		return *this;
	}
	virtual void set(int i, l_types* item) override {
		boolean = *dynamic_cast<l_BOOLEAN *> (item);
	}
	void displayInfo(ostream& os = cout) const {
		os <<"Boolean" << boolean;
	}
	l_types* clone() const override {
		return new l_BOOLEAN(this->boolean);
	}
};

class l_WORD : public l_types{
	string str;
public:

	l_WORD(string _str = "") : l_types("String"), str(_str) {}
	l_WORD(l_WORD *l) : l_types("String"), str((*l).str) {}

	operator string() {
		return *this;
	}
	l_WORD& operator=(string s){
		str.assign(s);
		return *this;
	}
	l_types& get(int i = -1) override {
		return *this;
	}
	virtual void set(int i, l_types* item) override {
		*this = *dynamic_cast<l_WORD *> (item); // equality is overwritten
	}
	
	void displayInfo(ostream& os = cout) const {
		os <<"Word"<< this;
	}

	l_types * clone() const override {
		return new l_WORD(*this);
	}
	
};

class tmp_group_l : public vector<l_types*> {
public:
	tmp_group_l(){};

	tmp_group_l& operator,(l_types &b) {
		push_back(&b);
		return *this;
	};

};


tmp_group_l& operator,(l_types &a, l_types &b) {
	tmp_group_l* arr = new tmp_group_l();
	arr->push_back(&a);
	arr->push_back(&b);
	return *arr;
};
tmp_group_l& operator,(const l_types &a, const l_types *b) {
	tmp_group_l* arr = new tmp_group_l();
	//arr->push_back(&a);
	//arr->push_back(&b);
	return *arr;
};


class array_l : public l_types, public vector<l_types *> {
public:
	
	array_l():l_types("Array"){};
	array_l(const array_l &l) :l_types("Array") {
		for (auto x : l) this->push_back((*x).clone());
	}
	
	template <class T>
	typename enable_if<is_base_of<l_types, T>::value, array_l&>::type
	operator=( initializer_list<T> l ) {
		this->clear();
		for(auto x:l) push_back(x.clone());
		return *this;
	}

	l_types& get(int i) {
		return *at(i);
	}
	void set(int i, l_types* item) {
		at(i) = item;
	}
	void displayInfo(ostream& os = cout) const {
		os << "meh";
	}
	l_types* clone() const override {
		return new array_l(*this);
	}

};

class list_l : public l_types, public vector<l_types*>{
public:

	list_l() :l_types("List") {};
	list_l(const list_l &l) :l_types("List") {
		for (auto x : l) this->push_back((*x).clone());
	};

	list_l& operator[](tmp_group_l &arr) {
		assign(arr.begin(), arr.end());
		return *this;
	}
	list_l& operator[](l_types *l) {
		push_back(l);
		return *this;
	}

	l_types& get(int i = -1) {
		//check size
		return *at(i);
	}
	virtual void set(int i, l_types* item) override {
		at(i) = item;
	}
	list_l& get_List() {
		return *this;
	}
	void displayInfo(ostream& os = cout) const {
		os << "meh";
	}
	l_types* clone() const override {
		return new list_l(*this);
	}
	
};

class sentence_l : public l_types, public vector<l_WORD *> {
public:

	sentence_l() :l_types("Sentence") {};

	//theres defntl a better way to do this
	template<typename ... following>
	sentence_l(l_WORD arg, const following&... rest) {
		this->push_back(dynamic_cast<l_WORD*> (arg.clone()));
		add(rest...);
	}
	
	template<typename ... following>
	void add(l_WORD arg, const following&... rest) {
		this->push_back(dynamic_cast<l_WORD*> (arg.clone()));
		add(rest...);
	}
	void add() {};

	l_types& get(int i = 0) {
		//check size
		return *at(i);
	}
	virtual void set(int i, l_types* item) override {
		at(i) = dynamic_cast<l_WORD*> (item);
	}

	void displayInfo(ostream& os = cout) const {
		os << "meh";
	}

	l_types* clone() const override {
		return new sentence_l(*this);
	}
};

l_types& item_l(initializer_list<l_NUMBER *> list, array_l& array) {
	l_types& item = array;
	for (auto i : list) item = item.get(*i);
	return item;
}

void setitem_l(initializer_list<l_NUMBER *> list, array_l* array, l_types* new_value) {
	l_NUMBER* i =  *list.begin();
	array->set( *i - 1, new_value);
}

l_NUMBER sum_l(l_NUMBER a, l_NUMBER b, l_NUMBER c = 0) { return a + b + c; }

l_NUMBER difference_l(l_NUMBER a, l_NUMBER b) {	return a - b; }

l_NUMBER minus_l(l_NUMBER a) { return a * (-1); }

l_NUMBER product_l(l_NUMBER a, l_NUMBER b = 1, l_NUMBER c = 1) { return a * b * c; }

l_NUMBER quotient_l(l_NUMBER a, l_NUMBER b) { 
	if (b == 0) return 0;
	return a / b; 
}

l_NUMBER modulo_l(l_NUMBER a, l_NUMBER b) {	return a % b; }

template<typename... REST > 
l_BOOLEAN and_l(l_BOOLEAN first, const REST&... rest){
	return first && and_l(rest...);
}
l_BOOLEAN and_l() { return true; }

template<typename... REST >
l_BOOLEAN or_l(l_BOOLEAN first, const REST&... rest) {
	return first || and_l(rest...);
}
l_BOOLEAN or_l() { return false; }

class varstack {
private:
	stack<int *> s;
	int ifcount;
	static varstack *s_instance;
	varstack() { 
		ifcount = 0; 
	};
public:
	static varstack *instance(){
		if (!s_instance) 
			s_instance = new varstack();
		return s_instance;
	}

	void push(int *i) {
		s.push(i);
	}
	void pop() {
		if(ifcount == 0) s.pop();
		else ifcount--;
	}
	int top() {
		return  *s.top();
	}
	void ifcalled() {
		ifcount++;
	}
	void increment() {
		(*s.top())++;
	}

};
varstack *varstack::s_instance = 0;

#define TRUE true
#define FALSE false
#define MAKE auto

#define NUMBER (*new l_NUMBER()) = 0? 0
#define WORD (*new l_WORD()) = 0? ""
#define BOOLEAN (*new l_BOOLEAN()) = 0? true
#define LIST (*new list_l())
#define ARRAY (* new array_l() ) = 
#define SENTENCE new sentence_l
				//intentionally left blank  
#define AND and_l;
#define OR or_l;
#define ELIF elseif(
#define IF	varstack::instance()->ifcalled(); \
			if(
#define DO ){ 
#define END  }; varstack::instance()->pop();

#define ASSIGN 
#define SUM sum_l
#define DIFFERENCE difference_l
#define SETITEM setitem_l
#define ITEM item_l
#define MINUS minus_l
#define QUOTIENT quotient_l
#define MODULO modulo_l


#define REPEAT	varstack::instance()->push(new int()); for(  ;(varstack::instance()->top()) < (
#define TIMES ); varstack::instance()->increment()
#define REPCOUNT varstack::instance()->top() + 1


