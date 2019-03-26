#include "storage/database_manager.h"
#include "storage/database_request.h"

#include "genetics/genome.h"
#include "genetics/species.h"

#include <iostream>
#include <sstream>

namespace KelNeat{
	DatabaseManager::DatabaseManager(const std::string& n):
		name(n),
		session(std::make_unique<DatabaseSession>(n))
	{
		
	}

	DatabaseManager::~DatabaseManager(){
		connection.close();
	}

	int32_t DatabaseManager::createDatabase(uint32_t in, uint32_t out, bool recurrent, bool meta){
		
		int32_t rc = connection.open(name,SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE);
		
		if(rc != 0){
			return rc;
		}

		connection.exec("CREATE TABLE meta_data "
			"( `id` INTEGER NOT NULL UNIQUE, `input` INTEGER NOT NULL, "
			"`output` INTEGER NOT NULL, `recurrent` BOOLEAN NOT NULL, "
			"`network` BOOLEAN NOT NULL, PRIMARY KEY(`id`) ) WITHOUT ROWID");

		std::stringstream sql_statement;
		sql_statement<<"INSERT INTO meta_data VALUES(1,"<<in<<", "<<out<<", "<<recurrent<<", "<<meta<<")";
		connection.exec(sql_statement.str());
		sql_statement.clear();

		connection.exec("CREATE TABLE species ( `id` INTEGER NOT NULL UNIQUE PRIMARY KEY )");

		connection.exec("CREATE TABLE genome ( `id` INTEGER NOT NULL UNIQUE PRIMARY KEY, "
			"`species_id` INTEGER NOT NULL )");

		connection.exec("CREATE TABLE mutation (`genome_id` INTEGER NOT NULL, `type` INTEGER NOT NULL, "
			"`value` REAL NOT NULL,`meta` REAL NOT NULL, "
			"PRIMARY KEY(genome_id, type), UNIQUE(genome_id, type) )");
		
		connection.exec("CREATE TABLE gene "
			"( `id` INTEGER NOT NULL, `genome_id` INTEGER NOT NULL, `input` INTEGER NOT NULL, "
			"`output` INTEGER NOT NULL, `weight` REAL NOT NULL, `active` BOOLEAN NOT NULL, "
			"PRIMARY KEY(id, genome_id), UNIQUE(id, genome_id) )");

		connection.exec("CREATE TABLE elo "
			"( `genome_id` INTEGER NOT NULL UNIQUE PRIMARY KEY, `score` INTEGER NOT NULL, "
			"`season` INTEGER NOT NULL, `games_played` INTEGER NOT NULL )");

		connection.exec("CREATE TABLE fitness ( `genome_id` INTEGER NOT NULL UNIQUE PRIMARY KEY, "
			"`score` INTEGER NOT NULL, `stage` INTEGER NOT NULL )");

		if(rc == 0){
			connection.close();
		}
		return rc;
	}

	int32_t DatabaseManager::loadDatabase(){
		int32_t rc = connection.open(name, SQLITE_OPEN_READONLY);
				
		if(rc == 0){
			connection.close();
		}
		
		return rc;
	}

	int32_t DatabaseManager::getGenome(uint32_t id, GenomeDataRequest &data){
		int32_t rc = session->open(SQLITE_OPEN_READONLY);
		
		
		if(rc == 0){
			session->getGenome(id, data);
			session->close();
		}
		return rc;
	}

	int32_t DatabaseManager::getMaxGenomeID(uint32_t& id){
		connection.open(name, SQLITE_OPEN_READONLY);
		connection.exec("SELECT MAX(id) AS max_id FROM genome", &id, &maxIDRequest);
		connection.close();

		return 0;
	}
	
	int32_t DatabaseManager::getMaxGeneID(uint32_t genome_id, uint32_t &id){
		connection.open(name, SQLITE_OPEN_READONLY);
		std::stringstream sql_statement;
		sql_statement<<"SELECT MAX(id) AS max_id FROM gene WHERE `genome_id` = "<<genome_id;
		connection.exec(sql_statement.str(), &id, &maxIDRequest);
		connection.close();

		return 0;
	}
	int32_t DatabaseManager::getMaxGeneNeuronID(uint32_t genome_id, uint32_t &id){
		connection.open(name, SQLITE_OPEN_READONLY);
		std::stringstream sql_statement;
		sql_statement<<"SELECT MAX(max_row_neuron) AS max_neuron FROM (SELECT (SELECT MAX(nNeu) AS max_neu FROM (SELECT g.input AS nNeu UNION SELECT g.output) a ) max_row_neuron FROM gene g WHERE genome_id= "<<genome_id<<");";
		connection.exec(sql_statement.str(), &id, &maxIDRequest);
		connection.close();

		return 0;
	}

	int32_t DatabaseManager::getMaxSpeciesID(uint32_t &id){
		connection.open(name, SQLITE_OPEN_READONLY);
		connection.exec("SELECT MAX(id) AS max_id FROM species", &id, &maxIDRequest);
		connection.close();

		return 0;
	}

	int32_t DatabaseManager::getMetaData(MetaData& data){
		connection.open(name, SQLITE_OPEN_READONLY);

		connection.exec("SELECT * FROM meta_data WHERE `id`=1", &data, &metaDataRequest);
		connection.close();

		int32_t rc = 0;
		return rc;
	}
	void DatabaseManager::writeGenome(Genome& genome){
		connection.open(name, SQLITE_OPEN_READWRITE);
		std::stringstream sql_statement;
		sql_statement<<"INSERT INTO genome VALUES("<<genome.getID()<<", "<<uint32_t(0)<<")";
		connection.exec(sql_statement.str());
		sql_statement.str("");

		const Mutation& mut = genome.getMutation();

		sql_statement<<"INSERT INTO mutation VALUES("<<genome.getID()<<", 0, "<<mut.weight_mutation.value<<", "<<mut.weight_mutation.meta<<"),("
		<<genome.getID()<<", 1, "<<mut.link_mutation.value<<", "<<mut.link_mutation.meta<<");";
		connection.exec(sql_statement.str());

		sql_statement.str("");
		genes.str("");

		auto it = genome.genes.begin();
		if(it != genome.genes.end()){
			genes<<"INSERT INTO gene VALUES ("<<it->second->getInnovation()<<", "<<genome.getID()<<", "<<it->second->getInput()<<", "<<it->second->getOutput()<<", "<<it->second->getWeight()<<", "<<it->second->isActive()<<")";
			++it;
		}
		for(; it != genome.genes.end();++it){
			Gene& gene = *(it->second);
			genes<<",("<<gene.getInnovation()<<", "<<genome.getID()<<", "<<gene.getInput()<<", "<<gene.getOutput()<<", "<<gene.getWeight()<<", "<<gene.isActive()<<")";
		}
		connection.exec(genes.str());
		connection.close();

	}

	void DatabaseManager::writeFitness(uint32_t id, int64_t fit, uint32_t stage){
		connection.open(name, SQLITE_OPEN_READWRITE);
		
		std::stringstream sql_statement;
		sql_statement<<"INSERT INTO fitness VALUES ("<<id<<", "<<fit<<", "<<stage<<");";
		connection.exec(sql_statement.str());
		connection.close();

	}

	int32_t DatabaseManager::getFitness(uint32_t id, uint32_t st, FitnessData& data){
		connection.open(name, SQLITE_OPEN_READONLY);

		std::stringstream sql_statement;
		sql_statement<<"SELECT * FROM fitness WHERE `id` = "<<id<<"AND `stage` = "<<st;
		connection.exec(sql_statement.str(), &data, &fitnessDataRequest);
		connection.close();

		return 0;
	}

	int32_t DatabaseManager::getGene(uint32_t genome_id, uint32_t id, GeneData& data){
		connection.open(name, SQLITE_OPEN_READONLY);

		std::stringstream sql_statement;
		sql_statement<<"SELECT * FROM gene WHERE `id` = "<<id<<" AND `genome_id` = "<<genome_id;
		connection.exec(sql_statement.str(), &data, &geneDataRequest);
		connection.close();

		int32_t rc = 0;
		return rc;
	}

	void DatabaseManager::writeGene(Gene &gene, uint32_t genome_id){
		connection.open(name, SQLITE_OPEN_READWRITE);
		
		genes.str("");		
		genes<<"INSERT INTO gene VALUES("<<gene.getInnovation()<<", "<<genome_id<<", "<<gene.getInput()<<", "<<gene.getOutput()<<", "<<gene.getWeight()<<", "<<gene.isActive()<<")";
		connection.exec(genes.str());
		connection.close();

	}
	
	void DatabaseManager::getUnevaluatedGenomeID(size_t amount, std::queue<uint32_t>& queue){
		connection.open(name, SQLITE_OPEN_READONLY);

		std::stringstream sql_statement;
		sql_statement<<"SELECT * FROM genome WHERE `id` NOT IN (SELECT `genome_id` FROM fitness)";
		connection.exec(sql_statement.str(), &queue, &fitnessUnevaluatedRequest);
		connection.close();

	}

	void DatabaseManager::getBestGenomes(size_t best, std::queue<uint32_t> &queue){
		connection.open(name, SQLITE_OPEN_READONLY);

		std::stringstream sql_statement;
		sql_statement<<"SELECT `genome_id` FROM fitness ORDER BY score DESC LIMIT "<<best<<";";
		connection.exec(sql_statement.str(), &queue, &fitnessBestRequest);
		connection.close();

	}
}