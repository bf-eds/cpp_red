#include <filesystem>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>

namespace fs = std::filesystem;

// adapted from https://en.cppreference.com/w/cpp/filesystem/permissions
void outputPerms(fs::perms p, std::string_view title)
{
    if (!title.empty())
    {
        std::cout << title << ": ";
    }

    std::cout << "owner: " << ((p & fs::perms::owner_read) != fs::perms::none ? "r" : "-")
              << ((p & fs::perms::owner_write) != fs::perms::none ? "w" : "-")
              << ((p & fs::perms::owner_exec) != fs::perms::none ? "x" : "-");
    std::cout << " group: " << ((p & fs::perms::group_read) != fs::perms::none ? "r" : "-")
              << ((p & fs::perms::group_write) != fs::perms::none ? "w" : "-")
              << ((p & fs::perms::group_exec) != fs::perms::none ? "x" : "-");
    std::cout << " others: " << ((p & fs::perms::others_read) != fs::perms::none ? "r" : "-")
              << ((p & fs::perms::others_write) != fs::perms::none ? "w" : "-")
              << ((p & fs::perms::others_exec) != fs::perms::none ? "x" : "-") << '\n';
}

int main(int argc, char *argv[])
{
    try
    {
        const std::string sTempName{"hello.txt"};
        std::ofstream sample(sTempName);
        sample << "Hello World!\n";
        sample.close();

        outputPerms(fs::status(sTempName).permissions(), "after creation   ");
        fs::permissions(sTempName, fs::perms::owner_read/* | fs::perms::others_all*/, fs::perm_options::remove);
        outputPerms(fs::status(sTempName).permissions(), "after read change");

        auto fsize = fs::file_size(sTempName);
        std::cout << "fsize: " << fsize << '\n';

        std::ifstream testFile(std::string(sTempName), std::ios::binary | std::ios::ate);
        if (testFile.good())
        {
            std::cout << "tellgSize: " << testFile.tellg() << '\n';
        }
        else
        {
            throw std::runtime_error("cannot read file...");
        }
    }
    catch (const fs::filesystem_error &err)
    {
        std::cerr << "filesystem error! " << err.what() << '\n';
    }
    catch (const std::exception &ex)
    {
        std::cerr << "general exception: " << ex.what() << '\n';
    }
}