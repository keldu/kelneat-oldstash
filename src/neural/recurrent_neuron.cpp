#include "neural/recurrent_neuron.h"

#include "helper/math.h"
#include <iostream>

namespace KelNeat{

	RecurrentNeuron::RecurrentNeuron(uint32_t id, Neuron::Type type):Neuron(id,type),
		old(0.0f)
	{

	}

	const float RecurrentNeuron::getValue() const{
		return old;
	}

	void RecurrentNeuron::setValue(float val){
		value = val;
	} 

	void RecurrentNeuron::update(){
		old = sigmoid(value);
	}

	void RecurrentNeuron::addValue(float val){
		value += val;
	}

	void RecurrentNeuron::setZero(){
		value = 0;
	}

	void RecurrentNeuron::calculateValue(){
		if(inputs.size() <= 0){
			return;
		}
		value = 0;
		for(auto& it : inputs){
			value += it.first->getValue() * it.second;
		}
	}
}