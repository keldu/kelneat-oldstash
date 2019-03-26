#include "storage/database_statement_source.h"

namespace KelNeat{
	std::string DatabaseStatementSource::insert_gene_data = "INSERT INTO gene VALUES(?, ?, ?, ?, ?);";
	std::string DatabaseStatementSource::select_gene_data_by_id = "SELECT * FROM gene WHERE id = ? AND genome_id = ?;";
	std::string DatabaseStatementSource::select_gene_max_id = "SELECT MAX(id) AS max_id FROM gene;";

	std::string DatabaseStatementSource::insert_meta_first_data = "INSERT INTO meta_data VALUES(1, ?, ?, ?, ?);";
	std::string DatabaseStatementSource::select_meta_first_data = "SELECT * FROM meta_data WHERE id=1;";

	std::string DatabaseStatementSource::insert_genome_data = "INSERT INTO genome VALUES(?, 0);";
	std::string DatabaseStatementSource::select_genome_data_by_id = "SELECT * FROM genome WHERE id = ?;";
	std::string DatabaseStatementSource::select_genome_max_id = "SELECT MAX(id) AS max_id FROM genome_id;";

	std::string DatabaseStatementSource::insert_fitness_data = "INSERT INTO fitness VALUES(?, ?, ?);";
	std::string DatabaseStatementSource::select_fitness_data_by_id = "SELECT * FROM fitness WHERE id = ?;";
	std::string DatabaseStatementSource::select_fitness_data_by_id_and_generation = "SELECT * FROM fitness WHERE id = ? AND generation = ?;";
	std::string DatabaseStatementSource::select_fitness_best_performing = "SELECT * FROM fitness ORDER BY score DESC LIMIT ?;";

	std::string DatabaseStatementSource::insert_species_data = "INSERT INTO species VALUES(?);";
	std::string DatabaseStatementSource::select_species_data = "SELECT * FROM species WHERE id = ?;";	
}