#pragma once

#include "neural/neuron.h"

namespace KelNeat{
	class RecurrentNeuron : public Neuron{
	public:
		RecurrentNeuron(uint32_t id, Neuron::Type type);

		const float getValue() const;
		void addValue(float val);
		void setZero();
		void setValue(float val);

		void calculateValue();

		void update();
	protected:

		float old;
	};
}