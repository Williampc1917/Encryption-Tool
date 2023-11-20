#include <iostream>
#include <boost/program_options.hpp>
#include <string>
#include <fstream>
#include "../include/Encryption.h"

namespace po = boost::program_options;

int main(int argc, char *argv[]) {

    // Define command-line options
    po::options_description desc("Allowed options");
    desc.add_options()
            ("help,h", "produce help message")
            ("encrypt,e", "encrypt a file")
            ("decrypt,d", "decrypt a file")
            ("generate-key,g", "generate a new key")
            ("list-keys,l", "list all stored keys")
            ("retrieve-key,r", po::value<std::string>(), "retrieve a specified key")
            ("input-file,i", po::value<std::string>(), "input file path")
            ("output-file,o", po::value<std::string>(), "output file path");

    // Variables to store the parsed command-line arguments
    po::variables_map vm;

    try {
        // Parse command-line arguments
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);

        // Check if help was requested
        if (vm.count("help")) {
            std::cout << desc << "\n";
            return 0;
        }

        // Check each command and call the appropriate function
        if (vm.count("encrypt")) {
            if(vm.count("input-file")&& vm.count("output-file")) {
                std::string inputFile = vm["input-file"].as<std::string>();
                std::string outputFile = vm["output-file"].as<std::string>();

                std::cout << "Encrypting" << inputFile << "to" << outputFile << "\n";

                // check if input file exists and can be opened
                std::ifstream inFile(inputFile, std::ifstream::binary);

                if (!inFile) {
                    std::cerr << "Error: Unable to open input file: " << inputFile << "\n";
                    return 1;
                }

                // Call the encryption function from the Encryption class
                Encryption::encryptFile(inputFile, outputFile);

                // close the file stream
                inFile.close();

            } else{
                std::cout << "Missing file path or output path for encryption .\n";
                return 1;
            }


            std::cout << "Encryption Done!.\n";
            // Call encryption function
        } else if (vm.count("decrypt")) {

            if(vm.count("input-file") && vm.count("output-file")) {
                std::string inputFile = vm["input-file"].as<std::string>();
                std::string outputFile = vm["output-file"].as<std::string>();

                std::cout << "Decrypting " << inputFile << " to " << outputFile << "\n";

            // Prompt for the encryption key
            std::string encryptionKey;
            std::cout << "Please enter the encryption key: ";
            std::getline(std::cin, encryptionKey); //Read the key

            // Read the encrypted file
            std::ifstream inFile(inputFile, std::ios::binary);
            if(!inFile){
                std::cerr << "Error: unable to open input file " << inputFile << "\n";
                return 1;
            }

            // Call the decryption function
            Encryption::decryptFile(inputFile, outputFile, encryptionKey);

            std::cout << "Decryption Done!" << "\n";
            }else{
                std::cout << "Missing file path or output path for decryption" << "\n";
                return 1;
            }

            //std::cout << "Decryption requested.\n";
            // Call decryption function
        } else if (vm.count("generate-key")) {
            std::cout << "Key generation requested.\n";
            // Generate and store a new key
        } else if (vm.count("list-keys")) {
            std::cout << "Listing all stored keys.\n";
            // List all stored keys
        } else if (vm.count("retrieve-key")) {
            std::string keyId = vm["retrieve-key"].as<std::string>();
            std::cout << "Retrieving key: " << keyId << "\n";
            // Retrieve the specified key
        } else {
            std::cout << "Invalid command. Use --help for usage information.\n";
            return 1;
        }
    }
    catch (const po::error &ex) {
        std::cerr << ex.what() << '\n';
        return 1;
    }

    return 0;
}