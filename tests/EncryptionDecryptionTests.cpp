//
// Created by william on 11/23/23.
//

#include "EncryptionDecryptionTests.h"
#include "Encryption.h"
#include <gtest/gtest.h>

// Helper function to read file content
std::string readFileContent(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

// Test Fixture for setting up encryption and decryption
class EncryptionDecryptionTest : public ::testing::Test {
protected:
    std::string originalText = "Hello, World!";
    std::string inputFilename = "test_input.txt";
    std::string encryptedFilename = "test_encrypted.enc";
    std::string decryptedFilename = "test_decrypted.txt";
    std::string key;

    void SetUp() override {
        // Write original text to input file
        std::ofstream inputFile(inputFilename);
        inputFile << originalText;
        inputFile.close();

        // Encrypt the file and store the key
        Encryption::encryptFile(inputFilename, encryptedFilename);
        // Assume key is retrieved and stored in 'key' variable
    }

    void TearDown() override {
        // Remove test files after each test
        remove(inputFilename.c_str());
        remove(encryptedFilename.c_str());
        remove(decryptedFilename.c_str());
    }
};

// Test for successful encryption and decryption
TEST_F(EncryptionDecryptionTest, SuccessfulEncryptionAndDecryption) {
    // Decrypt the file
    Encryption::decryptFile(encryptedFilename, decryptedFilename, key);

    // Read the content of the decrypted file
    std::string decryptedText = readFileContent(decryptedFilename);

    // Check if the decrypted content matches the original
    EXPECT_EQ(decryptedText, originalText);
}

// Test for decryption failure with wrong key
TEST_F(EncryptionDecryptionTest, DecryptionFailureWithWrongKey) {
    std::string wrongKey = "IncorrectKey";

    // Expect the decryption to throw an error or fail
    EXPECT_ANY_THROW(Encryption::decryptFile(encryptedFilename, decryptedFilename, wrongKey));
}

// Add more tests as needed...

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

