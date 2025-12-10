#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include <filesystem>
#include <atomic>
#include <csignal>
#include <cstdio>
#include <windows.h>

namespace fs = std::filesystem;

// Global variable for graceful exit
std::atomic<bool> stop_requested(false);

// Signal handler function
void signal_handler(int signal) {
    stop_requested = true;
}

// Run a program with input/output redirection
bool run_program(const std::string& exe_path, 
                 const std::string& input_file, 
                 const std::string& output_file) {
    // Build command
    std::string command = "\"" + exe_path + "\"";
    
    // Use CreateProcess on Windows
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));
    
    // Setup input/output redirection
    HANDLE hInputFile = CreateFileA(input_file.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hInputFile == INVALID_HANDLE_VALUE) {
        std::cerr << "Failed to open input file: " << input_file << " (" << GetLastError() << ")" << std::endl;
        return false;
    }
    
    HANDLE hOutputFile = CreateFileA(output_file.c_str(), GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hOutputFile == INVALID_HANDLE_VALUE) {
        std::cerr << "Failed to open output file: " << output_file << " (" << GetLastError() << ")" << std::endl;
        CloseHandle(hInputFile);
        return false;
    }
    
    si.dwFlags |= STARTF_USESTDHANDLES;
    si.hStdInput = hInputFile;
    si.hStdOutput = hOutputFile;
    si.hStdError = GetStdHandle(STD_ERROR_HANDLE);
    
    // Create process
    if (!CreateProcess(
        NULL,                   // No module name (use command line)
        const_cast<LPSTR>(command.c_str()), // Command line
        NULL,                   // Process handle not inheritable
        NULL,                   // Thread handle not inheritable
        TRUE,                   // Inherit handles
        0,                      // No creation flags
        NULL,                   // Use parent's environment
        NULL,                   // Use parent's working directory
        &si,                    // Startup info
        &pi)                    // Process info
    ) {
        std::cerr << "CreateProcess failed (" << GetLastError() << "): " << command << std::endl;
        CloseHandle(hInputFile);
        CloseHandle(hOutputFile);
        return false;
    }
    
    // Wait until process exits
    WaitForSingleObject(pi.hProcess, INFINITE);
    
    // Get exit code
    DWORD exit_code;
    GetExitCodeProcess(pi.hProcess, &exit_code);
    
    // Close handles
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    CloseHandle(hInputFile);
    CloseHandle(hOutputFile);
    
    return exit_code == 0;
}

// Run data generator with output to file
bool run_data_generator(const std::string& exe_path, const std::string& output_file) {
    // Build command
    std::string command = "\"" + exe_path + "\"";
    
    // Use CreateProcess on Windows
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));
    
    // Setup output redirection
    HANDLE hOutputFile = CreateFileA(output_file.c_str(), GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hOutputFile == INVALID_HANDLE_VALUE) {
        std::cerr << "Failed to open output file: " << output_file << " (" << GetLastError() << ")" << std::endl;
        return false;
    }
    
    si.dwFlags |= STARTF_USESTDHANDLES;
    si.hStdInput = GetStdHandle(STD_INPUT_HANDLE);
    si.hStdOutput = hOutputFile;
    si.hStdError = GetStdHandle(STD_ERROR_HANDLE);
    
    // Create process
    if (!CreateProcess(
        NULL,                   // No module name (use command line)
        const_cast<LPSTR>(command.c_str()), // Command line
        NULL,                   // Process handle not inheritable
        NULL,                   // Thread handle not inheritable
        TRUE,                   // Inherit handles
        0,                      // No creation flags
        NULL,                   // Use parent's environment
        NULL,                   // Use parent's working directory
        &si,                    // Startup info
        &pi)                    // Process info
    ) {
        std::cerr << "CreateProcess failed (" << GetLastError() << "): " << command << std::endl;
        CloseHandle(hOutputFile);
        return false;
    }
    
    // Wait until process exits
    WaitForSingleObject(pi.hProcess, INFINITE);
    
    // Get exit code
    DWORD exit_code;
    GetExitCodeProcess(pi.hProcess, &exit_code);
    
    // Close handles
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    CloseHandle(hOutputFile);
    
    return exit_code == 0;
}

// Compare two files
bool compare_files(const std::string& file1, const std::string& file2) {
    std::ifstream f1(file1, std::ifstream::binary);
    std::ifstream f2(file2, std::ifstream::binary);
    
    if (!f1.is_open()) {
        std::cerr << "Error opening file: " << file1 << std::endl;
        return false;
    }
    if (!f2.is_open()) {
        std::cerr << "Error opening file: " << file2 << std::endl;
        return false;
    }
    
    // Compare file sizes
    f1.seekg(0, std::ifstream::end);
    f2.seekg(0, std::ifstream::end);
    if (f1.tellg() != f2.tellg()) {
        return false;
    }
    
    // Compare content
    f1.seekg(0, std::ifstream::beg);
    f2.seekg(0, std::ifstream::beg);
    
    const size_t buffer_size = 4096;
    char buffer1[buffer_size], buffer2[buffer_size];
    
    while (f1.read(buffer1, buffer_size) || f2.read(buffer2, buffer_size)) {
        if (memcmp(buffer1, buffer2, f1.gcount()) != 0) {
            return false;
        }
    }
    
    return true;
}

// Set console color
void set_console_color(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

// Reset console color
void reset_console_color() {
    set_console_color(7); // Default gray
}

int main() {
    // Set console to UTF-8
    SetConsoleOutputCP(65001);
    
    // Set signal handler
    std::signal(SIGINT, signal_handler);
    
    // Create necessary directories
    fs::create_directory("execute");
    fs::create_directory("io");
    
    // Check if executables exist
    if (!fs::exists("execute/make_data.exe")) {
        std::cerr << "Error: Data generator not found! Please compile make_data.cpp to execute/make_data.exe" << std::endl;
        return 1;
    }
    if (!fs::exists("execute/mycode.exe")) {
        std::cerr << "Error: Your program not found! Please compile mycode.cpp to execute/mycode.exe" << std::endl;
        return 1;
    }
    if (!fs::exists("execute/std.exe")) {
        std::cerr << "Error: Standard program not found! Please compile std.cpp to execute/std.exe" << std::endl;
        return 1;
    }
    
    std::cout << "Starting comparison... (Press Ctrl+C to stop)" << std::endl;
    
    int test_case = 1;
    int ac_count = 0;
    auto start_time = std::chrono::steady_clock::now();
    
    while (!stop_requested) {
        // Generate test data
        std::string data_file = "io/data.in";
        if (!run_data_generator("execute/make_data.exe", data_file)) {
            std::cerr << "Failed to generate test data!" << std::endl;
            break;
        }
        
        // Run both programs
        if (!run_program("execute/mycode.exe", data_file, "io/mycode.out")) {
            std::cerr << "Failed to run mycode!" << std::endl;
            break;
        }
        if (!run_program("execute/std.exe", data_file, "io/std.out")) {
            std::cerr << "Failed to run std!" << std::endl;
            break;
        }
        
        // Compare outputs
        if (compare_files("io/mycode.out", "io/std.out")) {
            ac_count++;
            if (test_case % 10 == 0) {
                auto now = std::chrono::steady_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::seconds>(now - start_time);
                double speed = (duration.count() > 0) ? (test_case * 1.0 / duration.count()) : test_case;
                
                std::cout << "Tested " << test_case << " cases (" 
                          << speed << " cases/sec) - ";
                set_console_color(10); // Green
                std::cout << "ACCEPTED";
                reset_console_color();
                std::cout << std::endl;
            }
        } else {
            set_console_color(12); // Red
            std::cout << "\nTest case " << test_case << " WRONG ANSWER!\n";
            reset_console_color();
            
            // Save wrong data
            fs::copy_file(data_file, "io/wa.in", fs::copy_options::overwrite_existing);
            std::cout << "Wrong data saved to io/wa.in\n";
            std::cout << "Your output: io/mycode.out\n";
            std::cout << "Expected output: io/std.out\n";
            break;
        }
        
        test_case++;
    }
    
    auto end_time = std::chrono::steady_clock::now();
    auto total_duration = std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time);
    double avg_speed = (total_duration.count() > 0) ? (test_case * 1.0 / total_duration.count()) : test_case;
    
    std::cout << "\nTesting finished. Total cases: " << (test_case - 1) << std::endl;
    std::cout << "Accepted: " << ac_count << " cases" << std::endl;
    std::cout << "Average speed: " << avg_speed << " cases/sec" << std::endl;
    
    if (ac_count == test_case - 1) {
        set_console_color(10); // Green
        std::cout << "All tests passed successfully!";
        reset_console_color();
    } else if (ac_count > 0) {
        set_console_color(14); // Yellow
        std::cout << "Partial tests passed.";
        reset_console_color();
    }
    std::cout << std::endl;
    
    return 0;
}