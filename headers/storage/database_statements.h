#pragma once

#include <string>
#include <sqlite3.h>

#include "storage/database_request.h"

namespace KelNeat{
	class DatabaseStatements{
	public:
		DatabaseStatements();

		void compile(sqlite3* database);
		void finalize(sqlite3* database);

		void selectGenomeDataByID(uint32_t id, GenomeDataRequest& request);

	private:

		void compile_single(sqlite3* database, const std::string& source, sqlite3_stmt** statement);
		void finalize_single(sqlite3_stmt* statement);

		sqlite3_stmt* select_gene_data_by_id;
		sqlite3_stmt* select_gene_max_id;
		
		sqlite3_stmt* insert_meta_first_data;
		sqlite3_stmt* select_meta_first_data;

		sqlite3_stmt* select_genome_data_by_id;
		sqlite3_stmt* select_genome_max_id;

		sqlite3_stmt* select_fitness_data_by_id_and_generation;
		sqlite3_stmt* select_fitness_best_performing;

		sqlite3_stmt* select_species_data_by_id;

	};
}