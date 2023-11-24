//
// Created by william on 11/23/23.
//


#ifndef ENCRYPTIONDECRYPTIONTESTS_H
#define ENCRYPTIONDECRYPTIONTESTS_H

#include <string>
#include <gtest/gtest.h>
#include "../include/Encryption.h"

// Here you can declare any helper functions or classes needed for your tests
// For example, a function to compare two files:

bool areFilesEqual(const std::string& filename1, const std::string& filename2);

// Or a fixture class for setting up common test environments:
class EncryptionDecryptionFixture : public ::testing::Test {
protected:
    void SetUp() override {
        // Code to set up test environment
    }

    void TearDown() override {
        // Code to clean up after tests
    }

    // Any shared variables or setup objects
};

#endif // ENCRYPTIONDECRYPTIONTESTS_H
