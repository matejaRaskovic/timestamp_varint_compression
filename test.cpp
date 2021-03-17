#include "varint_compression.h"

#include <iostream>
#include <chrono>

int main(){
    bool passed;

    std::cout << "<==========     TESTING COMPRESS SINGLE 64 BIT INT     ==========>" << std::endl << std::endl;
    int num_passed_1 = 0, total_1 = 0;

    // test 1
    std::cout << "Test 1:" << std::endl << std::endl;
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
    std::cout << "Test 2:" << std::endl << std::endl;
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
    std::cout << "Test 3:" << std::endl << std::endl;
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
    std::cout << "Test 1:" << std::endl << std::endl;
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
    std::cout << "Test 2:" << std::endl << std::endl;
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
    std::cout << "Test 3:" << std::endl << std::endl;
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


    std::cout << "<==========     TESTING SEQUENCE COMPRESSION + DECOMPRESSION     ==========>" << std::endl << std::endl;

    int num_tests = 10;
    int total_passed = 0;
    bool passed_comp_decomp[10];
    srand(37);

    uint64_t seq_starts[num_tests] = {24234, 3453823, 11111, 8, 8433, 97397, 987654321, 157, 736492, 20202021};
    for (int i = 0; i < num_tests; i++){
        std::cout << "Test " << i << ": " << std::endl << std::endl;
        passed_comp_decomp[i] = true;
        int seq_len = rand() % 10 + 5;
        std::vector<uint64_t> original;
        original.push_back(seq_starts[i]);
        for (int j = 1; j < seq_len; j++){
            original.push_back(original[j-1] + (rand() % 10000 + 5));
        }
        std::vector<uint8_t> compressed = compress(original);
        std::vector<uint64_t> decompressed = decompress(compressed);
        std::cout << "Input:  ";
        for (size_t k = 0; k < original.size(); k++){
            std::cout << int(original[k]) << " ";
        }
        std::cout << std::endl << "Output: ";
        for (size_t k = 0; k < decompressed.size(); k++){
            std::cout << int(decompressed[k]) << " ";
        }

        if (decompressed.size() == original.size()){
            for (size_t k = 0; k < original.size(); k++){
                if (decompressed[k] != original[k]) passed_comp_decomp[i] = false;
            }
        } else {
            passed_comp_decomp[i] = false;
        }
        std::cout << std::endl << std::endl;
        std::cout << (passed_comp_decomp[i] ? "PASSED" : "FAILED") << std::endl << std::endl << std::endl;
        total_passed += passed_comp_decomp[i];
    }

    std::cout << "Passed " << total_passed << "/" << num_tests << std::endl << std::endl;


    std::cout << "<==========     TESTING 100k SEQUENCE COMPRESSION AND DECOMPRESSION TIME     ==========>" << std::endl << std::endl;

    int seq_len = 100000;
    std::vector<uint64_t> original;
    original.push_back(1);
    for (int j = 1; j < seq_len; j++){
        original.push_back(original[j-1] + (rand() % 10000 + 5));
    }
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    std::vector<uint8_t> compressed = compress(original);
    std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();
    std::vector<uint64_t> decompressed = decompress(compressed);
    std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();

    std::cout << "Compression time = " << std::chrono::duration_cast<std::chrono::milliseconds>(t1 - begin).count() << "[µs]" << std::endl;
    std::cout << "Decompression time = " << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() << "[µs]" << std::endl;
    std::cout << std::endl;

    std::cout << "<==========     TESTING 100k SEQUENCE COMPRESSION RATIO     ==========>" << std::endl << std::endl;

    std::cout << "Original size (bytes) = " << original.size() * 8 << std::endl;
    std::cout << "Compressed size (bytes) = " << compressed.size() << std::endl;
    std::cout << "Compression ratio = " << (float) (original.size() * 8) / compressed.size() << std::endl;

    return 0;
}
