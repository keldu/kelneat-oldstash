#pragma once

#include <string>
#include <sqlite3.h>
#include <memory>

#include <stdio.h>

namespace KelNeat{
	class DatabaseConnection{
	public:
		DatabaseConnection();
		~DatabaseConnection();

		int32_t open(const std::string& path, int flags);
		int32_t open(sqlite3** _data, const std::string& path, int flags);

		void close();
		void close(sqlite3* _data);

		int32_t exec(const std::string& statement);

		int32_t exec(const std::string& statement, void*, int (*callback)(void*,int,char**,char**));

	private:
		
		sqlite3* database;
		bool isOpen;
	};
}