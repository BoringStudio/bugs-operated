#pragma once

#include "Math.h"

class MapObject
{
	struct Segment
	{
		Segment(const vec2& start, const vec2& end) :
			start(start), end(end)
		{}

		vec2 start;
		vec2 end;
	};
public:
	MapObject();

private:
	
};