#include <iostream>
#include <string>
#include <set>

struct People
{
	std::string name;
	int age;

	People(std::string name, int age) : name{ name }, age{ age } {}
};

struct PeopleCompare
{
	bool operator()(const People& p1, const People& p2) const
	{
		return p1.name < p2.name;
	}
};
int main()
{
	std::set<People, PeopleCompare> s;

	s.emplace("kim", 20);
	s.emplace("lee", 25);
	s.emplace("park", 40);
	s.emplace("choi", 30);

//	auto p = s.find( { "kim", 20 } ); // People("kim", 20)

	auto p = s.find( "kim" );

	std::cout << p->name << std::endl; // kim
	std::cout << p->age  << std::endl; // 20
}
