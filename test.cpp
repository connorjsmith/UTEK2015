#include <iostream>
using namespace std;

class Object
{
	private:
		int a;
	public:
		Object(const Object& copy);
};

Object::Object(const Object& copy)
{
	this->a = copy.a;
}

int main() {
	Object A;
	return 0;
}
