/*
 * author: Maxiaoyuan
 * date: 2017/8/11
 * Implement shared_ptr on my own. All the functions are following the STL library.
 */

#include<memory>
#include<iostream>

using namespace std;

typedef unsigned int uint32;

string get() {
	cout<<"get called"<<endl;
	return "abc";
}

class A {
public:
	A() {
		cout<<"A"<<endl;
	}
	void f() {
		cout<<"f()"<<endl;
	}
	~A() {
		cout<<"~A"<<endl;
	}
	
	string tmp = get();
};

//Main class
template<class T> class ReferencedPtr {
public:
	ReferencedPtr() {
		instance_ = NULL;
		(*count) = 0;
	}
	ReferencedPtr(T * instance) {
		instance_ = instance;
		(*count) = 1;
	}
	ReferencedPtr(ReferencedPtr& r): ReferencedPtr() {
		if(r.instance_) {
			(*r.count)++;
			count = r.count;
		}
	}
	~ReferencedPtr() {
		if(*count == 0) {
			delete count;
			count = NULL;
		}
		else {
			(*count)--;
		}
	}
	
	T* get() {
		return instance_;
	}
	
	uint32 use_count() {
		return *count;
	}
	
	ReferencedPtr& operator = (ReferencedPtr & r) {
		if(r.instance_) {
			(*r.count)++;
			count = r.count;
		}
		return *this;
	}
	
	T * operator -> () {
		return instance_;
	}
	T & operator * () {
		return *instance_;
	}
	
	//we don't have nullptr, so we must use a release function explicitly
	void release() {
		if(!instance_) return;
		(*count)--;
		if(*count == 0) {
			delete instance_;
			instance_ = NULL;
		}
		else {
			count = new uint32(0);
		}
	}
	
private:
	T * instance_ = NULL;
	uint32 * count = new uint32;
};


typedef ReferencedPtr<A> ptr_A;

int main()
{
	A * pa = new A();
	ptr_A p1(pa);
	ptr_A p2 = p1;
	ptr_A p3 = p1;
	
	cout<<p1.use_count()<<endl;
	cout<<p2.use_count()<<endl;
	cout<<p3.use_count()<<endl;
	
	p1.release();
	
	cout<<p1.use_count()<<endl;
	cout<<p2.use_count()<<endl;
	cout<<p3.use_count()<<endl;
}




