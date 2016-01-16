#pragma once
#include <string>
#include "Road.h"

struct ruleAttr {
	//Do we end at a crossing? Did this crossing exist before or did we create it
	int depth;
	float *roadPatternVals;

	//Something to control direction

	//Indicates where a block points. 
	float manhattanBlockDirection;
};

struct roadAttr {
	float length, angle;
	Point start, end;
	roadType rtype;
	//null => create an intersection at start
	RoadIntersection *branchSource;
	//null => create an intersection at end
	RoadIntersection *target;

	//The road that generated this.
	Road *parentRoad;
	//The source of the whole path
	Road *rootRoad;
	//Incident road, if exists.
	Road *targetRoad;
	
	bool connected;

	void createFromIntersection(RoadIntersection *source) {
		branchSource = source;
		start = source->location;
	}

	void branchFromParent(Road *parent) {
		this->parentRoad = parent;
	}

	//Recalculate end point from length and angle
	void recalculateEndPoint();
	
};

enum class Zone {
	RESIDENTIAL,
	COMMERTICAL,
	INDUSTRIAL
};

enum class solutionState {
	UNASSIGNED,
	SUCCEED,
	FAILED
};

enum class variableType {
	ROAD,
	INSERTION,
	BRANCH,
	EMPTY
};

//Represents the basic variable
class Variable {
public:
	int delay;
	ruleAttr rules;
	roadAttr road;
	variableType varType;
	solutionState state;

	Variable(variableType vType, int delay, ruleAttr rules, roadAttr road);
	Variable(variableType vType);
	Variable(variableType vType, int delay);
	Variable();
	~Variable();

	std::string toString();

};
