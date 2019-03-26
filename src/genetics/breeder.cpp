#include "genetics/breeder.h"

#include "helper/math.h"
#include "genetics/gene_pool.h"

#include <iostream>

namespace KelNeat{
	Breeder::Breeder(GenePool& p):pool(&p){

	}

	std::unique_ptr<Genome> Breeder::clone(Genome &parent, uint32_t id){
		
		std::unique_ptr<Genome> genome = std::make_unique<Genome>(id);
		genome->max_hidden_neurons = parent.max_hidden_neurons;
		
		for(auto& iter : parent.genes){
			genome->addGene(std::make_unique<Gene>(*(iter.second)));
		}

		mutate(*genome);
		return genome;
	}

	std::unique_ptr<Genome> Breeder::createBasicMutatedGenome(uint32_t id){
		std::unique_ptr<Genome> genome = std::make_unique<Genome>(id);
		mutate(*genome,true);
		return genome;
	}

	void Breeder::mutate(Genome &genome, bool forced){
		genome.mutation.metaMutate();

		if(mutateLink(genome)){
		
		}
		mutateNode(genome);
		mutateWeight(genome,forced);
	}

	bool Breeder::mutateNode(Genome& genome){
		bool mutated = false;
		if(genome.active_genes.size() <= 0){
			return mutated;
		}

		double check_perc = genome.mutation.node_insertion.value;
		double percentage = random(0,1,random_steps);

		while(percentage < check_perc){
			size_t active_gene_size = genome.active_genes.size();
			size_t rand = random(active_gene_size);
			Gene *gene = genome.active_genes[rand];

			uint32_t node_id = genome.addNeuron() + pool->getOutputs() + pool->getInputs();

			genome.deactivate(*gene);

			genome.addGene(std::make_unique<Gene>(gene->getInput(),node_id, gene->getWeight(), true, genome.addInnovation()));
			genome.addGene(std::make_unique<Gene>(node_id,gene->getOutput(), 1.0, true, genome.addInnovation()));

			check_perc -= 1.0;
			mutated = true;
		}

		return mutated;
	}

	bool Breeder::mutateWeight(Genome& genome, bool forced){
		bool mutated = false;
		if(genome.active_genes.size() <= 0){
			return mutated;
		}
		double check_perc = genome.mutation.weight_mutation.value;
		double percentage = random(0,1,random_steps);

		while(percentage < check_perc || (!mutated && forced)){

			size_t active_gene_size = genome.active_genes.size();
			size_t rand = random(active_gene_size);
			Gene* gene = genome.active_genes[rand];
			double clamped_check_perc = check_perc < 1.0 ? check_perc * 0.5 : 0.5;
			double weight = random(0.0,0.5,random_steps);
			if(percentage < clamped_check_perc){
				gene->weight += weight;
			}else{
				gene->weight -= weight;
			}
			check_perc -= 1.0;
			percentage = random(0,1,random_steps);
			mutated = true;
		}

		return mutated;
	}

	bool Breeder::mutateLink(Genome& genome){
		bool mutated = false;
		double checkPerc = genome.mutation.link_mutation.value;
		
		double percentage = random(0,1,random_steps);

		while(percentage < checkPerc){
			uint32_t in, out;
			double weight = random(-0.5,0.5,random_steps);
			uint32_t tries = 0;
			bool isValid = false;
			do{
				in = getRandomNeuron(genome, true, false);
				out = getRandomNeuron(genome, false, true);
				++tries;

				if(!genome.linkExists(in,out) /*&& ( in != out )*/){
					isValid = true;
				}
			}while(!isValid && tries < 10);

			if(isValid){
				std::unique_ptr<Gene> gene = std::make_unique<Gene>(in,out,weight,true,genome.addInnovation());
				genome.addGene(std::move(gene));
				mutated = true;
			}

			checkPerc -= 1.0;
			percentage = random(0,1,random_steps);
		}

		return mutated;
	}

	uint32_t Breeder::getRandomNeuron(Genome& genome, bool input, bool output){
		uint32_t count = genome.max_hidden_neurons;
		if(input){
			count += (pool->getInputs() + 1);
		}
		if(output){
			count += pool->getOutputs();
		}
		
		uint32_t rolled = random(count);

		if(input){
			if(output){
				return rolled;
			}else{
				if(rolled > pool->getInputs()){
					return rolled + pool->getOutputs();
				}else{
					return rolled;
				}
			}
		}else{
			if(output){
				return rolled + pool->getInputs() + 1;
			}else{
				return rolled + pool->getInputs() + 1 + pool->getOutputs();
			}
		}
	}
}