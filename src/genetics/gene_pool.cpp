#include "genetics/gene_pool.h"

namespace KelNeat{
	GenePool::GenePool(DatabaseManager& data, uint32_t in, uint32_t out, bool rec):
		database(&data),
		inputs(in),
		outputs(out),
		recurrent(rec),
		breeder(*this)
	{

	}

	void GenePool::create(size_t size){

		for(size_t i = 0; i < size; ++i){
			uint32_t id = 0;
			database->getMaxGenomeID(id);
			std::unique_ptr<Genome> genome = breeder.createBasicMutatedGenome(id+1);
			database->writeGenome(*genome);
			checkout(id);
		}
	}

	void GenePool::clone(uint32_t parent, size_t amount){
		Genome& genome = loadGenome(parent);

		for(size_t i = 0; i < amount; ++i){
			uint32_t id = 0;

			database->getMaxGenomeID(id);
			std::unique_ptr<Genome> genome_ptr = breeder.clone(genome, id+1);
			database->writeGenome(*genome_ptr);
			checkout(id);

		}
	}


	uint32_t GenePool::findKind(Genome& genome){

		return 0;
	}

	Genome& GenePool::loadGenome(uint32_t id){
		auto finder = loaded_genomes.find(id);

		if(finder == loaded_genomes.end()){
			auto s_genome = std::make_unique<SGenome>(id);
			int rc = splicer.buildGenome(id,s_genome->genome,*this);
			if(rc == 0){
				auto fifi = loaded_genomes.insert(std::make_pair(id,std::move(s_genome)));
				finder = fifi.first;
			}else{
				;
			}
		}
		++(finder->second->counter);

		return finder->second->genome;
	}

	void GenePool::checkout(uint32_t id){
		auto finder = loaded_genomes.find(id);
		if(finder != loaded_genomes.end()){
			--(finder->second->counter);
			if(finder->second->counter == 0){
				database->writeGenome((finder->second->genome));
				loaded_genomes.erase(finder);
			}
		}
	}
}