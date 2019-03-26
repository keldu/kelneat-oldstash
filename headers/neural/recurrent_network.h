#pragma once

#include "neural/network.h"
#include "neural/recurrent_neuron.h"

#include <unordered_map>

namespace KelNeat{
	class Neat;
	class RecurrentNetwork : public Network{
	public:
		RecurrentNetwork(Neat&);

		void step();

		void setInput(float value, uint32_t pos);
		float getOutput(uint32_t pos);

	protected:

		void build();

	private:

		std::unordered_map<uint32_t, std::unique_ptr<RecurrentNeuron>> neurons;
	};
}