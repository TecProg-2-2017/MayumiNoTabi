#ifndef COMPMEMORYHPP
#define COMPMEMORYHPP

#include <common.hpp>
#include <component.hpp>
#include <timer.hpp>

#define COMPMEMORY(x)  ((CompMemory*)x. components[Component::type::t_memory])
#define COMPMEMORYp(x) ((CompMemory*)x->components[Component::type::t_memory])

class CompMemory : public Component{
	//private members
public:
	//public members
	map<string,string> strings;
	map<string,int> ints;
	map<string,float> floats;
	map<string,Timer> timers;

	CompMemory();
	~CompMemory();
	void update(float time);
	void render();
	Component::type get_type()const;
};

#endif//COMPMEMORYHPP
