#pragma once

#include <stdint.h>
#include <vector>

#include "storage/database_scheme.h"

namespace KelNeat{
	class DatabaseRequest{
	public:
		DatabaseRequest();

		uint32_t getCounter()const{return counter;}
		void addElement(){++counter;}
	private:
		uint32_t counter;
	};

	class GenomeDataRequest : public DatabaseRequest{
	public:
		struct Element{
			uint32_t id;
		};

		GenomeDataRequest();
		GenomeDataRequest(size_t s):data(s){}

		std::vector<Element> data;
	};

	class GeneDataRequest : public DatabaseRequest{
	public:
		GeneDataRequest(size_t s):data(s){}

		std::vector<GeneData> data;
	};

	class FitnessDataRequest : public DatabaseRequest{
	public:
		FitnessDataRequest(size_t s):data(s){}

		std::vector<FitnessData> data;
	};
	
	class MetaDataRequest : public DatabaseRequest{
	public:
		MetaData data;
	};
}