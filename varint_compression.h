#include <vector>
#include <cstdint>


std::vector<uint8_t> compress(std::vector<uint64_t> original);
std::vector<uint64_t> decompress(std::vector<uint8_t> compressed);
std::vector<uint8_t> compress_single(uint64_t original);
uint64_t decompress_single(std::vector<uint8_t> compressed);
