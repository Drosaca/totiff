

#ifndef PATH_SOLVER_H
#define PATH_SOLVER_H

#include <regex>
#include <filesystem>
#include <stack>

class pathSolver {
    static bool match(const std::string &str, const std::string &pattern);
    static std::vector<std::filesystem::path> search(std::filesystem::path &currentPath, std::vector<std::filesystem::path> &pathParts);
public:
    static std::vector<std::filesystem::path> resolve(const std::string& inputFile) ;
};

#endif