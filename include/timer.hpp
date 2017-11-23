#ifndef TIMERHPP
#define TIMERHPP

#include <common.hpp>

class Timer{
	float time = 0;
public:
	Timer();

	void add_time(float additional_time = 0);
	void restart_time();
	float get_time();
};

#endif//TIMERHPP
