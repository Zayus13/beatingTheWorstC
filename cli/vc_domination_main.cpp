#include <iostream>

#include "CLI11.hpp"
#include "framework/graph.hpp"
#include "framework/vc_domination.hpp"
#include <filesystem>
#include <utility>
using namespace std;
namespace fs = std::filesystem;

int main(int argc, char **argv) {
    std::filesystem::current_path("/mnt/c/Users/sven_/Desktop/Beating the Worst Case/praktikum_beating_the_worst_case_framework/");
    CLI::App app{"GIRG generator"};
    // create option struct for graph generation
    std::filesystem::path directory_name_in;
    app.add_option("input_directory", directory_name_in,
                   "Name of the file containing the graph.")
            ->required()
            ->check(CLI::ExistingDirectory);

    CLI11_PARSE(app, argc, argv);

    //create output directory
    //check if directory already exists
    std::filesystem::path directory_name_out = directory_name_in / "vc_domination_output";
    if (std::filesystem::exists(directory_name_out)) {
        std::filesystem::remove_all(directory_name_out);
    }
    std::filesystem::create_directory(directory_name_out);
    int counter = 0;

    unsigned int kernel_size;

    for (const auto & entry : std::filesystem::directory_iterator(directory_name_in)) {
        if (!fs::is_regular_file(entry.path())) {
            continue;
        }
        counter++;
        if (counter % 10 == 0) {
            std::cout << counter << std::endl;
        }
        const std::filesystem::path& file_name_in = entry.path();
        Graph G(file_name_in);
        vc_domination vc(G);
        kernel_size = vc.get_kernel();
        std::filesystem::path file_name_out = directory_name_out / file_name_in.filename();
        file_name_out.replace_extension(".csv");
        std::ofstream output;
        output.open(file_name_out.string());
        output << kernel_size << std::endl;
        output.close();

    }

    return 0;
}
