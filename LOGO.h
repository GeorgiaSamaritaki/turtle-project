#include "hy352_gui.h"
#include <stdio.h>
#include <stdio.h>
#include<iostream>
#include <list>
#include <vector>
#include <cstdarg>

using namespace std;


#define START_PROGRAM int main(){ cout << "hello"; 
#define END_PROGRAM return 0;}
class array_l;

class l_types{
	string type;
public:
	l_types(string t = "undefined"): type(t){}

	std::ostream &operator<<(std::ostream &os) {
		return os << type;
	}
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
};
class l_WORD : public l_types, public string{
public:

	l_WORD(string str = "") : l_types("String"), string(str) {}
	operator string() {
		return *this;
	}
	l_WORD& operator=(string s){
		string::assign(s);
		return *this;
	}
};

class array_l : public l_types, public vector<l_types> {
public:
	
	array_l():l_types("Array"){};


	/*
	template<typename T> array_l operator,(T a) {
		l_types* l;
		if (is_same<T, int>::value) {
			l = new l_NUMBER((int)a);
		} else if (is_same<T, bool>::value) {
			new l_BOOLEAN((bool)a);
		} else if (is_same<T, string>::value) {
			new l_WORD((string)a);
		}
		push_back(l);
		return *this;
	}*/

	array_l operator=(array_l* vec2) {
		this->clear();
		for (size_t i = 0; i < this->size(); i++)
			vec2->push_back(this[i]);
		return *this;
	}
	array_l operator=(initializer_list<l_types> l) {
		this->clear();
		insert(end(), l.begin(), l.end());
		return *this;
	}
};

class tmp_group : public vector<l_types> {
public:
	tmp_group(){};

	tmp_group& operator,(l_types &b) {
		push_back(b);
		return *this;
	};
};


tmp_group& operator,(l_types &a, l_types &b) {
	tmp_group* arr = new tmp_group();
	arr->push_back(a);
	arr->push_back(b);
	return *arr;
};

class list_l : public l_types, public vector<l_types>{
public:

	list_l() :l_types("List") {};

	list_l& operator[](tmp_group &arr) {
		assign(arr.begin(), arr.end());
		return *this;
	}
	list_l& operator[](l_types &l) {
		push_back(l);
		return *this;
	}
	list_l& get_List() {
		return *this;
	}

};

#define TRUE true
#define FALSE false
#define MAKE auto
#define NUMBER (*new l_NUMBER()) = 0? 0
#define WORD (*new l_WORD()) = 0? ""
#define BOOLEAN (*new l_BOOLEAN()) = 0? true
#define LIST (*new list_l())
#define ARRAY (* new array_l() ) = 