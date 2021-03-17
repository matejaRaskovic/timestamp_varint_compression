#include "varint_compression.h"

#include <iostream>

int main(){
    bool passed;

    std::cout << "<==========     TESTING COMPRESS SINGLE 64 BIT INT     ==========>" << std::endl << std::endl;
    int num_passed_1 = 0, total_1 = 0;

    // test 1
    std::cout << "Test 1:" << std::endl;
    passed = true;
    uint64_t t1_1 = 13579;
    std::cout << "Input: " << t1_1 << std::endl;
    uint8_t e1_1[2] = {0xEA, 0x0B};
    std::vector<uint8_t> t1_1_compressed = compress_single(t1_1);
    std::cout << "Output:   ";
    for (size_t i = 0; i < t1_1_compressed.size(); i++){
        std::cout << int(t1_1_compressed[i]) << " ";
    }
    std::cout << std::endl << "Expected: ";
    for (size_t i = 0; i < 2; i++){
        std::cout << int(e1_1[i]) << " ";
    }

    if (t1_1_compressed.size() == 2){
        for (size_t i = 0; i < t1_1_compressed.size(); i++){
            if (t1_1_compressed[i] != e1_1[i]) passed = false;
        }
    } else {
        passed = false;
    }
    std::cout << std::endl << std::endl;
    std::cout << (passed ? "PASSED" : "FAILED") << std::endl << std::endl << std::endl;
    num_passed_1 += passed;
    total_1++;

    // test 2
    std::cout << "Test 2:" << std::endl;
    passed = true;
    uint64_t t1_2 = 0;
    std::cout << "Input: " << t1_2 << std::endl;
    uint8_t e1_2[1] = {0x00};
    std::vector<uint8_t> t1_2_compressed = compress_single(t1_2);
    std::cout << "Output:   ";
    for (size_t i = 0; i < t1_2_compressed.size(); i++){
        std::cout << int(t1_2_compressed[i]) << " ";
    }
    std::cout << std::endl << "Expected: ";
    for (size_t i = 0; i < 1; i++){
        std::cout << int(e1_2[i]) << " ";
    }

    if (t1_2_compressed.size() == 1){
        for (size_t i = 0; i < t1_2_compressed.size(); i++){
            if (t1_2_compressed[i] != e1_2[i]) passed = false;
        }
    } else {
        passed = false;
    }
    std::cout << std::endl << std::endl;
    std::cout << (passed ? "PASSED" : "FAILED") << std::endl << std::endl << std::endl;
    num_passed_1 += passed;
    total_1++;

    // test 3
    std::cout << "Test 3:" << std::endl;
    passed = true;
    uint64_t t1_3 = ~0;
    std::cout << "Input: " << t1_3 << std::endl;
    uint8_t e1_3[10] = {0x81, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F};
    std::vector<uint8_t> t1_3_compressed = compress_single(t1_3);
    std::cout << "Output:   ";
    for (size_t i = 0; i < t1_3_compressed.size(); i++){
        std::cout << int(t1_3_compressed[i]) << " ";
    }
    std::cout << std::endl << "Expected: ";
    for (size_t i = 0; i < 10; i++){
        std::cout << int(e1_3[i]) << " ";
    }

    if (t1_3_compressed.size() == 10){
        for (size_t i = 0; i < t1_3_compressed.size(); i++){
            if (t1_3_compressed[i] != e1_3[i]) passed = false;
        }
    } else {
        passed = false;
    }
    std::cout << std::endl << std::endl;
    std::cout << (passed ? "PASSED" : "FAILED") << std::endl << std::endl << std::endl;
    num_passed_1 += passed;
    total_1++;

    std::cout << "Passed " << num_passed_1 << "/" << total_1 << std::endl << std::endl;


    std::cout << "<==========     TESTING DECOMPRESS SINGLE 64 BIT INT     ==========>" << std::endl << std::endl;
    int num_passed_2 = 0, total_2 = 0;

    // test 1
    std::cout << "Test 1:" << std::endl;
    passed = true;
    std::vector<uint8_t> t2_1{0xEA, 0x0B};
    std::cout << "Input: ";
    for (size_t i = 0; i < t2_1.size(); i++){
        std::cout << int(t2_1[i]) << " ";
    }
    std::cout << std::endl;
    uint64_t e2_1 = 13579;
    uint64_t t2_1_decompressed = decompress_single(t2_1);
    std::cout << "Output:   " << t2_1_decompressed << std::endl;
    std::cout << "Expected: " << e2_1 << std::endl;

    if (t2_1_decompressed != e2_1){
        passed = false;
    }
    std::cout << std::endl << std::endl;
    std::cout << (passed ? "PASSED" : "FAILED") << std::endl << std::endl << std::endl;
    num_passed_2 += passed;
    total_2++;

    // test 2
    std::cout << "Test 2:" << std::endl;
    passed = true;
    std::vector<uint8_t> t2_2{0x01};
    std::cout << "Input: ";
    for (size_t i = 0; i < t2_2.size(); i++){
        std::cout << int(t2_2[i]) << " ";
    }
    std::cout << std::endl;
    uint64_t e2_2 = 1;
    uint64_t t2_2_decompressed = decompress_single(t2_2);
    std::cout << "Output:   " << t2_2_decompressed << std::endl;
    std::cout << "Expected: " << e2_2 << std::endl;

    if (t2_2_decompressed != e2_2){
        passed = false;
    }
    std::cout << std::endl << std::endl;
    std::cout << (passed ? "PASSED" : "FAILED") << std::endl << std::endl << std::endl;
    num_passed_2 += passed;
    total_2++;

    // test 3
    std::cout << "Test 2:" << std::endl;
    passed = true;
    std::vector<uint8_t> t2_3{0x81, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F};
    std::cout << "Input: ";
    for (size_t i = 0; i < t2_3.size(); i++){
        std::cout << int(t2_3[i]) << " ";
    }
    std::cout << std::endl;
    uint64_t e2_3 = ~0;
    uint64_t t2_3_decompressed = decompress_single(t2_3);
    std::cout << "Output:   " << t2_3_decompressed << std::endl;
    std::cout << "Expected: " << e2_3 << std::endl;

    if (t2_3_decompressed != e2_3){
        passed = false;
    }
    std::cout << std::endl << std::endl;
    std::cout << (passed ? "PASSED" : "FAILED") << std::endl << std::endl << std::endl;
    num_passed_2 += passed;
    total_2++;

    std::cout << "Passed " << num_passed_2 << "/" << total_2 << std::endl << std::endl;

    return 0;
}
