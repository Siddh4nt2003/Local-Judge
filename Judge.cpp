#include <bits/stdc++.h>
#include <chrono>
#include <stdio.h>
#include <sys/wait.h>
#include <filesystem> // For C++17 filesystem library
using namespace std;
namespace fs = std::filesystem;

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        cerr << "Usage: " << argv[0] << " <Suffix>\n";
        return 1;
    }

    string suffix = argv[1];
    string checker = "Checker" + suffix;
    string input_dir = "./input_files" + suffix;

    // Compile Main.cpp
    system("g++ -std=c++20 ./Main.cpp -o Main.out");

    // Compile the specified Checker
    string checker_cpp = "./" + checker + ".cpp";
    string checker_out = checker + ".out";
    string compile_command = "g++ -std=c++20 " + checker_cpp + " -o " + checker_out;
    if (system(compile_command.c_str()) != 0)
    {
        cerr << "Error: Failed to compile " << checker_cpp << '\n';
        return 1;
    }

    for (const auto& entry : fs::directory_iterator(input_dir))
    {
        if (entry.is_regular_file() && entry.path().extension() == ".txt")
        {
            string input_file = entry.path().string();
            string output_file = "output.txt";
            // string output_file = "output_" + entry.path().stem().string() + ".txt";

            cout << "Processing: " << input_file << '\n';
            
            auto start = std::chrono::high_resolution_clock::now();
            string command = "timeout 4 ./Main.out < " + input_file + " > " + output_file;
            int ret = system(command.c_str());
            
            auto stop = std::chrono::high_resolution_clock::now();
            const std::chrono::duration<double, std::milli> fp_ms = stop - start;
            
            if (WEXITSTATUS(ret) != 0)
                cout << "Error: Program exited with code " << ret << '\n';
            else
                cout << "Executed!\n";
            cout << "Time taken: " << fp_ms.count() << "ms\n";
            
            if (fp_ms.count() > 4000.00)
            {
                cout << "Time Limit Exceeded\n";
                continue;
            }

            // Checker
            auto startJ = std::chrono::high_resolution_clock::now();
            string judge_command = "timeout 4 ./" + checker_out + " < " + input_file;
            int retJ = system(judge_command.c_str());
            
            auto stopJ = std::chrono::high_resolution_clock::now();
            const std::chrono::duration<double, std::milli> fp_msJ = stopJ - startJ;
            
            if (WEXITSTATUS(retJ) != 0)
                cout << "Judge has a different output\n";
            else
                cout << "Accepted\n";
        }
    }

    return 0;
}
