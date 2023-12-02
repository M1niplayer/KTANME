const int const cursor_pointing[] = {0b10000000000000000000100100001001, 
0b00000000000000000000000000000000, 0b00000000000000000000000001100000, 0b00000000000000000000000011000000, 0b00000000000000000000000011111110, 0b00000000000000000000000011100000, 0b00000000000000000000000011110000, 0b00000000000000000000000011100000, 0b00000000000000000000000011110000, 0b00000000000000000000000000000000, 0b00000000000000000000000001100000, 0b00000000000000000000000011110000, 0b00000000000000000000000111111110, 0b00000000000000000000000111111111, 0b00000000000000000000000111111110, 0b00000000000000000000000111111000, 0b00000000000000000000000111110000, 0b00000000000000000000000111111000, 0b00000000000000000000000011110000, };

const int const led[] = {0b10000000000000000000100000001100, 
0b00000000000000000000011111111110, 0b00000000000000000000111111111111, 0b00000000000000000000110000000011, 0b00000000000000000000100000000001, 0b00000000000000000000100000000001, 0b00000000000000000000110000000011, 0b00000000000000000000111111111111, 0b00000000000000000000011111111110, 0b00000000000000000000111111111111, 0b00000000000000000000111111111111, 0b00000000000000000000111111111111, 0b00000000000000000000111111111111, 0b00000000000000000000111111111111, 0b00000000000000000000111111111111, 0b00000000000000000000111111111111, 0b00000000000000000000111111111111, };

const int const explode_animation6[] = {0b00000000000000000001101000100000, 
0b00000000000000101010000000000000, 0b00000000000101010101010000000000, 0b00000000101010101010101010000000, 0b00000001010101010101010101000000, 0b00000010101010101010101010100000, 0b00000101010101111101010101000000, 0b00000010101111111111101010100000, 0b00000101011111111111110101010000, 0b00001010111111111111111010100000, 0b00000101011111111111111101010000, 0b00001010111111111111111010101000, 0b00010101111111111111111101010000, 0b00001010111111111111111110101000, 0b00010101111111111111111101010000, 0b00001010111111111111111110101000, 0b00010101011111111111111101010000, 0b00001010111111111111111010100000, 0b00000101011111111111111101010000, 0b00001010101111111111111010100000, 0b00000101010111111111110101000000, 0b00000010101010111110101010100000, 0b00000101010101010101010101000000, 0b00000010101010101010101010000000, 0b00000001010101010101010100000000, 0b00000000001010101010100000000000, 0b00000000000001010100000000000000, };

const int const explode_animation9[] = {0b00000000000000000111100000100000, 
0b00000000000000000000000000100000, 0b00000000000000000000000100000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000100000, 0b00000000000001000000000000000000, 0b00000000000001000000000000000000, 0b00001000000011100000000000000010, 0b00000000000001000000000010000000, 0b00000000000000000001010000000000, 0b00000000000000001100011000000100, 0b00000000000001001000000000000000, 0b00000000000000000000000000000000, 0b00000011000000000001000000000100, 0b00000111000000001111100100000000, 0b00010111000000111111110100000010, 0b00010000100001111111111000010000, 0b00000000100001111111111001100010, 0b00000000001011111111111101110000, 0b00001000100011111111111100100000, 0b00000000001011111111111100000000, 0b10011110100111111111111101000000, 0b01111111100001111111111100000001, 0b11111111110001111111111100000000, 0b11111111110010111111110000000011, 0b11111111111000111111000100001011, 0b11111111111000000000011110100011, 0b11111111111001100101111111100111, 0b11111111111000010011111111111111, 0b11111111111111111111111111110111, 0b11111111111111111111111111111111, 0b11111111111111111111111111111011, 0b00011111111111111111111111111011, 0b01111111111111111111111111111111, 0b11111111111111111111111111111111, 0b11111111111111111111111111111111, 0b11111111111111111111111111111111, 0b11111111111111111111111111111111, 0b11111111111111111111111111111111, 0b11111111111111111111111111111111, 0b11111111111111111111111111111111, 0b11111111111111111111111111111111, 0b11111111111111111111111111111111, 0b11111111111111111111111111111111, 0b11111111111111111111111111111111, 0b11111111111111111111111111111111, 0b11111111111111111111111111111111, 0b11111111111111111111111111111111, 0b11111111111111111111111111111111, 0b11111111111111111111111111111111, 0b11111111111111111111111111111111, 0b11111111111111111111111111111111, 0b11111111111111111111111111111111, 0b11111111111111111111111111111111, 0b11111111111111111111111111111111, 0b11111111111111111111111111111111, 0b11111111111111111111111111111111, 0b11111111111111111111111111111111, 0b11111111111111111111111111111111, 0b11111111111111111111111111111111, 0b11111111111111111111111111111111, 0b11111111111111111111111111111111, 0b11111111111111111111111111111111, 0b11111111111111111111111111111111, 0b11111111111111111111111111111111, 0b11111111111111111111111111111111, 0b11111111111111111111111111111111, 0b11111111111111111111111111111111, 0b11111111111111111111111111111111, 0b11111111111111111111111111111111, 0b11111111111111111111111111111111, 0b11111111111111111111111111111111, 0b11111111111111111111111111111111, 0b11111111111111111111111111111111, 0b11111111111111111111111111111111, 0b11111111111111111111111111111111, 0b11111111111111111111111111111111, 0b11111111111111111111111111111111, 0b11111111111111111111111111111111, 0b11111111111111111111111111111111, 0b01111111111111111111111111111110, 0b00011111111111111111111111111000, 0b00000111111111111111111111111000, 0b00001011111111111111111111111110, 0b00001011111111111111101111111111, 0b00011011111111111100001111111111, 0b11110001111111111000011111111111, 0b11111001111111111000011111111111, 0b11111100111111110010011111111111, 0b11111100001111011000011111111111, 0b11111110000100000100001111111111, 0b11111110000001000100001111111111, 0b11111110000010100010000111111110, 0b11111110000100100011110001111000, 0b11111100000000111111111101010000, 0b11111110000110111111111110001010, 0b11111011000100011111111110000000, 0b11100110110100111111111111000000, 0b10000001000000111111111111010000, 0b00000111100000111111111111000000, 0b00000101010000111111111111000000, 0b00000011000001011111111110000000, 0b00000000111000011111111110000000, 0b00000000000000001111111100000000, 0b00001000010000010011110001001000, 0b10001000100010010100000000000000, 0b00000100000000000001000001000000, 0b00110000000000010010000011100000, 0b00000000000000001000000001000000, 0b00000000000000000000000000000000, 0b00000000000000000000000101000000, 0b10000010100001100000000000000000, 0b00000000000001110000000000000000, 0b00000000000000100000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000001000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000001000000000000, };

const int const explode_animation8[] = {0b00000000000000000111001000100000, 
0b00000000000000001000000000000000, 0b00000000001010000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000001000000, 0b00000000000000000000000000000000, 0b00000100000000000000000001000000, 0b00100000000000010000000000000000, 0b00001000000000010000000000000000, 0b00000000001000000000000000000001, 0b00000000010000000000100000000000, 0b00000000000000010100000000000000, 0b00000000000100000000000000001000, 0b00000000000001000000000000000000, 0b10000000000000110000000000010100, 0b00000101000010000000000000100000, 0b00001000000000000000000000000000, 0b00010000010000000000000000000000, 0b00000000000000000000000000000000, 0b01100011000010000000000000000000, 0b01110011000000000000000010000000, 0b00000010000000001000000000000000, 0b00000000000000010011100000000110, 0b00000000000000000111110000000110, 0b00000000000000000111110000100000, 0b00100000000000000111110000000000, 0b00000001100000000111100110000100, 0b00000001111110001110000110100000, 0b00011000011111011111000000000000, 0b00011000011111011111100000000000, 0b00001100011111011111110000000000, 0b00001100001110011111111100110000, 0b00110000000001111111111110110000, 0b00110000011111100011111110100001, 0b00111110111111000011111110000001, 0b00111111111111100011111101100000, 0b00001111111111110111111111100011, 0b00000011111111111111111111111111, 0b00011011111111111111111111111111, 0b00011001111111111111111111111111, 0b00011001111111111111111111111111, 0b00000001111111111111111111111000, 0b00000001111111111111111111011111, 0b10000001111111111111111111101111, 0b11000111111111111111111111100111, 0b11001111111111111111111111100111, 0b11001111111111111111111111110011, 0b11011111111111111111111111110000, 0b00011111111111111111111111110000, 0b11111111111111111111111111111000, 0b11111111111111111111111111111111, 0b11111111111111111111111111111111, 0b11111111111111111111111111111111, 0b11111111111111111111111111111111, 0b11111111111111111111111111111101, 0b11101111111111111111111111111000, 0b10001111111111111111111111110000, 0b10001111111111111111111111110000, 0b10000111111111111111111111111100, 0b00111011111111111111111111111110, 0b01111101111111111111111111111111, 0b01111100111111111111111111111111, 0b01111100011111111111111111111111, 0b01111100001111111111110011111110, 0b01111100011101111111110011111000, 0b00111000011100111111110001110111, 0b00000000001101111111110001111111, 0b00000000001111111111101111111111, 0b00110001100011111110111111111111, 0b00111111100111111111111111111111, 0b00011111000111110111111111111000, 0b00011111110111110001111111111000, 0b00011111110011111000111111111100, 0b00001110110000011000011101111100, 0b00011011110000000000011001111111, 0b00011011100000000000001101111011, 0b00000011100000011000001100110000, 0b00000000000011111000001000110000, 0b00000000000111110000011100000100, 0b01001110000111110011011101100000, 0b00001100000111110011000001100000, 0b00000000000111100000101000001000, 0b00001000000110000000010000000000, 0b00000000000000001000100000000000, 0b00000000000000000000000010000000, 0b01001100000000000000000000000000, 0b00001100000011000010000000110000, 0b00000000000111100101000000110000, 0b00000000011011100000000000000000, 0b00000000011100000000000000000000, 0b00011000001100000000000000000000, 0b00011000000000000001000000000000, 0b00000000000000000000000000000000, 0b00000001000100000010000000000000, 0b01000001100000000001010000000000, 0b00001000000000000000000000000000, 0b00010000100000000001000000000100, 0b00000000010000100000000000000000, 0b00000000000010000000000000000000, 0b00000000000010010100000000001000, 0b00000000000000001000000000000000, 0b00000000000000110000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000100000000, 0b00000000000010000000000000000000, 0b00000000000000000000110000000000, 0b01100000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000010000000000000000000, };

const int const explode_animation5[] = {0b00000000000000000001000000100000, 
0b00000000000000101000000000000000, 0b00000000000101010101000000000000, 0b00000000001010101010100000000000, 0b00000000010101010101010000000000, 0b00000000001010101010101000000000, 0b00000000010101010101010000000000, 0b00000000101010111110101000000000, 0b00000000010101111101010100000000, 0b00000000101010111110101000000000, 0b00000000010101111101010100000000, 0b00000000001010101010101000000000, 0b00000000010101010101010000000000, 0b00000000001010101010101000000000, 0b00000000000101010101010000000000, 0b00000000000010101010100000000000, 0b00000000000000010100000000000000, };

const int const black16[] = {0b10000000000000000001000000010000, 
0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000001111111111111111, 0b00000000000000001111111111111111, 0b00000000000000001111111111111111, 0b00000000000000001111111111111111, 0b00000000000000001111111111111111, 0b00000000000000001111111111111111, 0b00000000000000001111111111111111, 0b00000000000000001111111111111111, 0b00000000000000001111111111111111, 0b00000000000000001111111111111111, 0b00000000000000001111111111111111, 0b00000000000000001111111111111111, 0b00000000000000001111111111111111, 0b00000000000000001111111111111111, 0b00000000000000001111111111111111, 0b00000000000000001111111111111111, };

const int const moduletest[] = {0b00000000000000001000000000100000, 
0b11111111111111111111111111111111, 0b10000000000000000000000000000001, 0b10000000000000000000000000000001, 0b10000000111111001111111111111001, 0b10000000100001001000000000001001, 0b10000000100001001000000000001001, 0b10000000100001001000000000001001, 0b10000000100001001000000000001001, 0b10000000100001001000000000001001, 0b10000000100001001000000000001001, 0b10000000100001001000000000001001, 0b10000000100001001000000000001001, 0b10000000100001001000000000001001, 0b10000000100001001000000000001001, 0b10000000100001001000000000001001, 0b10000000100001001000000000001001, 0b10000000100001001000000000001001, 0b10000000100001001000000000001001, 0b10000000100001001000000000001001, 0b10000000100001001000000000001001, 0b10000000100001001000000000001001, 0b10000000100001001000000000001001, 0b10000000100001001000000000001001, 0b10000000100001001000000000001001, 0b10000000100001001000000000001001, 0b10000000100001001000000000001001, 0b10000000100001001000000000001001, 0b10000000100001001000000000001001, 0b10000000100001001000000000001001, 0b10000000100001001000000000001001, 0b10000000100001001000000000001001, 0b10000000100001001000000000001001, 0b10000000100001001000000000001001, 0b10011100100001001000000000001001, 0b10010100100001001000000000001001, 0b10011100111111001000000000001001, 0b10000000000000001000000000001001, 0b10000000000000001000000000001001, 0b10011111111111001000000000001001, 0b10010000000001001000000000001001, 0b10010000000001001000000000001001, 0b10010000000001001000000000001001, 0b10010000000001001000000000001001, 0b10010000000001001000000000001001, 0b10010000000001001000000000001001, 0b10010000000001001000000000001001, 0b10010000000001001000000000001001, 0b10010000000001001000000000001001, 0b10010000000001001000000000001001, 0b10010000000001001000000000001001, 0b10010000000001001000000000001001, 0b10010000000001001000000000001001, 0b10010000000001001000000000001001, 0b10010000000001001000000000001001, 0b10010000000001001000000000001001, 0b10010000000001001000000000001001, 0b10010000000001001000000000001001, 0b10010000000001001000000000001001, 0b10010000000001001000000000001001, 0b10010000000001001000000000001001, 0b10010000000001001000000000001001, 0b10010000000001001000000000001001, 0b10010000000001001000000000001001, 0b10010000000001001000000000001001, 0b10011111111111001000000000001001, 0b10000000000000001000000000001001, 0b10000000000000001000000000001001, 0b10011111111111001000000000001001, 0b10010000000001001000000000001001, 0b10010000000001001000000000001001, 0b10010000000001001000000000001001, 0b10011111111111001000000000001001, 0b10000000000000001000000000001001, 0b10000000000000001000000000001001, 0b10000000000000001000000000001001, 0b10011111111111001000000000001001, 0b10010000000001001000000000001001, 0b10010000000001001000000000001001, 0b10010000000001001000000000001001, 0b10010000000001001000000000001001, 0b10010000000001001000000000001001, 0b10010000000001001000000000001001, 0b10010000000001001000000000001001, 0b10010000000001001000000000001001, 0b10010000000001001000000000001001, 0b10010000000001001000000000001001, 0b10010000000001001000000000001001, 0b10010000000001001000000000001001, 0b10010000000001001000000000001001, 0b10010000000001001000000000001001, 0b10010000000001001000000000001001, 0b10010000000001001000000000001001, 0b10011111111111001111111111111001, 0b10000000000000000000000000000001, 0b10000000000000000000000000000001, 0b11111111111111111111111111111111, 0b11111111111111111111111111111111, 0b10000000000000000000000000000001, 0b10000000000000000000000000000001, 0b10011111111111111111111111111001, 0b10010000000000011000000000001001, 0b10010000000000011000000000001001, 0b10010000000000011000000000001001, 0b10010000000000011000000000001001, 0b10010000000000011000000000001001, 0b10010000000000011000000000001001, 0b10010000000000011000000000001001, 0b10010000000000011000000000001001, 0b10010000000000011000000000001001, 0b10010000000000011000000000001001, 0b10010000000000011000000000001001, 0b10011111111111111111111111111001, 0b10011111111111111111111111111001, 0b10010000000000000000000000001001, 0b10010000000000000000000000001001, 0b10010000000000000000000000001001, 0b10010000000000000000000000001001, 0b10010000000000000000000000001001, 0b10010000000000000000000000001001, 0b10010000000000000000000000001001, 0b10010000000000000000000000001001, 0b10010000000000000000000000001001, 0b10010000000000000000000000001001, 0b10010000000000000000000000001001, 0b10011111111111111111111111111001, 0b10000000000000000000000000000001, 0b10000000000000000000000000000001, 0b11111111111111111111111111111111, };

const int const explode_animation4[] = {0b00000000000000000000011000100000, 
0b00000000000000011000000000000000, 0b00000000000000111100000000000000, 0b00000000000001111110000000000000, 0b00000000000001111110000000000000, 0b00000000000000111100000000000000, 0b00000000000000011000000000000000, };

const int const screen[] = {0b00000000000000001000000000100000, 
0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, };

const int const menu[] = {0b00000000000000001000000000100000, 
0b11111111111111111111111111111111, 0b10000000000000000000000000000001, 0b10111111101111111011111110101001, 0b10100000101000001010000010010101, 0b10111011101111101010101010000001, 0b10100000101111011010111010000101, 0b10111111101111101011111110111101, 0b10100001101000001010000110000101, 0b10111010101111111011101010000001, 0b10100001101000001010000110111001, 0b10111111101010101011111110010101, 0b10100000101011101010110110111001, 0b10111010101111111010101010000001, 0b10100101101000001011011010111101, 0b10111111101011101011111110010101, 0b10100000101100011011110010101001, 0b10101110101111111010001110000001, 0b10110001101000001011110010000101, 0b10111111101111111011111110111101, 0b10111111101100001011111110000101, 0b10111111101011111011111110000001, 0b10111111101000001011111110000001, 0b10111111101111111011111110000001, 0b10111111101000001011111110000001, 0b10111111101111101011111110000001, 0b10111111101111011011111110000001, 0b10111111101111101011111110000001, 0b10111111101000001011111110000001, 0b10111111101111111011111110000001, 0b10000000000000000000000000000001, 0b10000000000000000000000000000001, 0b10000000000000000000000000000001, 0b10000000000000000000000000000001, 0b10000000000000000000000000000001, 0b10000000000000000000000000000001, 0b11111111111111111111111111111111, 0b10000000000000000000000000000001, 0b10111110111110000000000000111101, 0b10111110111110000000000000001001, 0b10111110111110000000000000111101, 0b10000000000000000000000000000001, 0b10001000001000001000001000111101, 0b10000000000000000000000000000001, 0b10111110111110000000000000011001, 0b10111110111110000000000000100101, 0b10111110111110000000000000110101, 0b10111110111110000000000000000001, 0b10111110111110000000000000111101, 0b10000000000000000000000000001001, 0b10111110111110000000000000111101, 0b10111110111110000000000000000001, 0b10111110111110000000000000101001, 0b10111110111110000000000000010101, 0b10111110111110000000000000000001, 0b10000000000000000000000000011001, 0b10111110111110000000000000100101, 0b10111110111110000000000000100101, 0b10111110111110000000000000000001, 0b10111110111110000000000000011001, 0b10111110111110000000000000100101, 0b10000000000000000000000000011001, 0b10001000001000001000001000000001, 0b10000000000000000000000000111101, 0b10111110111110000000000000010101, 0b10111110111110000000000000101001, 0b10111110111110000000000000000001, 0b10000000000000000000000000111101, 0b10111110111110000000000000101101, 0b10111110111110000000000000100101, 0b10111110111110000000000000000001, 0b10000000000000000000000000101001, 0b10010100010100010100010100010101, 0b10000000000000000000000000000001, 0b10111110111110000000000000000001, 0b10111110111110000000000000000001, 0b10111110111110000000000000000001, 0b10000000000000000000000000000001, 0b10111110111110000000000000000001, 0b10111110111110000000000000000001, 0b10111110111110000000000000000001, 0b10000000000000000000000000000001, 0b11111111111111111111111110000001, 0b10000000000000000000000000000001, 0b10111110111110000000000000000001, 0b10111110111110000000000000000001, 0b10111110111110000000000000000001, 0b10000000000000000000000000000001, 0b10001000001000001000001000000001, 0b10000000000000000000000000000001, 0b10111110111110000000000000000001, 0b10111110111110000000000000000001, 0b10111110111110000000000000000001, 0b10111110111110000000000000000001, 0b10111110111110000000000000000001, 0b10000000000000000000000000000001, 0b10111110111110000000000000000001, 0b10111110111110000000000000000001, 0b10111110111110000000000000000001, 0b10111110111110000000000000000001, 0b10111110111110000000000000000001, 0b10000000000000000000000000000001, 0b10111110111110000000000000000001, 0b10111110111110000000000000000001, 0b10111110111110000000000000000001, 0b10111110111110000000000000000001, 0b10111110111110000000000000000001, 0b10000000000000000000000000000001, 0b10001000001000001000001000000001, 0b10000000000000000000000000000001, 0b10111110111110000000000000000001, 0b10111110111110000000000000000001, 0b10111110111110000000000000000001, 0b10000000000000000000000000000001, 0b10111110111110000000000000000001, 0b10111110111110000000000000000001, 0b10111110111110000000000000000001, 0b10000000000000000000000000000001, 0b10010100010100010100010100000001, 0b10000000000000000000000000000001, 0b10111110111110000000000000000001, 0b10111110111110000000000000000001, 0b10111110111110000000000000000001, 0b10000000000000000000000000000001, 0b10111110111110000000000000000001, 0b10111110111110000000000000000001, 0b10111110111110000000000000000001, 0b10000000000000000000000000000001, 0b11111111111111111111111111111111, };

const int const small_cursor[] = {0b10000000000000000000100100001001, 
0b00000000000000000000000000000000, 0b00000000000000000000000011111110, 0b00000000000000000000000011111110, 0b00000000000000000000000001111110, 0b00000000000000000000000000111110, 0b00000000000000000000000001111110, 0b00000000000000000000000011101110, 0b00000000000000000000000011000110, 0b00000000000000000000000000000000, 0b00000000000000000000000111111111, 0b00000000000000000000000111111111, 0b00000000000000000000000111111111, 0b00000000000000000000000011111111, 0b00000000000000000000000001111111, 0b00000000000000000000000011111111, 0b00000000000000000000000111111111, 0b00000000000000000000000111101111, 0b00000000000000000000000111000111, };

const int const explode_animation3[] = {0b00000000000000000000001000100000, 
0b00000000000000011000000000000000, 0b00000000000000011000000000000000, };

const int const explode_animation7[] = {0b00000000000000000011011100100000, 
0b00001000000010000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000001000000000000, 0b00000000000000000100000000000000, 0b00000100000000000000000111001000, 0b00000000000011100000001111100000, 0b00000000000111110000001111100000, 0b00000001111111111100011111100000, 0b00000011111111111110000111000000, 0b00000011111111111110100000000000, 0b00000011111100111111000000000000, 0b10000101111000111110000000000000, 0b00000100000101111111010000000000, 0b00000111111111111111101010000111, 0b00001111111111111111111101001111, 0b00001111111111111111111110101111, 0b10001111111111111111111111001111, 0b10000111111111111111111111100111, 0b10000111111111111111111111111111, 0b00001111111111111111111111111111, 0b00000111111111111111111111111111, 0b00001111111111111111111111111111, 0b00111111111111111111111111110000, 0b00001111111111111111111111111000, 0b00011111111111111111111111110000, 0b00001111111111111111111111111000, 0b00011111111111111111111111110001, 0b01111111111111111111111111110000, 0b11111111111111111111111111110000, 0b11111011111111111111111111111000, 0b11111111111111111111111111111000, 0b01110011111111111111111111111000, 0b00000101111111111111111111110000, 0b00000011111111111111111110000000, 0b00000001111111111111111110100000, 0b00000001111111111111111110011101, 0b00000000111111111111111110111111, 0b00001000001111111111111110111111, 0b00000000011111010011111110111111, 0b01000000111110000101111100011101, 0b00000000111111111110100010000010, 0b00000000111110011111010010001110, 0b00000000011100011111000000011111, 0b00000000000000011111000000011111, 0b00000000000000001111000000011111, 0b00000000000000000000001000001110, 0b00000001000000000000000000000000, 0b00000000000001000000000000000000, 0b00000000000000000000010000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000001000000000000000000000, };

const int const cursor[] = {0b10000000000000000001000000010000, 
0b00000000000000001111111111111111, 0b00000000000000000110000000000001, 0b00000000000000000001100000000001, 0b00000000000000000000011000000001, 0b00000000000000000000000100000001, 0b00000000000000000000001000000001, 0b00000000000000000000010000000001, 0b00000000000000000000100000000001, 0b00000000000000000001000000010001, 0b00000000000000000010000000110001, 0b00000000000000000100000001001001, 0b00000000000000001000000010001001, 0b00000000000000001000000100000101, 0b00000000000000001000001000000011, 0b00000000000000001000010000000011, 0b00000000000000001111100000000001, 0b00000000000000001111111111111111, 0b00000000000000000111111111111111, 0b00000000000000000001111111111111, 0b00000000000000000000011111111111, 0b00000000000000000000000111111111, 0b00000000000000000000001111111111, 0b00000000000000000000011111111111, 0b00000000000000000000111111111111, 0b00000000000000000001111111111111, 0b00000000000000000011111111111111, 0b00000000000000000111111111001111, 0b00000000000000001111111110001111, 0b00000000000000001111111100000111, 0b00000000000000001111111000000011, 0b00000000000000001111110000000011, 0b00000000000000001111100000000001, };

const int const uidraft[] = {0b00000000000000001000000000100000, 
0b11111111111111111111111111111111, 0b10000000000000000000000000000001, 0b10000000000000000000000000000001, 0b10000000000000000000000000000001, 0b10000000000000000000000000000001, 0b10000000000000000000000000000001, 0b10000000000000000000000000000001, 0b10000000000000000000000000000001, 0b10000000000000000000000000000001, 0b10000000000000000000000000000001, 0b10000000000000000000000000000001, 0b10000000000000000000000000000001, 0b10000000000000000000000000000001, 0b10000000000000000000000000000001, 0b10000000000000000000000000000001, 0b10000000000000000000000000000001, 0b10000000000000000000000000000001, 0b10000000000000000000000000000001, 0b10000000000000000000000000000001, 0b10000000000000000000000000000001, 0b10000000000000000000000000000001, 0b10000000000000000000000000000001, 0b10000000000000000000000000000001, 0b10000000000000000000000000000001, 0b10000000000000000000000000000001, 0b10000000000000001000000000000001, 0b10000000000000000111111100000001, 0b10000000000000000000001100000001, 0b10000000000000000000011000000001, 0b10000000000000000000110000000001, 0b10000000000000000011100000000001, 0b10000000000000000111000000000001, 0b10000000000000000000111100000001, 0b10000000000000000000001111000001, 0b10000000000000001111111000000001, 0b10000000000000000000000000000001, 0b10000000000000000000000000000001, 0b10000000000000000000000000000001, 0b10000000000000001100000000000001, 0b10000000000000011011000000000001, 0b10000000000000010001000000000001, 0b10000000000000010001000000000001, 0b10000000000000001110000000000001, 0b10000000000000000000000000000001, 0b10000000000000001100000000000001, 0b10000000000000011100000000000001, 0b10000000000000010100000000000001, 0b10000000000000010110000000000001, 0b10000000000000011111111000000001, 0b10000000000000000000000000000001, 0b10000000000000000000000000000001, 0b10000000000000000000000000000001, 0b10000000000000000000000000000001, 0b10000000000000000110000000000001, 0b10000000000000011000000000000001, 0b10000000000000010000000000000001, 0b10000000000000010000000000000001, 0b10000000000000001111000000000001, 0b10000000000000011110000000000001, 0b10000000000000000000000000000001, 0b10000000000000000000000000000001, 0b10000000000000000000000000000001, 0b10000000000000000000011100000001, 0b10000000000000000111100000000001, 0b10000000000000011100000000000001, 0b10000000000000000000000000000001, 0b10000000000000000000000000000001, 0b10000000000000000000000000000001, 0b10000000000000000010000000000001, 0b10000000000000000111100000000001, 0b10000000000000011100110000000001, 0b10000000000000010100011000000001, 0b10000000000000110110001000000001, 0b10000000000000100011111000000001, 0b10000000000000110000110000000001, 0b10000000000000010000000000000001, 0b10000000000000000000000000000001, 0b10000000000000000000000000000001, 0b10000000000000000000000000000001, 0b10000000000000000000000000000001, 0b10000000000000000000000000000001, 0b10000000000000000000000000000001, 0b10000000000000000000000000000001, 0b10000000000000000000000000000001, 0b10000000000000000000000000000001, 0b10000000000000000000000000000001, 0b10000000000000000000000000000001, 0b10000000000000000000000000000001, 0b10000000000000000000000000000001, 0b10000000000000000000000000000001, 0b10000000000000000000000000000001, 0b10000000000000000000000000000001, 0b10000000000000000000000000000001, 0b10000000000000000000000000000001, 0b10000000000000000000000000000001, 0b11111111111111111111111111111111, 0b10000000000000000000000000000001, 0b10000000000000000000000000000001, 0b10000000000000000000000000000001, 0b10000000000000000000000000000001, 0b10000000000001111111000001110001, 0b10000000000001000001000010001001, 0b10000000000001000001000010111001, 0b10000000000001000001000010101001, 0b10000000000001000001000001110001, 0b10000000000001000001000000000001, 0b10000000000001111111000000000001, 0b10000000000000000000000000000001, 0b10000000000001111111000000000001, 0b10000000000001000001000000000001, 0b10000000000001000001000000000001, 0b10000000000001000001000000000001, 0b10000000000001000001000000000001, 0b10000000000001000001000000000001, 0b10000000000001111111000001010001, 0b10000000000000000000000000000001, 0b10000000000001111111000000000001, 0b10000000000001000001000000000001, 0b10000000000001000001000000000001, 0b10000000000001000001000000000001, 0b10000000000001000001000000000001, 0b10000000000001000001000000000001, 0b10000000000001111111000000000001, 0b10000000000000000000000000000001, 0b10000000000000000000000000000001, 0b10000000000000000000000000000001, 0b10000000000000000000000000000001, 0b11111111111111111111111111111111, };

const int const Ledpointer[] = {0b10000000000000000000010000001000, 
0b00000000000000000000000001110000, 0b00000000000000000000000011010011, 0b00000000000000000000000010101111, 0b00000000000000000000000001110000, 0b00000000000000000000000011111111, 0b00000000000000000000000011111111, 0b00000000000000000000000011111111, 0b00000000000000000000000011111111, };

const int const white32[] = {0b00000000000000000010000000100000, 
0b11111111111111111111111111111111, 0b11111111111111111111111111111111, 0b11111111111111111111111111111111, 0b11111111111111111111111111111111, 0b11111111111111111111111111111111, 0b11111111111111111111111111111111, 0b11111111111111111111111111111111, 0b11111111111111111111111111111111, 0b11111111111111111111111111111111, 0b11111111111111111111111111111111, 0b11111111111111111111111111111111, 0b11111111111111111111111111111111, 0b11111111111111111111111111111111, 0b11111111111111111111111111111111, 0b11111111111111111111111111111111, 0b11111111111111111111111111111111, 0b11111111111111111111111111111111, 0b11111111111111111111111111111111, 0b11111111111111111111111111111111, 0b11111111111111111111111111111111, 0b11111111111111111111111111111111, 0b11111111111111111111111111111111, 0b11111111111111111111111111111111, 0b11111111111111111111111111111111, 0b11111111111111111111111111111111, 0b11111111111111111111111111111111, 0b11111111111111111111111111111111, 0b11111111111111111111111111111111, 0b11111111111111111111111111111111, 0b11111111111111111111111111111111, 0b11111111111111111111111111111111, 0b11111111111111111111111111111111, };

const int const strike[] = {0b10000000000000000000001100000011, 
0b00000000000000000000000000000101, 0b00000000000000000000000000000010, 0b00000000000000000000000000000101, 0b00000000000000000000000000000111, 0b00000000000000000000000000000111, 0b00000000000000000000000000000111, };

