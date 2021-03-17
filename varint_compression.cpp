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

}
