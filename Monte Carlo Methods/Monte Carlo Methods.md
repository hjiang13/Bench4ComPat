Solving a problem with the Monte Carlo method involves a sampling of the solution space with thousands to millions of experiments. The numbers of independent experiments provide significant parallel opportunities, which high performance computing (HPC) experts often call “embarrassingly parallel”. While this describes the ample parallelism opportunities, there are still many implementation decisions that need to be made for efficient execution. Each experiment requires a three-step process:

1. Experiment generation: generating a random set of input parameters for an experiment
2. Experiment execution: executing the experiment with its input parameter
3. Result aggregation: aggregating the experimental results to into statistical relevant solutions.

At the top level, we may have one problem to solve, or a set of problems to solve. In Pi estimation, we have one value to estimate; in option pricing, we often have a batch of thousands of options to price, where all options can be priced in parallel. When there is more than one problem to solve, we have the multiple levels of parallel opportunities to explore. Given the potential SIMD level and core level parallelism in the implementation platform.

Many problem specific tradeoffs can be made based on the execution behavior of the experiments. Map-Reduce Structural Pattern can be use here, where the problem is expressed as a two phase program with a phase-1 mapping a single function onto independent sets of data (i.e. sets of i.i.d. experimental parameters), and a phase-2 reducing the experimental results into a statistical estimation as a solution; the solution is composed of the efficient distribution and load balancing of the mapping phase, and efficiently collecting the results in the reducing phase.

# Known Uses:
1. Statistical physics
Goal:
Parameter:
Typical experiment size:
Available Packages
http://en.wikipedia.org/wiki/Monte_Carlo_method_in_statistical_physics

2. Molecular modeling
Goal:
Parameters:
Typical experiment size:
Available Packages:
http://en.wikipedia.org/wiki/Monte_Carlo_molecular_modeling

3. Financial Risk Analysis
Goal: Simulating the effects of uncertain market conditions on the liability exposure of a contract or trading strategy
Parameters: Market conditions such as interest rates, prices of financial instruments (usually modeled by Brownian Motion with drift and volatility)
Typical experiment size: 5,000 to 500,000 experiments
Available Packages:
http://en.wikipedia.org/wiki/Monte_Carlo_methods_in_finance