#include "neural/recurrent_network.h"

#include "neat.h"


#include <iostream>

namespace KelNeat{
	RecurrentNetwork::RecurrentNetwork(Neat& _neat):
		Network(_neat)
		{

		}

	void RecurrentNetwork::step(){
		for(auto& it : neurons){
			it.second->calculateValue();
		}
		for(auto& it : neurons){
			it.second->update();
		}
	}

	void RecurrentNetwork::build(){
		size_t i;
		size_t static_size = neat->getPool().getInputs() + 1;
		neurons.insert(std::make_pair(0,std::make_unique<RecurrentNeuron>(0,Neuron::BIAS)));
		for(i = 1; i < static_size; ++i){
			neurons.insert(std::make_pair(i,std::make_unique<RecurrentNeuron>(i,Neuron::INPUT)));	
		}
		static_size += neat->getPool().getOutputs();
		for(i = neat->getPool().getInputs() + 1; i < static_size; ++i){
			neurons.insert(std::make_pair(i,std::make_unique<RecurrentNeuron>(i,Neuron::OUTPUT)));	
		}

		size_t size = genome->getActiveGeneSize();
		for(size_t i = 0; i < size; ++i){
			Gene& gene = genome->getActiveGene(i);
			auto input_finder = neurons.find(gene.getInput());
			auto output_finder = neurons.find(gene.getOutput());

			if(input_finder != neurons.end()){
				
			}else{
				auto finder = neurons.insert(std::make_pair(gene.getInput(), std::make_unique<RecurrentNeuron>(gene.getInput(),Neuron::HIDDEN)));
				input_finder = finder.first;
			}
			if(output_finder != neurons.end()){
				;
			}else{
				auto finder = neurons.insert(std::make_pair(gene.getOutput(), std::make_unique<RecurrentNeuron>(gene.getOutput(), Neuron::HIDDEN)));
				output_finder = finder.first;
			}
			output_finder->second->addInputNeuron(*(input_finder->second), gene.getWeight());
			
		}
	}

	void RecurrentNetwork::setInput(float value, uint32_t pos){
		neurons.at(1 + pos)->setValue(value);
	}

	float RecurrentNetwork::getOutput(uint32_t pos){
		return neurons.at(neat->getPool().getInputs() + 1 + pos)->getValue();
	}
}
