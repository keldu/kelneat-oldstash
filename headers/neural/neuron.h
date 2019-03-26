#pragma once

#include <vector>
#include <utility>
#include <stdint.h>

namespace KelNeat{
	class Neuron{
	public:
		enum Type{
			HIDDEN,
			INPUT,
			OUTPUT,
			BIAS
		};
		
		Neuron(uint32_t id, Type);
		virtual ~Neuron() = default;

		const uint32_t getID() const;
		const Type getType() const;
		const virtual float getValue() const = 0;
		virtual void addValue(float val) = 0;
		virtual void setZero() = 0;
		virtual void setValue(float val) = 0;


		virtual void calculateValue() = 0;
		void addInputNeuron(Neuron& neuron, float wei){inputs.push_back(std::make_pair(&neuron,wei));}

	protected:
		uint32_t id;
		Type type;

		float value;

		std::vector<std::pair<Neuron*,float> > inputs;
	};
}