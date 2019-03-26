#include "storage/database_scheme.h"
#include "storage/database_request.h"

#include <iostream>
#include <queue>

namespace KelNeat{
	int32_t DatabaseScheme::initialise(){
		
		return 0;
	}

	int metaDataRequest(void* custom, int number, char** value, char** name){
		MetaData* meta = (MetaData*) custom;

		meta->input = atoi(value[1]);
		meta->output = atoi(value[2]);
		meta->recurrent = atoi(value[3]);
		meta->meta = atoi(value[4]);

		return 0;
	}

	int maxIDRequest(void* custom, int number, char** value, char** name){
		uint32_t* data = (uint32_t*)custom;

		if(value[0] == 0L){
			*data = 0;
			return 2;
		}
		*data = atoi(value[0]);
		return 0;
	}

	int genomeDataRequest(void* custom, int number, char** value, char** name){
		
		return 0;
	}

	int fitnessDataRequest(void* custom, int number, char** value, char** name){
		FitnessData* data = (FitnessData*)custom;
		
		data->genome = atoi(value[0]);
		data->fit = atol(value[1]);
		data->stage = atoi(value[2]);

		return 0;
	}

	int geneDataRequest(void* custom, int number, char** value, char** name){
		GeneData* data = (GeneData*)custom;

		data->innovation = atoi(value[0]);
		data->input = atoi(value[2]);
		data->output = atoi(value[3]);
		data->weight = atof(value[4]);
		data->active = atoi(value[5]);

		return 0;
	}
	
	int speciesDataRequest(void* custom, int number, char** value, char** name){
		
		
		return 0;
	}

	int fitnessUnevaluatedRequest(void* custom, int number, char** value, char** name){
		std::queue<uint32_t>* data = (std::queue<uint32_t>*)custom;
		data->push(atoi(value[0]));

		return 0;
	}
	
	int fitnessBestRequest(void* custom, int number, char** value, char** name){
		std::queue<uint32_t>* data = (std::queue<uint32_t>*)custom;
		data->push(atoi(value[0]));
		return 0;
	}
}