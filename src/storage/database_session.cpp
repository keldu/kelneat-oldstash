#include "storage/database_session.h"

#include <iostream>

namespace KelNeat{
	DatabaseSession::DatabaseSession(const std::string& _path):
		path(_path),
		database(0L)
	{

	}

	int32_t DatabaseSession::open(int flags){
		int32_t rc = connection.open(&database, path, flags);
		std::cout<<"Open try: "<<rc<<std::endl;
		if(rc == 0){
			statements.compile(database);
		}

		return rc;
	}

	void DatabaseSession::close(){
		statements.finalize(database);
		connection.close(database);
	}

	int32_t DatabaseSession::getGenome(uint32_t id, GenomeDataRequest& request){
		statements.selectGenomeDataByID(id, request);


		return 0;
	}
}