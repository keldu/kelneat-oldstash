#pragma once

#include <vector>
#include <queue>
#include <list>
#include <string>
#include <sstream>
#include <queue>

#include "storage/database_connection.h"
#include "storage/database_scheme.h"
#include "storage/database_session.h"

namespace KelNeat{
	class Genome;
	class Gene;
	class Species;
	class DatabaseManager{
	public:
		DatabaseManager(const std::string& n);
		~DatabaseManager();

		void openConnection();

		void getNextGenome();

		int32_t getGenome(uint32_t id, GenomeDataRequest& req);
		void writeGenome(Genome& genome);
		int32_t getMaxGenomeID(uint32_t &id);

		void writeFitness(uint32_t id, int64_t fit, uint32_t stage);
		int32_t getFitness(uint32_t id, uint32_t stage, FitnessData& data);

		int32_t getMaxGeneID(uint32_t genome_id, uint32_t &id);
		int32_t getMaxGeneNeuronID(uint32_t genome_id, uint32_t &id);
		int32_t getGene(uint32_t genome_id, uint32_t id, GeneData& req);
		void writeGene(Gene& gene, uint32_t genome_id);

		void writeSpecies(Species& species);
		int32_t getMaxSpeciesID(uint32_t &id);

		void getUnevaluatedGenomeID(size_t amount, std::queue<uint32_t>& queue);
		void getBestGenomes(size_t best, std::queue<uint32_t>& queue);

		bool isCorrupted();
		int32_t loadDatabase();
		int32_t createDatabase(uint32_t in, uint32_t out, bool recurrent, bool meta);

		int32_t getMetaData(MetaData&);

	private:

		std::string name;

		DatabaseConnection connection;

		std::unique_ptr<DatabaseSession> session;

		std::stringstream genomes, mutation, genes;
	};
}