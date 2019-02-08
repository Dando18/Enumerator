#include <iostream>
#include <vector>
#include <libconfig.h++>
#include "BobyqaOptimizer.h"
#include "testing_mnist.h"
using namespace std;

typedef struct p {
	string name; 
	double type;
	double start;
	double end;
	double step_size;
} params_t;

// read_cfg takes the name of the cfg file that you want to read, and returns
// a vector of the parameters stored in the file
vector <params_t *> 
read_cfg(const char *filename) 
{
	int i;
	std::string name;
	vector <params_t*> saved_params;
	params_t *cur_params;
	libconfig::Config cfg; 

	// Read the configuration file
	try{
		cfg.readFile(filename);
	} 
	catch(const libconfig::FileIOException &fioex) {
		std::cerr << "I/O error while reading file." << std::endl;
		exit(EXIT_FAILURE);
	}
	catch(const libconfig::ParseException &pex) {
		std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine()
			<< " - " << pex.getError() << std::endl;
		exit(EXIT_FAILURE);
	}

	// Get the parameters list from the file that was read in
	const libconfig::Setting& root = cfg.getRoot();
	const libconfig::Setting &params = root["parameters"];

	// Save parameters
	for (i = 0; i < params.getLength(); i++) {
		const libconfig::Setting &param = params[i];
		cur_params = new params_t;
		param.lookupValue("name", cur_params->name);
		param.lookupValue("type", cur_params->type);
		param.lookupValue("start", cur_params->start);
		param.lookupValue("end", cur_params->end);
		param.lookupValue("step_size", cur_params->step_size);
		saved_params.push_back(cur_params);
	}
	return saved_params;
}

void objFunction(int nInputs, double *inputs, int nOuts, double *outputs) {
	outputs[0] = mnist_test(inputs[0]);	
	printf("Input = %f\n", inputs[0]);
	printf("Output = %f\n", outputs[0]);
}


double 
min (void (*func)(int,double*,int,double*), vector <params_t *> space, const char *optimizer)
{ 
	int ii, nInps=1, nOuts=1, maxEvals=10;
	double *X; 
	double *inputs, *lbnds, *ubnds, tol=1e-6;
	BobyqaOptimizer *opt;

	if (strcmp(optimizer, "bobyqa") == 0) {
		opt = new BobyqaOptimizer();
	}

	X = (double *) malloc(sizeof(double) * nInps);

	// Set objective function for the optimizer
	opt->setObjectiveFunction(func);

	inputs = new double[nInps];
	lbnds  = new double[nInps];
	ubnds  = new double[nInps];

	// put initial guess into inputs
	inputs[0] = 0;
	// put lower and upper bounds into lbnds and ubnds 
	lbnds[0] = 0.0; 
	ubnds[0] = 1.0;

	// run the optimization routine
	opt->optimize(nInps, inputs, lbnds, ubnds, maxEvals, tol);

	// print out the final input 
	for (ii = 0; ii < nInps; ii++) {
		printf("Cobyla final X %d = %12.4e\n",ii+1,inputs[ii]);
	}
	printf("Optimal Y = %e\n", opt->getOptimalY());
	printf("Total number of function evaluations = %d\n", opt->getNumFuncEvals());

	delete [] inputs;
	delete [] lbnds;
	delete [] ubnds;

	return opt->getOptimalY();
}


int 
main(int argc, char **argv) 
{
	vector <params_t *> parameter_space;
	double result;

	parameter_space = read_cfg("parameters.cfg");

	result = min(objFunction, parameter_space, "bobyqa");

	return 0;
}
