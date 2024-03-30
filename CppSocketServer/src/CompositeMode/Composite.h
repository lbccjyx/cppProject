#ifndef _COMPOSITE_H_
#define _COMPOSITE_H_
#include <set>

class ComponentB
{
public:
	ComponentB() {};
	virtual ~ComponentB() {};
	virtual void Operation() = 0;
	virtual void Add(ComponentB*) = 0;
	virtual void Remove(ComponentB*) = 0;
	virtual ComponentB* GetChild(int) = 0;
};

class Composite :public ComponentB
{
public:
	Composite() {}
	~Composite() {}

	void Operation() {
		if (_setComp.size() <= 0)
			return;

		for (auto pC : _setComp)
		{
			pC->Operation();
		}
	}
	void Add(ComponentB* pC) {
		_setComp.insert(pC);
		return;
	}
	void Remove(ComponentB* pC) {
		_setComp.erase(pC);
		return;
	}
	ComponentB* GetChild(int nIndex) {
		return *_setComp.begin();
	}
private:
	std::set<ComponentB*> _setComp;
};

class leaf:public ComponentB
{
public:
	leaf() {}
	~leaf() {}
	void Operation() {
		std::cout << "leaf::Operation\n";
	}
private:
	void Add(ComponentB*) {}
	void Remove(ComponentB*) {}
	ComponentB* GetChild(int n) { return nullptr; }
};
#endif