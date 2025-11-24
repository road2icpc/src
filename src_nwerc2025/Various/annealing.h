//@ Author: cp-algorithms
//@ Date: 2025-05-21
//@ License: CC0
//@ Source: cp-algorithms
//@ Status: Not tested

//# Title: Simmulated Annealing
//# Description: [cp-algorithms] A randomized approach to approximate a global optimum of a function (i.e TSP).
//# Usage:
//#  Fill in the state class:
//#    state() should be the initial state (initial guess)
//#    next() should create a neighbouring state, i.e. (For TSP swap two nodes in the order)
//#    E() should be the energy function, the thing that should be maximized. (For TSP the total distance)
//# Complexity: $\mathcal{O}(E() \cdot log_{1 / u}(T))$.

//@ tested on:
//@  nothing :(

bool P(double E,double E_next,double T,mt19937 rng){
    double prob =  exp(-(E_next-E)/T);
    if(prob > 1) return true;
    else{
        bernoulli_distribution d(prob); 
        return d(rng);
    }
}
class state {
    public:
    state() {
        // Generate the initial state
    }
    state next() {
        state s_next;
        // Modify s_next to a random neighboring state
        return s_next;
    }
    double E() {
        // Implement the energy function here
    };
};


pair<double, state> simAnneal() {
    state s = state();
    state best = s;
    double T = 10000; // Initial temperature
    double u = 0.995; // decay rate
    double E = s.E();
    double E_next;
    double E_best = E;
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    while (T > 1) {
        state next = s.next();
        E_next = next.E();
        if (P(E, E_next, T, rng)) {
            s = next;
            if (E_next < E_best) {
                best = s;
                E_best = E_next;
            }
            E = E_next;
        }
        T *= u;
    }
    return {E_best, best};
}
