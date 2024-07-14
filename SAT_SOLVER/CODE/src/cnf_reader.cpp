#include <fstream>
#include <sstream>

#include "../header/cnf_reader.h"

CNF_Reader::CNF_Reader(std::string path){

    std::ifstream filestream;
    filestream.open(path);
    std::string word;
    std::string line;
    std::string temp;
    std::stringstream temp_stream;
    std::vector<int> clause;

    int curr_clause = 0;
    while(filestream >> word) {
        if(word == "c") {continue;}
        if(word == "p") {
            filestream >> word;
            filestream >> word;
            no_variables = std::stoi(word);
            filestream >> word;
            no_clauses = std::stoi(word);
            break;
        }
    }

    temp = "";
    clause_s.resize(no_clauses);

    while(getline(filestream,line)) {
        if(line[line.size() -1 ] == '0') {
            temp_stream.clear();
            temp_stream << temp << line;
            temp_stream >> temp;
            clause.clear();

            while(temp != "0") {
                clause.push_back(std::stoi(temp));
                temp_stream >> temp;
            }
            clause_s[curr_clause++] = clause;
            temp = "";
        } else {
            temp = temp + line + " ";
        }
    }

    // Debugging output
    std::cout << "Parsed clauses:" << std::endl;
    for(const auto& cl : clause_s) {
        for(int lit : cl) {
            std::cout << lit << " ";
        }
        std::cout << "0" << std::endl;
    }
}

int CNF_Reader::return_no_vars() { return no_variables; }

int CNF_Reader::return_no_clauses() { return no_clauses;}

std::vector<std::vector<int>> CNF_Reader::return_clauses() {return clause_s;}