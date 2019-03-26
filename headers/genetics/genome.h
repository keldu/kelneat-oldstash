#pragma once

#include <unordered_map>
#include <vector>
#include <memory>

#include "gene.h"
#include "helper/math.h"

namespace KelNeat{
	class Mutation{
		public:
			struct Data{//MutationData
				Data(double m, double v):meta(m),value(v){}
				double meta;
				double value;
			};
			Mutation();

			void metaMutate();
			
			Data weight_mutation;
			Data edge_creation;
			Data activation, deactivation;
			Data node_insertion;
			Data link_mutation;

			//mutation chance value of mutation chances of the mutation chances.
			double meta;
		private:
			//mutates mutation chance.
			void singleMutate(Data &relayed);
			//mutates mutation chance of mutation chances.
			void metaMetaMutate(Data &relayed);
			//convenience method two call both of the above methods
			void metaAndSingleMutate(Data &relayed);
	};

	class Genome{
	public:

	public:
		Genome(uint32_t _id);

		bool isRecurrent();
		bool linkExists(uint32_t in, uint32_t out);

		void addGene(std::unique_ptr<Gene> gene);
		uint32_t addNeuron();
		uint32_t addInnovation();

		void deactivate(Gene& gene);
		void activate(Gene& gene);

		const Mutation& getMutation()const{return mutation;}
		const uint32_t getID() const {return id;}
		const uint32_t getSpeciesID() const {return species_id;}

		size_t getActiveGeneSize() {return active_genes.size();}
		size_t getInactiveGeneSize() {return inactive_genes.size();}

		Gene& getActiveGene(size_t id);

		void setFitness(int64_t fitness);

	private:
		friend class Breeder;
		friend class Splicer;
		friend class DatabaseManager;

		std::unordered_map<uint32_t, std::unique_ptr<Gene> > genes;

		std::vector<Gene*> active_genes, inactive_genes;

		int64_t fitness;
		bool evaluated;

		uint32_t species_id;
		uint32_t id;

		uint32_t max_innovation;
		uint32_t max_hidden_neurons;

		Mutation mutation;
	};
}