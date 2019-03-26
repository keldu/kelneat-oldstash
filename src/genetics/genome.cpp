#include "genetics/genome.h"

namespace KelNeat{
	Mutation::Mutation():
		weight_mutation(1.0,1.0),
		edge_creation(1.0,1.0),
		activation(1.0,1.0),
		deactivation(1.0,1.0),
		node_insertion(1.0,2.0),
		link_mutation(1.0,5.0),
		meta(1.0)
	{
		
	}

	void Mutation::metaMutate(){
		double percentage = random(0, 1, random_steps);
		if(percentage < meta){
			if(percentage < meta /2.0){
				meta *= 0.95;
			}else{
				meta /= 0.95;
			}
		}

		metaAndSingleMutate(weight_mutation);
		metaAndSingleMutate(edge_creation);
		metaAndSingleMutate(activation);
		metaAndSingleMutate(deactivation);
		metaAndSingleMutate(node_insertion);
		metaAndSingleMutate(link_mutation);
	}

	void Mutation::singleMutate(Data& relayed){
		if( double perc = random(0, 1, random_steps) < relayed.meta ){
			if(perc < relayed.meta/2.0){
				relayed.value *= 0.95;
			}else{
				relayed.value *= 1.0/0.95;
			}
		}
	}

	void Mutation::metaMetaMutate(Data& relayed){
		if( double perc = random(0, 1, random_steps)  < meta ) {
			if(perc < meta / 2.0){
				relayed.meta *= 0.95;
			}else{
				relayed.meta *= 1.0/0.95;
			}
		}
	}

	void Mutation::metaAndSingleMutate(Data& relayed){
		metaMetaMutate(relayed);
		singleMutate(relayed);
	}

	Genome::Genome(uint32_t _id):
		id(_id),
		max_innovation(0),
		max_hidden_neurons(0)
	{
		
	}

	bool Genome::isRecurrent(){
		return false;
	}

	bool Genome::linkExists(uint32_t in, uint32_t out){
		for(auto& pair : genes){
			if(pair.second->getInput() == in && pair.second->getOutput() == out){
				return true;
			}
		}
		return false;
	}

	void Genome::addGene(std::unique_ptr<Gene> gene){

		uint32_t inno = gene->getInnovation();

		if(inno > max_innovation){
			max_innovation = inno;
		}

		if(gene->isActive()){
			active_genes.push_back(gene.get());
		}else{
			inactive_genes.push_back(gene.get());
		}
		
		genes.insert(std::make_pair(inno,std::move(gene)));
	}

	uint32_t Genome::addNeuron(){
		return ++max_hidden_neurons;
	}

	uint32_t Genome::addInnovation(){
		return ++max_innovation;
	}

	void Genome::deactivate(Gene &gene){
		if(!gene.isActive()){
			return;
		}

		for(auto it = active_genes.begin(); it != active_genes.end(); ++it){
			if(gene.getInnovation() == (**it).getInnovation()){
				std::swap(*it, active_genes.back());
				Gene *gene = active_genes.back();
				active_genes.pop_back();
				gene->active = false;
				inactive_genes.push_back(gene);
				return;
			}
		}
	}

	void Genome::activate(Gene& gene){
		if(gene.isActive()){
			return;
		}

		for(auto it = inactive_genes.begin(); it != inactive_genes.end(); ++it){
			if(gene.getInnovation() == (**it).getInnovation()){
				std::swap(*it, inactive_genes.back());
				Gene *gene = inactive_genes.back();
				inactive_genes.pop_back();
				gene->active = true;
				active_genes.push_back(gene);
				return;
			}
		}	
	}

	Gene& Genome::getActiveGene(size_t id){
		return *active_genes[id];
	}

	void Genome::setFitness(int64_t fit){
		fitness = fit;
		evaluated = true;
	}
}