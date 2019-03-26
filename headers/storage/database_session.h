#pragma once

#include <string>

#include <sqlite3.h>

#include "storage/database_connection.h"
#include "storage/database_statements.h"
#include "storage/database_request.h"

namespace KelNeat{
	class DatabaseSession{
	public:
		DatabaseSession(const std::string& path);

		int32_t open(int flags);
		void close();

		int32_t getGenome(uint32_t id, GenomeDataRequest& request);

	private:

		std::string path;
		sqlite3* database;

		DatabaseConnection connection;
		DatabaseStatements statements;

	};
}