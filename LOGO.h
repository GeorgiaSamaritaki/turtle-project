#include "hy352_gui.h"
#include <stdio.h>
#include <stdio.h>
#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <cstdarg>
#include <initializer_list>
#include <stack>
#include <cmath>

using namespace std;
class array_l;
class l_BOOLEAN;


class l_types {
	string type;
public:
	l_types(string t = "undefined") : type(t) {}
	string gettype() { return type; }
	/*
	template<class T, bool _Test = is_base_of<l_types, T> >
	enable_if <  _Test, l_BOOLEAN& >
	 transform(l_BOOLEAN& a) { return a;}
	*/

	virtual l_BOOLEAN operator==(l_types& l) const = 0;
	virtual l_BOOLEAN operator>=(l_types& l) const = 0;
	virtual l_BOOLEAN operator<=(l_types& l) const = 0;
	virtual l_BOOLEAN operator!=(l_types& l) const = 0;
	virtual l_BOOLEAN operator>(l_types& l) const = 0;
	virtual l_BOOLEAN operator<(l_types& l) const = 0;

	virtual l_types& get(int i = -1) = 0;
	virtual void set(int i, l_types* item) = 0;
	virtual void show_l() const = 0;
	virtual l_types* clone() const = 0;

	virtual ~l_types() {};
};

class l_BOOLEAN : public l_types {
	bool boolean;
public:
	l_BOOLEAN(bool b = NULL) : l_types("Bool"), boolean(b) {}

	operator bool() {
		return boolean;
	}
	l_BOOLEAN& operator=(bool b) {
		boolean = b;
		return *this;
	}


	l_types& get(int i = -1) override {
		return *this;
	};

	virtual void set(int i, l_types* item) override {
		boolean = *dynamic_cast<l_BOOLEAN *> (item);
	}
	void displayInfo(ostream& os = cout) const {
		os << "Boolean" << boolean;
	}
	void show_l() const override {
		cout << "(BOOLEAN: " << boolean << ") ";
	}

	l_BOOLEAN* clone() const override {
		return new l_BOOLEAN(this->boolean);
	}

	virtual l_BOOLEAN operator==(l_types& l) const override {
		return l_BOOLEAN(this->boolean == dynamic_cast<l_BOOLEAN&>(l).boolean);
	}
	virtual l_BOOLEAN operator!=(l_types& l) const override {
		return l_BOOLEAN(this->boolean != dynamic_cast<l_BOOLEAN&>(l).boolean);
	}
	virtual l_BOOLEAN operator>=(l_types& l) const override { return operator==(l);}
	virtual l_BOOLEAN operator<=(l_types& l) const override { return operator==(l);}
	virtual l_BOOLEAN operator>(l_types& l) const override  { return operator!=(l);}
	virtual l_BOOLEAN operator<(l_types& l) const override  { return operator!=(l);}
};

class l_NUMBER : public l_types {
	double number;
public:
	l_NUMBER(double a = 0) : l_types("Number"), number(a) {}
	l_NUMBER(int a) : l_types("Number"), number(a) {}

	operator double() {
		return number;
	}

	l_NUMBER& operator=(double i) {
		number = i;
		return *this;
	}

	virtual l_BOOLEAN operator==(l_types& l) const override {
		return l_BOOLEAN(this->number == dynamic_cast<l_NUMBER&>(l).number);
	}
	virtual l_BOOLEAN operator!=(l_types& l) const override {
		return l_BOOLEAN(this->number != dynamic_cast<l_NUMBER&>(l).number);
	}
	virtual l_BOOLEAN operator>=(l_types& l) const override {
		return l_BOOLEAN(this->number >= dynamic_cast<l_NUMBER&>(l).number);
	}
	virtual l_BOOLEAN operator<=(l_types& l) const override {
		return l_BOOLEAN(this->number <= dynamic_cast<l_NUMBER&>(l).number);
	}
	virtual l_BOOLEAN operator>(l_types& l) const override {
		return l_BOOLEAN(this->number > dynamic_cast<l_NUMBER&>(l).number);
	}
	virtual l_BOOLEAN operator<(l_types& l) const override {
		return l_BOOLEAN(this->number < dynamic_cast<l_NUMBER&>(l).number);
	}

	l_types& get(int i = -1) override {
		return *this;
	};

	virtual void set(int i, l_types* item) override {
		number = *dynamic_cast<l_NUMBER *> (item);
	}

	void show_l() const override {
		cout << "(NUMBER:" << number << ") ";
	}

	l_NUMBER* clone() const override {
		return new l_NUMBER(this->number);
	}
};


class l_WORD : public l_types {
	string str;
public:

	l_WORD(string _str = "") : l_types("String"), str(_str) {}
	l_WORD(l_WORD *l) : l_types("String"), str((*l).str) {}

	operator string() {
		return *this;
	}
	l_WORD& operator=(string s) {
		str.assign(s);
		return *this;
	}

	virtual l_BOOLEAN operator==(l_types& l) const override {
		return str.compare(dynamic_cast<l_WORD&>(l).str) == 0;
	}

	virtual l_BOOLEAN operator!=(l_types& l) const override { return str.compare(dynamic_cast<l_WORD&>(l).str) != 0; }
	virtual l_BOOLEAN operator>=(l_types& l) const override { return str.compare(dynamic_cast<l_WORD&>(l).str) >= 0; }
	virtual l_BOOLEAN operator<=(l_types& l) const override { return str.compare(dynamic_cast<l_WORD&>(l).str) <= 0; }
	virtual l_BOOLEAN operator>(l_types& l) const override { return str.compare(dynamic_cast<l_WORD&>(l).str) > 0; }
	virtual l_BOOLEAN operator<(l_types& l) const override { return str.compare(dynamic_cast<l_WORD&>(l).str) < 0; }
	

	l_WORD& get(int i = -1) override {
		return *this;
	};

	const char *getcstring() {
		return str.c_str();
	}

	virtual void set(int i, l_types* item) override {
		*this = *dynamic_cast<l_WORD *> (item); // equality is overwritten
	}

	void show_l() const override {
		cout << "(WORD: " << str << ") ";
	}

	l_WORD* clone() const override {
		return new l_WORD(*this);
	}

};

class tmp_group_l : public vector<l_types*> {
public:
	tmp_group_l() {};

	tmp_group_l& operator,(l_types &b) {
		push_back(&b);
		return *this;
	};
	tmp_group_l& operator,(l_types *b) {
		push_back(b);
		return *this;
	};
};

tmp_group_l& operator,(l_types &a, l_types &b) {
	tmp_group_l* arr = new tmp_group_l();
	arr->push_back(&a);
	arr->push_back(&b);
	return *arr;
};


class array_l : public l_types, public vector<l_types *> {

	template <class T, typename... REST >
	typename enable_if<is_base_of<l_types, T>::value, void>::type
		create_array(T first, const REST&... rest) {
		push_back((dynamic_cast<l_types *>(&first))->clone());
		create_array(rest...);
	}
	void create_array() {  }

public:

	array_l() :l_types("Array") {};
	array_l(const array_l &l) :l_types("Array") {
		for (auto x : l) this->push_back((*x).clone());
	}

	template<typename... Args>
	array_l(Args...args) {
		create_array(args...);
	}

	array_l& operator=(array_l *l) {
		this->clear();
		for (auto x : *l) push_back((*x).clone());
		return *this;
	}

	virtual l_BOOLEAN operator==(l_types& l) const override {
		return this->operator==(dynamic_cast<array_l&>(l));
	}

	virtual l_BOOLEAN operator!=(l_types& l) const override { return this->operator!=(dynamic_cast<array_l&>(l));}
	virtual l_BOOLEAN operator>=(l_types& l) const override { return this->operator>=(dynamic_cast<array_l&>(l));}
	virtual l_BOOLEAN operator<=(l_types& l) const override { return this->operator<=(dynamic_cast<array_l&>(l));}
	virtual l_BOOLEAN operator>(l_types& l) const override	{ return this->operator>(dynamic_cast<array_l&>(l));}
	virtual l_BOOLEAN operator<(l_types& l) const override	{ return this->operator<(dynamic_cast<array_l&>(l));}


	array_l& get() {
		return *this;
	}
	l_types& get(int i) {
		return *at(i);
	}
	void set(int i, l_types* item) {
		at(i) = item->clone();
	}

	void show_l() const override {
		cout << "Array { ";
		for (auto i : *this) i->show_l();
		cout << "}" << endl;
	}

	array_l* clone() const override {
		return new array_l(*this);
	}

};

class list_l : public l_types, public vector<l_types*> {
public:

	list_l() :l_types("List") {};
	list_l(const list_l &l) :l_types("List") {
		for (auto x : l) this->push_back((*x).clone());
	};

	list_l& operator[](tmp_group_l &arr) {
		assign(arr.begin(), arr.end());
		return *this;
	}
	list_l& operator[](l_types &l) {
		push_back(&l);
		return *this;
	}

	virtual l_BOOLEAN operator==(l_types& l) const override {
		return this->operator==(dynamic_cast<list_l&>(l));
	}
	virtual l_BOOLEAN operator!=(l_types& l) const override { return this->operator!=(dynamic_cast<list_l&>(l));}
	virtual l_BOOLEAN operator>=(l_types& l) const override { return this->operator>=(dynamic_cast<list_l&>(l));}
	virtual l_BOOLEAN operator<=(l_types& l) const override { return this->operator<=(dynamic_cast<list_l&>(l));}
	virtual l_BOOLEAN operator>(l_types& l) const override	{ return this->operator>(dynamic_cast<list_l&>(l));}
	virtual l_BOOLEAN operator<(l_types& l) const override	{ return this->operator<(dynamic_cast<list_l&>(l));}

	list_l& get(){
		return *this;
	}

	l_types& get(int i) {
		//check size
		return *at(i);
	}
	l_types& get(l_types& l) {
		int i = dynamic_cast<l_NUMBER&>(l);
		return *at(i);
	}
	virtual void set(int i, l_types* item) override {
		at(i) = item->clone();
	}

	void show_l() const override {
		cout << "List[ ";
		for (auto i : *this) i->show_l();
		cout << "]" << endl;
	}

	list_l* clone() const override {
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

	l_types& get(int i) {
		//check size
		return *at(i);
	}

	virtual l_BOOLEAN operator==(l_types& l) const override {
		return this->operator==(dynamic_cast<sentence_l&>(l));
	}

	virtual l_BOOLEAN operator!=(l_types& l) const override { return this->operator!=(dynamic_cast<sentence_l&>(l)); }
	virtual l_BOOLEAN operator>=(l_types& l) const override { return this->operator>=(dynamic_cast<sentence_l&>(l)); }
	virtual l_BOOLEAN operator<=(l_types& l) const override { return this->operator<=(dynamic_cast<sentence_l&>(l)); }
	virtual l_BOOLEAN operator>(l_types& l) const override { return this->operator>(dynamic_cast<sentence_l&>(l)); }
	virtual l_BOOLEAN operator<(l_types& l) const override { return this->operator<(dynamic_cast<sentence_l&>(l)); }

	virtual void set(int i, l_types* item) override {
		at(i) = dynamic_cast<l_WORD*> (item);
	}

	void show_l() const override {
		cout << "Sentence: ";
		for (auto i : *this) i->show_l();
		cout << endl;
	}

	sentence_l* clone() const override {
		return new sentence_l(*this);
	}
};


l_types& item_l(initializer_list<l_NUMBER> list, const l_types& array) {
	l_types* item = const_cast<l_types*>(&array);
	for (auto i : list) item = &item->get(i - 1);
	return *item;
}

void setitem_l(initializer_list<l_NUMBER> list, l_types& array, l_types &new_value) {
	l_types& item = const_cast<l_types&>(array);
	unsigned int i;
	auto j = list.begin();
	for (i = 0; i < list.size() - 1; i++, j++)
		item = item.get((*const_cast<l_NUMBER*>(j)) - 1);

	item.set(*const_cast<l_NUMBER*>(j) - 1, &new_value);
}

l_NUMBER sum_l(l_types& a, l_types& b, l_types& c = *new l_NUMBER(0)) {
	return l_NUMBER(dynamic_cast<l_NUMBER&>(a) + dynamic_cast<l_NUMBER&>(b) + dynamic_cast<l_NUMBER&>(c));
}

l_NUMBER difference_l(l_types& a, l_types& b) { return l_NUMBER(dynamic_cast<l_NUMBER&>(a) - dynamic_cast<l_NUMBER&>(b)); }

l_NUMBER minus_l(l_types& a) { return l_NUMBER(dynamic_cast<l_NUMBER&>(a) * (-1)); }

l_NUMBER product_l(l_types& a, l_types& b, l_types& c = *new l_NUMBER(1)) {
	return l_NUMBER(dynamic_cast<l_NUMBER&>(a) * dynamic_cast<l_NUMBER&>(b) * dynamic_cast<l_NUMBER&>(c));
}

l_NUMBER quotient_l(l_types& a, l_types& b) {
	if (dynamic_cast<l_NUMBER&>(b) == 0) return 0;
	return l_NUMBER(dynamic_cast<l_NUMBER&>(a) / dynamic_cast<l_NUMBER&>(b));
}

l_NUMBER modulo_l(l_types& a, l_types& b) {
	return l_NUMBER(fmod(dynamic_cast<l_NUMBER&>(a), dynamic_cast<l_NUMBER&>(b)));
}


template<typename... Args>
l_BOOLEAN and_l(Args&...args) {
	return and_l(&args...);
}
template<class T, typename... REST >
l_BOOLEAN and_l(T first, const REST... rest) {
	return (bool)(first) && and_l(rest...);
}
l_BOOLEAN and_l() { return true; }

template<typename... Args>
l_BOOLEAN or_l(Args&...args) {
	return and_l(&args...);
}
template<class T, typename... REST >
l_BOOLEAN or_l(T first, const REST... rest) {
	return (bool)(first) || or_l(rest...);
}
l_BOOLEAN or_l() { return true; }


class varstack {
private:
	stack<int *> s;
	static varstack *s_instance;
	varstack() { };
public:
	static varstack *instance() {
		if (!s_instance)
			s_instance = new varstack();
		return s_instance;
	}

	void push(int *i) {
		s.push(i);
	}
	void pop() {
		if (s.empty()) return;
		s.pop();
	}
	int top() {
		if (s.empty()) return -1;
		stack<int *> temp;
		int *i = s.top();
		while (*i == -2 && !s.empty()) {
			s.pop();
			temp.push(i);
			i = s.top();
		}
		while (!temp.empty()) {
			s.push(temp.top());
			temp.pop();
		}
		return *i;
	}
	void ifcalled() {
		push(new int(-2));
	}
	bool increment() {
		if (s.empty() || *s.top() == -2) return false;
		(*s.top())++;
		return true;
	}

};

varstack *varstack::s_instance = 0;


class forward_l {
public:
	forward_l() {}
	void operator=(l_types& i) {
		turtle_mv_forward((float)dynamic_cast<l_NUMBER&>(i));
		render_GUI();
	}
};

class back_l {
public:
	back_l() {}
	void operator=(l_types& i) {
		turtle_mv_backward((float)dynamic_cast<l_NUMBER&>(i));
		render_GUI();
	}
};

class rotate_l {
public:
	rotate_l() {}
	void operator=(l_types& i) {
		turtle_rotate(dynamic_cast<l_NUMBER&>(i));
	}
};

class right_l {
public:
	right_l() {}
	void operator=(l_types& i) {
		turtle_rotate(dynamic_cast<l_NUMBER&>(i));
		render_GUI();
	}
};
class left_l {
public:
	left_l() {}
	void operator=(l_types& i) {
		turtle_rotate(360 - dynamic_cast<l_NUMBER&>(i));
		render_GUI();
	}
};

void center_l() {
	turtle_go_to_center();
	render_GUI();
}
void clear_l() {
	destroy_GUI();
	init_GUI();
	render_GUI();
}

class setxy_l {
	double a;
public:
	setxy_l() {}
	setxy_l& operator=(l_types &a_) {
		a = dynamic_cast<l_NUMBER&>(a_);
		return *this;
	}
	void operator,(l_types &b_) {
		turtle_go_to_position(a, dynamic_cast<l_NUMBER&>(b_));
		render_GUI();
	}
};

class circle_l {
public:
	circle_l() {}
	void operator=(l_types& i) {
		turtle_draw_circle((unsigned)dynamic_cast<l_NUMBER&>(i));
		render_GUI();
	}
};
class print_l {
public:
	print_l() {}
	void operator=(l_WORD l) {
		turtle_draw_label(l.getcstring());
		render_GUI();
	}
};
class setpencolor_l {
public:
	setpencolor_l() {}
	void operator=(l_types& l) {
		unsigned int x = dynamic_cast<l_NUMBER&>(l.get(0));
		unsigned int y = dynamic_cast<l_NUMBER&>(l.get(1));
		unsigned int z = dynamic_cast<l_NUMBER&>(l.get(2));
		set_pen_color(x, y, z);
	}
};
class setscreencolor_l {
public:
	setscreencolor_l() {}
	void operator=(list_l l) {
		unsigned int x = dynamic_cast<l_NUMBER&>(l.get(0));
		unsigned int y = dynamic_cast<l_NUMBER&>(l.get(1));
		unsigned int z = dynamic_cast<l_NUMBER&>(l.get(2));
		set_screen_color(x, y, z);
	}
};
class setpensize_l {
public:
	class setpensize_l() {}
	void operator=(l_types& i) {
		set_pen_thickness((float)dynamic_cast<l_NUMBER&>(i));
	}
};

class show_l {
public:
	class show_l() {}
	void operator=(l_types& i) {
		i.show_l();
	}
};

#define START_PROGRAM int main(){ init_GUI();
#define END_PROGRAM  destroy_GUI(); return 0;}

#define TRUE true
#define FALSE false
#define MAKE ;auto&

#define NUMBER (*new l_NUMBER()) = 0? 0
#define WORD (*new l_WORD()) = 0? ""
#define BOOLEAN (*new l_BOOLEAN()) = 0? true
#define LIST (*new list_l())
#define ARRAY (*new array_l()) =  array_l
#define SENTENCE(...) *new sentence_l(__VA_ARGS__)

#define AND and_l
#define OR or_l
#define ELIF ;}else if(
#define ELSE ;}else{
#define IF	;varstack::instance()->ifcalled(); \
			if(

#define ASSIGN ;
#define SUM sum_l
#define DIFFERENCE difference_l
#define SETITEM(...) setitem_l(__VA_ARGS__);
#define ITEM item_l
#define MINUS minus_l
#define QUOTIENT quotient_l
#define PRODUCT product_l
#define MODULO modulo_l


#define REPEAT	;varstack::instance()->push(new int()); for(  ;(varstack::instance()->top()) < (
#define TIMES ); varstack::instance()->increment()
#define REPCOUNT l_NUMBER(varstack::instance()->top() + 1)

#define WHILE 0);	DO  END varstack::instance()->push(new int(-1)); \
					while(  (varstack::instance()->increment()) && 

#define ELEM *ELEM
#define FOREACH ;varstack::instance()->ifcalled(); for (auto ELEM :

#define FORWARD	;forward_l() =
#define BACK	;back_l() = 
#define LEFT	;left_l() =
#define RIGHT	;right_l() =
#define CENTER	;center_l();
#define CLEAR	;clear_l();
#define SETXY	;setxy_l() =
#define CIRCLE	;circle_l() = 
#define PRINT	;print_l() =
#define SHOW	;show_l() = 0? (l_types&)l_NUMBER()

#define SETPENCOLOR    ;setpencolor_l() =   
#define SETSCREENCOLOR ;setscreencolor_l() =   
#define SETPENSIZE 	   ;setpensize_l() =
#define PENDOWN 	   ;pen_down();
#define PENUP		   ;pen_up();

#define TO void
#define ARG(...) ARG.get((__VA_ARGS__) - 1)
#define WITH ( list_l& ARG){ int
#define CALL  ;
#define FSTART ;
#define RETURN ;return ;
#define FEND ;return;}

#define DO ){ 
#define END  ;}; varstack::instance()->pop();