#include "neat.h"

#include "neural/recurrent_network.h"

namespace KelNeat{

	Neat::Neat(const std::string& n):
		database(std::make_unique<DatabaseManager>(n))
	{
		seed();
	}

	int32_t Neat::createPool(uint32_t in, uint32_t out, bool recurrent, bool meta){
		int32_t rc = database->createDatabase(in, out, recurrent, meta);
		if(rc == 0){
			init();
		}
		return rc;
	}

	int32_t Neat::loadPool(){
		int32_t rc = database->loadDatabase();
		if(rc == 0){
			init();
		}
		return rc;
	}

	uint32_t Neat::getInputSize(){
		return pool->getInputs();
	}

	uint32_t Neat::getOutputSize(){
		return pool->getOutputs();
	}

	void Neat::init(){
		MetaData data;
		database->getMetaData(data);
		pool = std::make_unique<GenePool>(*database, data.input, data.output, data.recurrent);
	}

	void Neat::stop(){
		
	}

	std::unique_ptr<Network> Neat::createRecurrentNetwork(uint32_t genome_id){
		
		std::unique_ptr<Network> network = std::make_unique<RecurrentNetwork>(*this);
		Genome& genome = pool->loadGenome(genome_id);
		network->create(genome);

		return network;
	}

	void Neat::destroyNetwork(Network& net){
		Genome& genome = net.getGenome();

		pool->checkout(genome.getID());
	}

	void Neat::createPopulation(size_t number){
		pool->create(number);
	}

	bool Neat::isGenomeUnevaluatedEmpty(){
		return unevaluated_genomes.empty();
	}

	uint32_t Neat::getNextUnevaluatedGenomes(){
		if(unevaluated_genomes.empty()){
			return 0;
		}
		uint32_t fro = unevaluated_genomes.front();
		unevaluated_genomes.pop();
		return fro;
	}

	size_t Neat::refillUnevaluatedQueue(size_t amount){
		database->getUnevaluatedGenomeID(amount, unevaluated_genomes);

		return unevaluated_genomes.size();
	}

	void Neat::cloneBestPopulation(size_t best, size_t clones){
		std::queue<uint32_t> best_genomes;

		database->getBestGenomes(best, best_genomes);

		while(!best_genomes.empty()){
			pool->clone(best_genomes.front(),clones);
			best_genomes.pop();
		}
	}
}