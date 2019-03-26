#pragma once

#include <memory>
#include <unordered_map>
#include <set>

#include "storage/database_manager.h"
#include "genetics/species.h"
#include "genetics/genome.h"
#include "genetics/breeder.h"
#include "genetics/splicer.h"

namespace KelNeat{
	class GenePool{
	public:

		GenePool(DatabaseManager& data, uint32_t in, uint32_t out, bool rec);

		uint32_t getInputs() const {return inputs;}
		uint32_t getOutputs() const {return outputs;}
		uint32_t getShift() const {return inputs + outputs;}
		bool isRecurrent() const {return recurrent;}

		Genome& loadGenome(uint32_t genome_id);
		DatabaseManager& getDatabase() const {return *database;}

		void create(size_t size);
		void clone(uint32_t parent, size_t amount);

		void checkout(uint32_t id);

		
	private:

		uint32_t findKind(Genome& genome);

		DatabaseManager* database;

		std::unique_ptr<Species> species;

		class SGenome{
		public:
			SGenome(uint32_t id):genome(id),counter(0){}
			Genome genome;
			uint32_t counter;
		};

		std::unordered_map<uint32_t,std::unique_ptr<SGenome>> loaded_genomes;
		
		uint32_t inputs;
		uint32_t outputs;
		bool recurrent;

		Breeder breeder;
		Splicer splicer;
	};
}