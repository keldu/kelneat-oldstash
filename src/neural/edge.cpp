#include "neural/edge.h"

namespace KelNeat{
	Edge::Edge():
		input(0),
		output(0),
		weight(0.0f)
		{

		}	
	void Edge::setData(uint32_t in, uint32_t out, float weight){
		input = in;
		output = out;
	}

	uint32_t Edge::getInput() const{
		return input;
	}

	uint32_t Edge::getOutput() const{
		return output;
	}

	float Edge::getWeight() const{
		return weight;
	}

}