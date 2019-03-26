#pragma once

#include <memory>
#include <unordered_map>

#include "neural/neuron.h"
#include "genetics/genome.h"

namespace KelNeat{
	class Neat;
	class Network{
	public:
		Network(Neat& _pool);
		virtual ~Network();

		void create(Genome&);
		virtual void step() = 0;

		uint32_t getInputSize();
		uint32_t getOutputSize();

		virtual void setInput(float value, uint32_t pos) = 0;
		virtual float getOutput(uint32_t pos) = 0;

		Genome& getGenome(){return *genome;}

		void setFitness(int64_t fit);
		void evaluate();

	protected:

		virtual void build() = 0;

		int64_t current_evaluation;
		Genome *genome;
		Neat *neat;
	};
}