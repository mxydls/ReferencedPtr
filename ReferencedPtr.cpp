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
		cout<<"ReferencedPtr()"<<endl;
		instance_ = NULL;
		count_ = NULL;
	}
	ReferencedPtr(T * instance) {
		cout<<"ReferencedPtr(T*)"<<endl;
		instance_ = instance;
		count_ = new uint32;
		(*count_) = 1;
	}
	ReferencedPtr(ReferencedPtr& r): ReferencedPtr() {
		if(r.instance_) {
			(*r.count_)++;
			count_ = r.count_;
		}
	}
	~ReferencedPtr() {
		cout<<"~ReferencedPtr()"<<endl;
		release();
	}
	
	T* get() {
		return instance_;
	}
	
	uint32 use_count() {
		if(!count_) return 0;
		return *count_;
	}
	
	ReferencedPtr& operator = (ReferencedPtr & r) {
		release();
		if(r.instance_) {
			(*r.count_)++;
			count_ = r.count_;
			instance_ = r.instance_;
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
		(*count_)--;
		if(*count_ == 0) {
			delete instance_;
			delete count_;
		}
		instance_ = NULL;
		count_ = NULL;
	}
	
private:
	T * instance_ = NULL;
	uint32 * count_ = NULL;
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
