#include "storage/database_statements.h"

#include "storage/database_statement_source.h"

#include <iostream>

namespace KelNeat{
	DatabaseStatements::DatabaseStatements(){
	
	}

	void DatabaseStatements::compile(sqlite3* database){
		compile_single(database, DatabaseStatementSource::selectGeneDataByID(), &select_gene_data_by_id);
		compile_single(database, DatabaseStatementSource::selectGeneMaxID(), &select_gene_max_id);

		compile_single(database, DatabaseStatementSource::insertMetaFirstData(), &insert_meta_first_data);
		compile_single(database, DatabaseStatementSource::selectMetaFirstData(), &select_meta_first_data);
		
		compile_single(database, DatabaseStatementSource::selectGenomeDataByID(), &select_genome_data_by_id);
		compile_single(database, DatabaseStatementSource::selectGenomeMaxID(), &select_genome_max_id);
		
		compile_single(database, DatabaseStatementSource::selectFitnessDataByIDAndGeneration(), &select_fitness_data_by_id_and_generation);
	}

	void DatabaseStatements::finalize(sqlite3* database){

	}

	void DatabaseStatements::compile_single(sqlite3* database, const std::string& source, sqlite3_stmt** statement){
		int rc = sqlite3_prepare_v2(database, source.c_str(), -1, statement, 0L);
		std::cout<<"Prepare result: "<<rc<<" "<<sqlite3_errstr(rc)<<" "<<source<<std::endl;
	}

	void DatabaseStatements::finalize_single(sqlite3_stmt* statement){
		sqlite3_finalize(statement);
	}

	void DatabaseStatements::selectGenomeDataByID(uint32_t id, GenomeDataRequest& request){
		int rc = 0;
		std::cout<<"Reset status: "<<rc<<std::endl;
		rc = sqlite3_bind_int(select_genome_data_by_id, 0, id);
		std::cout<<"Bind status: "<<rc<<std::endl;
return;

		while(true){
			rc = sqlite3_step(select_genome_data_by_id);

			if(rc == SQLITE_ROW){
				GenomeDataRequest::Element element;
				element.id = (uint32_t)sqlite3_column_int(select_genome_data_by_id, 0);

				request.addElement();
				request.data.push_back(element);

				std::cout<<"Result: "<<element.id<<std::endl;
			
			}else if(rc == SQLITE_DONE){
				std::cout<<"Finished: "<<id<<std::endl;
				break;
			}else{
				std::cout<<"Error: "<<rc<<std::endl;
			}
		}
		rc = sqlite3_clear_bindings(select_genome_data_by_id);
	}
}