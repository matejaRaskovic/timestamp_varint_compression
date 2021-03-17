#include "varint_compression.h"

#include <iostream>
#include <algorithm>

#define MAX_INTS_FROM_ORIGINAL 10

// The function is used to convert numbers greater than 0 but it will work for 0 too
std::vector<uint8_t> compress_single(uint64_t original){
    uint64_t zeros_mask = 0;
    uint64_t ones_mask = ~zeros_mask;
    uint64_t positional_mask = ~(ones_mask << 7);  // only the last 7 bits are ones
    std::vector<uint8_t> varint_compressed_reverse;

    for (int i = 0; i < MAX_INTS_FROM_ORIGINAL; i++){
        if (!i || original & (ones_mask << (7*i))){
            uint8_t to_add_int = (original >> (7*i) & positional_mask) | ((i!=0) << 7);
            varint_compressed_reverse.push_back(to_add_int);
        } else {
            break;
        }
    }

    // Using push_back and then reverting vector
    std::vector<uint8_t> varint_compressed(varint_compressed_reverse.size());
    std::reverse_copy(varint_compressed_reverse.begin(), varint_compressed_reverse.end(), varint_compressed.begin());

    return varint_compressed;
}


std::vector<uint8_t> compress(std::vector<uint64_t> original){
    std::vector<uint8_t> varint_compressed;
    uint64_t prev = 0;
    for (size_t i = 0; i < original.size(); i++){
        if (i) {
            prev = original[i-1];
            if (prev >= original[i]){
                // original vector is not monotonically increasing an exception should be raised or similar
            }
        }
        std::vector<uint8_t> single_varint_compressed = compress_single(original[i] - prev);
        for (size_t j = 0; j < single_varint_compressed.size(); j++){
            varint_compressed.push_back(single_varint_compressed[j]);
        }
    }

    return varint_compressed;
}


uint64_t decompress_single(std::vector<uint8_t> compressed){
    uint64_t decompressed = 0;
    size_t num_ints = compressed.size();
    for (size_t i = 0; i < num_ints; i++){
        uint8_t bits_to_copy = compressed[i] & ~(1 << 7);
        decompressed = decompressed | (bits_to_copy << 7*(num_ints-i-1));
    }

    return decompressed;
}


std::vector<uint64_t> decompress(std::vector<uint8_t> compressed){
    std::vector<uint64_t> decompressed;
    std::vector<uint8_t> single_to_decompress;
    for (size_t i = 0; i < compressed.size(); i++){
        uint8_t current = compressed[i];
        single_to_decompress.push_back(current);
        if (current & (1 << 7)){
            continue;
        } else {
            uint64_t to_add = decompress_single(single_to_decompress);
            decompressed.push_back(to_add);
            if (decompressed.size() > 1){
                decompressed[decompressed.size()-1] += decompressed[decompressed.size()-2];
            }
            single_to_decompress.clear();
        }
    }

    return decompressed;
}
