#include "genetics/splicer.h"

#include "storage/database_manager.h"
#include "storage/database_request.h"
#include "genetics/gene_pool.h"

#include <stdint.h>
#include <iostream>

namespace KelNeat{
	int32_t Splicer::buildGenome(uint32_t id, Genome& genome, GenePool& pool){
		DatabaseManager& man = pool.getDatabase();

		GenomeDataRequest genome_data;
		
		std::cout<<"hello\n"<<id<<std::endl;
		int32_t rc = man.getGenome(id, genome_data);
		std::cout<<"bye\n"<<genome_data.getCounter()<<std::endl;

		uint32_t gene_max_inno = 0;
		man.getMaxGeneID(id, gene_max_inno);

		uint32_t gene_hidden_size = 0;
		man.getMaxGeneNeuronID(id, gene_hidden_size);


		uint32_t min_shift = pool.getShift();
		gene_hidden_size = min_shift > gene_hidden_size ? 0 : gene_hidden_size - min_shift;

		genome.max_hidden_neurons = gene_hidden_size;

		for(size_t i = 1; i <= gene_max_inno; ++i){
			GeneData data;
			man.getGene(id,i,data);
			if(data.innovation > 10000) {throw 10;}
			genome.addGene(std::make_unique<Gene>(data.input,data.output,data.weight,data.active,data.innovation));
		}

		FitnessData fitness;

		man.getFitness(id,1,fitness);

		return rc;
	}
}