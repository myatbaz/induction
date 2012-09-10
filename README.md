induction
=========

Non-parametric feature based Bayesian algorithms

v0.0.3
	-Christodoulopoulos et al. (2012) is implemented with basic functionality
	-Calculates log and normal probabilities
	-Random initialization is available
	-[POSSIBLE BUG]:Numerical stability due to multiplication of too many small probabilities.

v0.0.2
	-Tok k feature values threshold is added
	-learn.cpp and type.cpp are added
	-Format the data to start learning

v0.0.1
	-Read gzip, stdin and regular text files
	-Creates a hash entry for every input token
	-Converts the token data to id-data using hash corresponding values

------FUTURE WORK------
	-Memory/CPU time logs might be helpful
	-Test modem on artificial data
	-Implement Likelihood function
	-Implement the cool-down and hyper parameter updates
	-Implement the score functions