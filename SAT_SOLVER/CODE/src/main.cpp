#include "../header/sat_solver.h"
#include "../header/cnf_reader.h"
int main(int argc, char**argv) {
    if(argc != 2){std::cout << "Command line arguments incorrect: ./executable cnf_file_path" << std::endl;exit(-1);};
    std::string path = "../test";
    CNF_Reader reader(argv[1]);

    int no_variables = reader.return_no_vars();
    std::vector<std::vector<int>> clauses = reader.return_clauses();
    // std::cout << reader.no_variables;
    Solver solver(no_variables, clauses);

    if (solver.Solve()) {
        std::cout << "SATISFIABLE" << std::endl;
        solver.print_assignments();
    } else {
        std::cout << "UNSATISFIABLE" << std::endl;
    }

    return 0;
}
