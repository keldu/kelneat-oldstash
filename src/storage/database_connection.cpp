#include "storage/database_connection.h"

namespace KelNeat{
	DatabaseConnection::DatabaseConnection():
		database(0L),
		isOpen(false)
	{

	}

	DatabaseConnection::~DatabaseConnection(){
		if(isOpen){
			close();
		}
	}

	int32_t DatabaseConnection::open(const std::string& fileName, int flags){
		if(isOpen){
			return 1;
		}
		if(sqlite3_open_v2(fileName.c_str(),&database,flags,0L) != SQLITE_OK){
			isOpen = false;
			return -1;
		}else{
			isOpen = true;
			return 0;
		}
	}

	int32_t DatabaseConnection::open(sqlite3** _data, const std::string &fileName, int flags){
		int32_t rc = 0;
		if(sqlite3_open_v2(fileName.c_str(),_data,flags,0L) != SQLITE_OK){
			isOpen = false;
		}else{
			isOpen = true;
		}
		return rc;
	}

	void DatabaseConnection::close(){
		if(!isOpen){
			return;
		}

		sqlite3_close(database);
		isOpen = false;
	}

	void DatabaseConnection::close(sqlite3* _data){
		if(!isOpen){
			return;
		}

		sqlite3_close(_data);
		isOpen = false;
	}

	int32_t DatabaseConnection::exec(const std::string &statement){
		int rc = sqlite3_exec(database, statement.c_str(), 0L, 0L, 0L);
		return rc;
	}

	int32_t DatabaseConnection::exec(const std::string &statement, void* data, int (*callback)(void*,int,char**,char**)){
		int rc = sqlite3_exec(database, statement.c_str(), callback, data, 0L);
		return rc;
	}
}