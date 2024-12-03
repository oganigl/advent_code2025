#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>

enum Movement {
    INCREASE,
    DECREASE,
};

bool is_safe(const std::vector<int>& report) {
    if (report.size() < 2) return false; // Reports with less than 2 elements are unsafe by definition

    Movement report_movement;
    int difference;
    
    for (size_t j = 0; j + 1 < report.size(); j++) {
        difference = report[j + 1] - report[j];
        if (j == 0) {
            report_movement = (difference > 0) ? INCREASE : DECREASE;
        }
        if (abs(difference) < 1 || abs(difference) > 3 || 
            (report_movement == INCREASE && difference < 0) || 
            (report_movement == DECREASE && difference > 0)) {
            return false;
        }
    }
    return true;
}

int check_safeness_of_reports(std::vector<std::vector<int>>& reports) {
    int safe_reports = 0;

    for (size_t i = 0; i < reports.size(); i++) {
        bool is_report_safe = is_safe(reports[i]);
        if (!is_report_safe) {
            // Try removing one element at a time
            for (size_t j = 0; j < reports[i].size(); j++) {
                std::vector<int> modified_report = reports[i];
                modified_report.erase(modified_report.begin() + j); // Remove the j-th element
                if (is_safe(modified_report)) {
                    is_report_safe = true;
                    break;
                }
            }
        }
        if (is_report_safe) {
            safe_reports++;
            std::cout << (i + 1) << ": Safe\n";
        } else {
            std::cout << (i + 1) << ": Unsafe\n";
        }
    }

    return safe_reports;
}

int main() {
    std::ifstream file("day2_puzzle");
    if (!file) {
        std::cerr << "Error opening the file!" << std::endl;
        return 1;
    }

    std::vector<std::vector<int>> reports;
    std::string line;
    int number;

    while (std::getline(file, line)) {
        reports.push_back({});
        std::istringstream iss(line);
        while (iss >> number) {
            reports.back().push_back(number);
        }
    }

    int reports_safe = check_safeness_of_reports(reports);
    std::cout << "Total safe reports: " << reports_safe << std::endl;

    return 0;
}
