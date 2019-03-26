#include "neural/neuron.h"

namespace KelNeat{
	Neuron::Neuron(uint32_t _id, Type _type):
		id(_id),
		type(_type),
		value(0.0f)
		{

		}

	const uint32_t Neuron::getID() const {
		return id;
	}

	const Neuron::Type Neuron::getType() const {
		return type;
	}
}