#include "neural/network.h"

#include "genetics/gene_pool.h"
#include "neat.h"

namespace KelNeat{
	Network::Network(Neat& _neat):
		current_evaluation(0),
		neat(&_neat)
	{

	}

	Network::~Network(){
		neat->destroyNetwork(*this);
	}

	void Network::create(Genome& g){
		genome = &g;
		build();
	}

	uint32_t Network::getOutputSize(){
		return neat->getOutputSize();
	}

	uint32_t Network::getInputSize(){
		return neat->getInputSize();
	}

	void Network::setFitness(int64_t fit){
		current_evaluation = fit;	
	}

	void Network::evaluate(){
		genome->setFitness(current_evaluation);
		neat->getDatabase().writeFitness(genome->getID(), current_evaluation, 1);
	}
}