#pragma once

#include <memory>

#include "genetics/genome.h"

namespace KelNeat{
	class GenePool;
	class Breeder{
	public:
		Breeder(GenePool&);

		std::unique_ptr<Genome> createBasicMutatedGenome(uint32_t id);
		std::unique_ptr<Genome> cross(Genome& parent_a, Genome& parent_b, uint32_t id);
		std::unique_ptr<Genome> clone(Genome& parent, uint32_t id);
		
		void mutate(Genome& genome,bool forced= false);
	private:

		bool mutateActivation(Genome& genome);
		bool mutateDeactivation(Genome& genome);
		bool mutateWeight(Genome& genome, bool force = false);
		bool mutateLink(Genome& genome);//creates new Link
		bool mutateNode(Genome& genome);//creates new Node in Link

		uint32_t getRandomNeuron(Genome& genome, bool input, bool output);

		GenePool *pool;
	};
}