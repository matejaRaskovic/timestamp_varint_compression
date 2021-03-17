#include <vector>
#include <cstdint>


std::vector<uint8_t> compress(std::vector<uint64_t> original);


std::vector<uint64_t> decompress(std::vector<uint8_t> compressed);

// Function converts 64 bit int into shortest possible array of 8 bit ints
std::vector<uint8_t> compress_single(uint64_t original);

// Function converts array of 8 bit ints into a single 64 bit int
uint64_t decompress_single(std::vector<uint8_t> compressed);
