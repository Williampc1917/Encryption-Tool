//
// Created by william on 11/17/23.
//
#include "../include/Encryption.h"
#include <cryptopp/aes.h>  // Example: Including Crypto++ headers
#include <cryptopp/modes.h>
#include <cryptopp/filters.h>
#include <cryptopp/osrng.h>// For the random number generator
#include <files.h>
#include <hex.h>
#include <termio.h>
#include <unistd.h>

// ... other necessary includes

class SDKOptions;

static CryptoPP::SecByteBlock HexToBinary(const std::string& hex);

void Encryption::encryptFile(const std::string& inputFile, const std::string& outputFile) {
    // Implement your encryption logic here
    // Example: Open the input file, read data, encrypt it, and write to the output file

    std::ifstream inFile (inputFile, std::ios::binary);
    if(!inFile){
        throw std::runtime_error("Cannot open input file");
    }

    // Key and IV generation
    CryptoPP::AutoSeededRandomPool rng;
    CryptoPP::SecByteBlock key(CryptoPP::AES::DEFAULT_KEYLENGTH);
    rng.GenerateBlock(key, key.size());
    CryptoPP::byte iv[CryptoPP::AES::BLOCKSIZE];
    rng.GenerateBlock(iv, sizeof(iv));

    // Encrypt data
    std::string encryptedData;
    // ... Encryption code below

    // Encryption code below
    try {
        // Set up the AES encryption in CBC mode
        CryptoPP::CBC_Mode<CryptoPP::AES>::Encryption encryptor;
        encryptor.SetKeyWithIV(key, key.size(), iv);

        // Create a new StringSink that writes to encryptedData
        CryptoPP::StringSink* stringSink = new CryptoPP::StringSink(encryptedData);

        // Create a new StreamTransformationFilter
        CryptoPP::StreamTransformationFilter* stfEncryptor = new CryptoPP::StreamTransformationFilter(encryptor, stringSink);

        // Create a new FileSource that reads from inFile and writes to stfEncryptor
        CryptoPP::FileSource fs(inFile, true, stfEncryptor);
    } catch(const CryptoPP::Exception& e) {
        std::cerr << "Error during encryption: " << e.what() << std::endl;
        throw;
    }

    inFile.close();


    // After encryption is done, display the key to the user
    std::string hexKey;
    CryptoPP::ArraySource as(key.data(), key.size(), true,new CryptoPP::HexEncoder(new CryptoPP::StringSink(hexKey)) // HexEncoder
    ); // ArraySource

    std::cout << "Encryption Key: " << hexKey << std::endl;
    std::cout << "Please store this key in a secure location, this key will be required for decryption";

    // Write encrypted data to the output file
    std::ofstream outFile(outputFile, std::ios::binary);
    if (!outFile) {
        throw std::runtime_error("Cannot open output file");
    }
    // Write IV first
    outFile.write(reinterpret_cast<const char*>(iv), sizeof(iv));
    // Write encrypted data
    outFile.write(encryptedData.c_str(), encryptedData.size());
    outFile.close();

    // Securely handle the key
    // For example, you can display it to the user, write it to a secure location, or use a password-based key derivation function
    // User will be storing and handling their key safety !!!!!!!!!
}

void Encryption::decryptFile (const std::string& inputFile, const std::string& outputFile, const std::string& key){

    // Open the input file
    std::ifstream inFile(inputFile, std::ios::binary);
    if (!inFile) {
        throw std::runtime_error("Cannot open input file");
    }

    // Read the IV from the file
    CryptoPP::byte iv[CryptoPP::AES::BLOCKSIZE];
    inFile.read(reinterpret_cast<char*>(iv), sizeof(iv));

    // Convert the key from string to SecByteBlock
    CryptoPP::SecByteBlock keySec = HexToBinary(key);



    std::string decryptedData;

    try {
        // Set up AES decryption in CBC mode
        CryptoPP::CBC_Mode<CryptoPP::AES>::Decryption decryptor;
        decryptor.SetKeyWithIV(keySec, keySec.size(), iv);

        // Create a FileSource
        CryptoPP::FileSource fs(inFile, true,new CryptoPP::StreamTransformationFilter(decryptor,new CryptoPP::StringSink(decryptedData)) // StreamTransformationFilter
        ); // FileSource
    } catch (const CryptoPP::Exception& e) {
        std::cerr << "Decryption error: " << e.what() << std::endl;
        throw;
    }

    inFile.close();

    // Write the decrypted data to the output file
    std::ofstream outFile(outputFile, std::ios::binary);
    if (!outFile) {
        throw std::runtime_error("Cannot open output file");
    }
    outFile.write(decryptedData.c_str(), decryptedData.size());
    outFile.close();

}

static CryptoPP::SecByteBlock HexToBinary(const std::string& hex) {
    CryptoPP::SecByteBlock binary((hex.size() + 1) / 2);
    CryptoPP::StringSource ss(hex, true, new CryptoPP::HexDecoder);
    ss.Get(binary, binary.size());
    return binary;
}


// Function to hide when the user inputs their key or copy and paste
std::string getHiddenInput(){

    termios oldt;
    tcgetattr(STDIN_FILENO, reinterpret_cast<termios *>(&oldt));
    termios newt = oldt;
    newt.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    std::string input;
    std::getline(std::cin, input);

    tcsetattr(STDIN_FILENO, TCSANOW, reinterpret_cast<const termios *>(&oldt));
    return input;

}
