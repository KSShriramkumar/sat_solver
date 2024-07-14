#include "../header/sat_solver.h"

        Solver::Solver(int no_variables_in, std::vector<std::vector<int>> clause_s_in, int assigned_in, std::vector<int> clause_sizes_in,
               std::vector<int> positives_in, std::vector<int> negatives_in, std::vector<int> assignments_in,std::vector<bool>clause_set_in) {
            no_variables = no_variables_in;
            no_clauses = clause_s_in.size();
            assigned = assigned_in;
            clause_s = clause_s_in;
            clause_sizes = clause_sizes_in;
            positives = positives_in;
            negatives = negatives_in;
            assignments = assignments_in;
            clause_set = clause_set_in;
        }

        Solver::Solver(int no_variables_in, std::vector<std::vector<int>> clause_s_in) {
            assignments.clear();
            clause_sizes.clear();
            assigned = 0;
            no_variables = no_variables_in;
            assignments.resize(no_variables_in + 1, UNASSIGNED);
            positives.clear();
            negatives.clear();
            positives.resize(no_variables_in + 1, 0);
            negatives.resize(no_variables_in + 1, 0);
            clause_s = clause_s_in;
            no_clauses = clause_s.size();
            clause_set.resize(no_clauses,false);
            clause_sizes.resize(no_clauses, 0);

            for(int i = 0; i < no_clauses; i++) {
                clause_sizes[i] = clause_s[i].size();
                for(int j = 0; j < clause_s[i].size(); j++) {
                    if(clause_s[i][j] < 0) {
                        negatives[-clause_s[i][j]]++;
                    } else {
                        positives[clause_s[i][j]]++;
                    }
                }
            }
        }      

        bool Solver::setVariable(int variable, int assignment) {
            if(assignments[variable] != UNASSIGNED) {
                std::cout << "Error: Assigning already assigned variable " << variable << std::endl;
                exit(-1);
            }
            assignments[variable] = assignment;
            std::cout << "Assigned variable " << variable << " to " << assignment << std::endl;
            std::vector<int> copy = clause_sizes;
            std::vector<int> copy_pos = positives;
            std::vector<int> copy_neg = negatives; 
            std::vector<bool> copy_clause_set = clause_set;
            bool not_marked = true;
            for(int i = 0; i < no_clauses; i++) {
                not_marked = true;
                for(int j = 0; j < clause_s[i].size(); j++) {
                    if(clause_s[i][j] == variable || clause_s[i][j] == -variable) {
                        copy[i]--;
                        if((clause_s[i][j] == variable && assignment == TRUE || clause_s[i][j] == -variable && assignment == FALSE) && not_marked) {
                            not_marked = false;
                            copy_clause_set[i] = true;
                            for(int k = 0; k < clause_s[i].size(); k++) {
                                if(assignments[clause_s[i][j]] == UNASSIGNED) {
                                    if(clause_s[i][j] < 0) copy_neg[-clause_s[i][j]]--;
                                    else copy_pos[clause_s[i][j]]--;
                                }
                            }
                        } 
                        if(copy[i] == 0) {
                            bool is_true = false;
                            for(int k = 0; k < clause_s[i].size(); k++) {
                                if((clause_s[i][k] > 0 && assignments[std::abs(clause_s[i][k])] == TRUE) || 
                                   (clause_s[i][k] < 0 && assignments[std::abs(clause_s[i][k])] == FALSE)) {
                                    is_true = true;
                                    break;
                                }
                            }
                            if(!is_true) {   
                                assignments[variable] = -1;
                                return false;
                            }
                        }
                    }
                }
            }

            clause_sizes = copy;
            assignments[variable] = assignment;
            assigned++;
            positives = copy_pos;
            clause_set = copy_clause_set;
            negatives = copy_neg;
            return true;
        }

        int Solver::Unit_clause_elimination() {
            int var = -1;
            int dummy;
            for(int i = 0; i < no_clauses; i++) {
                if(clause_sizes[i] == 1 && !clause_set[i]) {
                    std::cout << "Unit clause " << i << std::endl;
                    for(int j = 0; j < clause_s[i].size(); j++) {
                        if(assignments[std::abs(clause_s[i][j])] == UNASSIGNED) {
                            var = clause_s[i][j];
                            break;
                        }
                    }
                    if(var > 0) {
                        dummy = TRUE;
                    } else {
                        dummy = FALSE;
                    }

                    bool result = setVariable(std::abs(var), dummy);
                    if(!result) {
                        return -1;
                        exit(-1);
                    }
                    return 1;
                }
            }
            return 0;
        }

        int Solver::Pure_literal_elimination() {
            for(int i = 1; i <= no_variables; i++) {
                if(assignments[i] == UNASSIGNED) {
                    if(negatives[i] == 0 && positives[i] != 0) {
                        bool result = setVariable(i, TRUE);
                        if(result == false) {
                            return -1;
                        }
                        return 1; 
                    } else {
                        if(negatives[i] != 0 && positives[i] == 0) {
                            bool result = setVariable(i, FALSE);
                            if(result == false) {
                                return -1;
                            }
                            return 1;
                        }
                    }
                }
            }
            return 0;
        }

        bool Solver::Solve() {
            std::cout << "Solving: assigned = " << assigned << " / " << no_variables << std::endl;
            if(assigned == no_variables) {return true;}
            int unit, pure;
            Solver* Zero;
            Solver* One;
            do {
                unit = Unit_clause_elimination();
                std::cout << "Unit:" << unit << std::endl;
                if(unit == -1) {
                    return false;
                }
                pure = Pure_literal_elimination();
                std::cout << "Pure:" << pure << std::endl;
                if(pure == -1) {
                    return false;
                }
            } while(unit != 0 || pure != 0);
             if(assigned == no_variables) {return true;}
            for(int i = 1; i <= no_variables; i++) {
                if(assignments[i] == UNASSIGNED) {
                    std::cout << "Trying: " << i << std::endl;
                    Zero = new Solver(no_variables, clause_s, assigned, clause_sizes, positives, negatives, assignments,clause_set);

                    if(Zero->setVariable(i, FALSE)) {
                        if(Zero->Solve()) {
                            assignments = Zero->assignments;
                            return true;
                        } else {
                            delete Zero;
                        }
                    }
                    One = new Solver(no_variables, clause_s, assigned, clause_sizes, positives, negatives, assignments,clause_set);
                    if(One->setVariable(i, TRUE)) {
                        if(One->Solve()) {
                            assignments = One->assignments;
                            return true;
                        } else {
                            delete One;
                        }
                    }
                    break;
                }
            }
            return false;
        }

        void Solver::print_assignments() {
            for(int i = 1; i <= no_variables; i++) {
                std::cout << i << ":" << assignments[i] << std::endl;
            }
        }