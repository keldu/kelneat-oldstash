#pragma once

#include <string>

namespace KelNeat{
	class DatabaseStatementSource{
	public:
		static const std::string& insertGeneData(){return insert_gene_data;}
		static const std::string& selectGeneDataByID(){return select_gene_data_by_id;}
		static const std::string& selectGeneMaxID(){return select_gene_max_id;}

		static const std::string& insertMetaFirstData(){return insert_meta_first_data;}
		static const std::string& selectMetaFirstData(){return select_meta_first_data;}

		static const std::string& insertGenomeData(){return insert_genome_data;}
		static const std::string& selectGenomeDataByID(){return select_genome_data_by_id;}
		static const std::string& selectGenomeMaxID(){return select_genome_max_id;}
		
		static const std::string& insertFitnessData(){return insert_fitness_data;}
		static const std::string& selectFitnessDataByIDAndGeneration(){return select_fitness_data_by_id_and_generation;}
		static const std::string& selectFitnessBestPerforming(){return select_fitness_best_performing;}

		static const std::string& insertSpeciesData(){return insert_species_data;}
		static const std::string& selectSpeciesData(){return select_species_data;}

	private:
		static std::string insert_gene_data;
		static std::string select_gene_data_by_id;
		static std::string select_gene_max_id;

		static std::string insert_meta_first_data;
		static std::string select_meta_first_data;

		static std::string insert_genome_data;
		static std::string select_genome_data_by_id;
		static std::string select_genome_max_id;
		
		static std::string insert_fitness_data;
		static std::string select_fitness_data_by_id;
		static std::string select_fitness_data_by_id_and_generation;
		static std::string select_fitness_best_performing;
		
		static std::string insert_species_data;
		static std::string select_species_data;
	};
}