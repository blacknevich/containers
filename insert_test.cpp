#include "ft_vector.hpp"
#include <vector>
#include <exception>

class B {
public:
	char *l;
	int i;
	B():l(nullptr), i(1) {};
	B(const int &ex) {
		this->i = ex;
		this->l = new char(0);
	};
	virtual ~B() {
		delete this->l;
		this->l = nullptr;
	};
};

class A : public B {
public:
	A():B(){};
	A(const B* ex){
		this->l = new char(*(ex->l));
		this->i = ex->i;
		if (ex->i == -1) throw "n";
	}
	~A() {
		delete this->l;
		this->l = nullptr;
	};
};

void show_vector_info(ft::Vector<int> vector) {
    std::cout << "size    : " << vector.size()     << std::endl;
    std::cout << "capacity: " << vector.capacity() << std::endl;
    std::cout << "arr     :" << std::endl;
    for (size_t i = 0; i < vector.size(); ++i) {
        if (i != 0 && i % 20 == 0)
            std::cout << std::endl;
        std::cout << vector[i] << " ";
    }
    std::cout << std::endl;
}

void show_etalon_vector_info(std::vector<int> vector) {
    std::cout << "size    : " << vector.size()     << std::endl;
    std::cout << "capacity: " << vector.capacity() << std::endl;
    std::cout << "arr     :" << std::endl;
    for (size_t i = 0; i < vector.size(); ++i) {
        if (i != 0 && i % 20 == 0)
            std::cout << std::endl;
        std::cout << vector[i] << " ";
    }
    std::cout << std::endl;
}

void action_announce(std::string str) {
    std::cout << ">>> action made: ";
    std::cout << str << std::endl;
}

void other() {
	ft::Vector<int>test(42);
	test.insert(test.begin(), 5);
}

void my() {
	ft::Vector<int> vector(42, 1);
	std::vector<int> v;

	int _ratio = 1;
	action_announce("vector my base state");
	vector.assign(26 * _ratio, 1);
	show_vector_info(vector);
	v.push_back(*(vector.insert(vector.end() - 8 * _ratio, 44)));
	action_announce("inserted 44 to end - 8");
	show_etalon_vector_info(v);
	std::cout << "Size " << vector.size() << std::endl;
	std::cout << "Capacity " << vector.capacity() << std::endl;
	std::unique_ptr<B> k2(new B(3));
	std::unique_ptr<B> k3(new B(4));
	std::unique_ptr<B> k4(new B(-1));
	ft::Vector<A> vv;
	ft::Vector<B*> v1;

	v1.push_back(&(*k2));
	v1.push_back(&(*k3));
	v1.push_back(&(*k4));
	action_announce("insert a child in vector of parents");
	try {vv.insert(vv.begin(), v1.begin(), v1.end()); }
	catch (...) {
	//catch (std::exception & e) {
	//std::cout << e.what() << std::endl;
	std::cout << "Size " << vv.size() << std::endl;
	std::cout << "Capacity " << vv.capacity() << std::endl;
	}
}

void etalon() {
	std::vector<int> vector(42, 1);
	std::vector<int> v;

	int _ratio = 1;
	action_announce("vector etalon base state");
	vector.assign(26 * _ratio, 1);
	show_etalon_vector_info(vector);
	v.push_back(*(vector.insert(vector.end() - 8 * _ratio, 44)));
	action_announce("inserted 44 to end - 8");
	show_etalon_vector_info(v);
	std::cout << "Size " << vector.size() << std::endl;
	std::cout << "Capacity " << vector.capacity() << std::endl;
	std::unique_ptr<B> k2(new B(3));
	std::unique_ptr<B> k3(new B(4));
	std::unique_ptr<B> k4(new B(-1));
	std::vector<A> vv;
	std::vector<B*> v1;

	v1.push_back(&(*k2));
	v1.push_back(&(*k3));
	v1.push_back(&(*k4));
	action_announce("insert a child in vector of parents");
	try {vv.insert(vv.begin(), v1.begin(), v1.end()); }
	//catch (char const* str) {
	catch (...) {
	std::cout << "Size " << vv.size() << std::endl;
	std::cout << "Capacity " << vv.capacity() << std::endl;
	}
}
int main()
{
	//my();
	//etalon();
	other();
}
