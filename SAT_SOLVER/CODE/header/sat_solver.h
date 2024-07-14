#ifndef HEADERS
#define HEADERS 1
#include <bits/stdc++.h>
#include <vector>
#include <map>
#include <set>
#include <string>
#endif
#define TRUE 1
#define FALSE 0
#define UNASSIGNED -1

class Solver {
    private:
        int no_variables;
        int no_clauses;
        int assigned;
        std::vector<std::vector<int>> clause_s;
        std::vector<int> clause_sizes;
        std::vector<int> positives;
        std::vector<int> negatives;
        std::vector<bool> clause_set;

    public:
        std::vector<int> assignments;

        //Constructors
        Solver() {}
        Solver(int no_variables_in, std::vector<std::vector<int>> clause_s_in, int assigned_in, std::vector<int> clause_sizes_in,
               std::vector<int> positives_in, std::vector<int> negatives_in, std::vector<int> assignments_in,std::vector<bool> clause_set_in);
        Solver(int no_variables_in, std::vector<std::vector<int>> clause_s_in);

        //Helper functions
        bool setVariable(int variable, int assignment);
        int Unit_clause_elimination();
        int Pure_literal_elimination();

        //Solving, outputting results
        bool Solve();
        void print_assignments();
};

