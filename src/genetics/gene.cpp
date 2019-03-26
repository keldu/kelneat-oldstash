#include "genetics/gene.h"

namespace KelNeat{
	Gene::Gene(uint32_t in, uint32_t out, double wei, bool act, uint32_t inno):
		input(in),
		output(out),
		weight(wei),
		active(act),
		innovation(inno)
	{
		
	}

	Gene::Gene(const Gene& a):
		input(a.input),
		output(a.output),
		weight(a.weight),
		active(a.active),
		innovation(a.innovation)
	{

	}

	uint32_t Gene::getInput() const{
		return input;
	}

	uint32_t Gene::getOutput() const{
		return output;
	}

	uint32_t Gene::getInnovation() const {
		return innovation;
	}

	double Gene::getWeight() const{
		return weight;
	}

	bool Gene::isActive() const{
		return active;
	}
}

