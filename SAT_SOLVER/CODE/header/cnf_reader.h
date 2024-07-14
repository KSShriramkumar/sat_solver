#ifndef HEADERS
#define HEADERS 1
#include <bits/stdc++.h>
#include <vector>
#include <map>
#include <set>
#include <string>
#endif
class CNF_Reader {
    public:
        std::string path;
        int no_variables;
        int no_clauses;
        std::vector<std::vector<int>> clause_s;

        //constructor
        CNF_Reader(std::string path);

        //return functions
        int return_no_vars();
        int return_no_clauses() ;

        std::vector<std::vector<int>> return_clauses();
};
