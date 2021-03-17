# Timestamp Compression

Functions for compressing and decompressing arrays of 64-bit timestamps are implemented. </br> 
Timestamps have the property that they are monotonically increasing, so the compression function does</br>
two things:

#### Diffing

Converts the array into the array of differences, so for instance [100, 104, 106, 110, 210] becomes </br>[100, 4, 2, 4, 100].

#### Varint Compression

Then it takes that array of differences and applies the varint encoding, meaning a single 64-bit number</br>
is converted to a variable number of 7-bit numbers. Then a bit is added to differentiate the last 7 bits in</br> the series. So for example the number:

0b_1110_1110_1110_1110 is broken into 3 seven-bit numbers:


0b&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;110_1110</br>
0b&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;10_1110_1</br>
0b_11

and then encoded as three bytes: 0b1110_1110, 0b1101_1101, 0b0000_0011. Note that all bytes but the</br> last byte have the highest bit set to indicate there is more coming.

## Running tests

Navigate to the repo folder. To compile run command:

```
g++ -o test test.cpp varint_compression.cpp
```

To run tests, run command:

```
./test
```

## Compression and decompression time

For a sequence of 100k timestamps with step up to 10k running times are:
* Compression: 70 ms
* Decompression: 22 ms

## Compression ratio

For a sequence of 100k timestamps with step up to 10k compression ratio is ~4



