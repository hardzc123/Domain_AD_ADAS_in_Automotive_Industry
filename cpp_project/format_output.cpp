#include <iostream>
#include <string>

void printUsage() {
    std::cout << "Usage:\n"
              << "    tool [options] <path-to-source>\n"
              << "    tool [options] <path-to-existing-build>\n"
              << "    tool [options] -S <path-to-source> -B <path-to-build>\n"
              << "\n"
              << "Specify a source directory to (re-)generate a build system for it in the\n"
              << "current working directory. Specify an existing build directory to\n"
              << "re-generate its build system.\n"
              << "\n"
              << "Run 'tool --help' for more information.\n";
}

int main(int argc, char* argv[]) {
    // If no arguments are provided or "--help" is specified
    if (argc < 2 || std::string(argv[1]) == "--help") {
        printUsage();
        return 0;
    }

    // Other logic for your tool...
    std::cout << "Running the tool with provided options...\n";

    return 0;
}