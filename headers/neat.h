#pragma once

#include <memory>

#include "neural/network.h"
#include "storage/database_manager.h"
#include "genetics/gene_pool.h"

namespace KelNeat{
	class Neat{
	public:
		Neat(const std::string& n);

		int32_t createPool(uint32_t in, uint32_t out, bool recurrent, bool meta);
		int32_t loadPool();

		std::unique_ptr<Network> createRecurrentNetwork(uint32_t genome);
		void destroyNetwork(Network& net);

		void createPopulation(size_t number);
		void cloneBestPopulation(size_t best, size_t clones);

		uint32_t getInputSize();
		uint32_t getOutputSize();

		bool isGenomeUnevaluatedEmpty();
		uint32_t getNextUnevaluatedGenomes();
		size_t refillUnevaluatedQueue(size_t amount);

		DatabaseManager& getDatabase() const {return *database;}
		GenePool& getPool() const {return *pool;}
	private:

		void init();
		void stop();

		std::unique_ptr<GenePool> pool;
		std::unique_ptr<DatabaseManager> database;

		std::queue<uint32_t> unevaluated_genomes;
	};
}
