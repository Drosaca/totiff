#include <regex>
#include <filesystem>
#include <stack>
#include "pathSolver.h"


bool pathSolver::match(const std::string &str, const std::string &pattern) {
    std::string p = pattern;
    p = std::regex_replace(p, std::regex("(\\\\)"), "\\\\");
    p = std::regex_replace(p, std::regex("(\\.)"), "\\.");
    p = std::regex_replace(p, std::regex("(\\*)"), ".*");
    bool res = std::regex_match(str, std::regex("(" + p + ")"));
    return res;
}

std::vector<std::filesystem::path>
pathSolver::search(std::filesystem::path &currentPath, std::vector<std::filesystem::path> &pathParts) {
    std::vector<std::filesystem::path> matches{};
    std::stack<std::pair<std::filesystem::path, int>> stack;
    stack.emplace(currentPath, 0);
    while (!stack.empty()) {
        std::filesystem::path curr = stack.top().first;
        int level = stack.top().second;
        stack.pop();
        for (auto &entry: std::filesystem::directory_iterator(curr)) {
            std::string pattern = (curr / pathParts[level]).string();
            if (match(entry.path().string(), pattern)) {
                if (level == pathParts.size() - 1) {
                    matches.emplace_back(entry.path().string());
                    continue;
                }
                stack.emplace(entry.path(), level + 1);
            }
        }
    }
    return matches;
}


std::vector<std::filesystem::path> pathSolver::resolve(const std::string &inputFile) {
    std::vector<std::filesystem::path> files;
    std::filesystem::path dir = inputFile;
    while (dir != dir.parent_path()) {
        if (std::filesystem::exists(dir)) {
            files.push_back(dir);
            break;
        }
        files.push_back(dir.filename());
        dir = dir.parent_path();
    }
    std::filesystem::path validPath = files.back();
    files.pop_back();
    std::reverse(files.begin(), files.end());
    std::vector<std::filesystem::path> matches = search(validPath, files);
    return matches;
};
