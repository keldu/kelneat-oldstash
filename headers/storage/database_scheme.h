#pragma once

#include <stdint.h>
#include <map>

namespace KelNeat{

	struct MetaData{
		uint32_t input;
		uint32_t output;
		bool recurrent;
		bool meta;
	};
	int metaDataRequest(void* custom, int number, char** value, char** name);

	struct MutationData{
		double weight_v, weight_m;
		double link_v, link_m;
	};
	int mutationDataRequest(void* custom, int number, char** value, char** name);
/*
	struct GenomeData{
		uint32_t id;
		uint32_t species_id;
	};
*/
	int genomeDataRequest(void* custom, int number, char** value, char** name);

	int maxIDRequest(void* custom, int number, char** value, char** name);

	struct FitnessData{
		uint32_t genome;
		int64_t fit;
		uint32_t stage;
	};
	int fitnessDataRequest(void* custom, int number, char** value, char** name);

	struct GeneData{
		uint32_t innovation;
		uint32_t input;
		uint32_t output;
		bool active;
		double weight;
	};
	int geneDataRequest(void* custom, int number, char** value, char** name);

	struct SpeciesData{
		uint32_t id;
	};
	int speciesDataRequest(void* custom, int number, char** value, char** name);

	int fitnessUnevaluatedRequest(void* custom, int number, char** value, char** name);
	int fitnessBestRequest(void* custom, int number, char** value, char** name);

	class DatabaseScheme{
	public:
		DatabaseScheme();

		int32_t validate();
		int32_t initialise();

	private:
		//std::map for table layouts
	};
}
