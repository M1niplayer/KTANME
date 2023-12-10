#include "highscore.h"

/*Save highschore in eeprom. First three chars are the signature of the player*/
void save_highscore(uint8_t char0, uint8_t char1, uint8_t char2, uint16_t score){
    //optimized to reduce amount of page writes
    //check how many scores there are
    uint8_t bitpackedByte0 = 0;
    uint8_t bitpackedByte1 = 0;
    uint8_t bitpackedByte2 = 0;
    _pack_score(char0, char1, char2, score, &bitpackedByte0, &bitpackedByte1, &bitpackedByte2);

    uint8_t ctScores = read_single_byte(0x003f);

    uint8_t scoreList[64]; 
    int j = 0;
    //important as to not include a bunch of crap
    for (j = 0; j<64; j++){
        scoreList[j] = 0;
    }

    if (ctScores == 0) {
        //save at first place at score list and increment score count
        scoreList[0] = bitpackedByte0;
        scoreList[1] = bitpackedByte1;
        scoreList[2] = bitpackedByte2;
        scoreList[63] = 1;
        write_page(0x0000, scoreList); 
        return;
    }
    read_page(0x0000, scoreList);

    int i = 0;
    int k = 0;
    uint16_t tempScore = 0;
    uint8_t* dummyName;
    for (i = 0; i < 8; i++){
        if (i == 8) return; //only 8 scores allowed. Will not be reach but 2 hours left and I'm not changing
        bitpackedByte0 = read_single_byte(i*3);
        bitpackedByte1 = read_single_byte(i*3 + 1);
        bitpackedByte2 = read_single_byte(i*3 + 2);
        _unpack_score(&dummyName[0], &dummyName[1], &dummyName[2], &tempScore, bitpackedByte0, bitpackedByte1, bitpackedByte2);

        if (score > tempScore){
            //shift all scores down by one
            for (k = ctScores +1; k > i; k--){
                scoreList[k*3] = scoreList[(k-1)*3];
                scoreList[k*3 + 1] = scoreList[(k-1)*3 + 1];
                scoreList[k*3 + 2] = scoreList[(k-1)*3 + 2];
            }
            //insert new score
            _pack_score(char0, char1, char2, score, &bitpackedByte0, &bitpackedByte1, &bitpackedByte2);
            scoreList[i*3] = bitpackedByte0;
            scoreList[i*3 + 1] = bitpackedByte1;
            scoreList[i*3 + 2] = bitpackedByte2;
            scoreList[63] += 1;
            write_page(0x0000, scoreList);
            return;
        }
    }


}
/*Load highscore from eeprom located at address 0x0000*/
void load_highscore(uint8_t *highscores) {
    uint8_t scoreList[64]; 
    uint8_t ctScores = read_single_byte(0x003f);
    highscores[0] = ctScores;
    read_page(0x0000, scoreList);
    int i = 0;
    for (i = 0; i < 8; i++){ 
        if (i == 8) return; //only 8 scores allowed
        uint8_t bitpackedByte0 = read_single_byte(i*3);
        uint8_t bitpackedByte1 = read_single_byte(i*3 + 1);
        uint8_t bitpackedByte2 = read_single_byte(i*3 + 2);
        uint8_t char0;
        uint8_t char1;
        uint8_t char2;
        uint16_t time;
        _unpack_score(&char0, &char1, &char2, &time, bitpackedByte0, bitpackedByte1, bitpackedByte2);
        //insert scores
        highscores[(i*5)+1] = char0;
        highscores[(i*5)+2] = char1;
        highscores[(i*5)+3] = char2;
        time%=900;
        highscores[(i*5)+4] = ((time>>8)&0xFF);
        highscores[(i*5)+5] = (time&0xFF);
    }
}

/*helper to bitpack information. char mod 26 because available characters to input is from a to z. Max time is 900 (15 min)*/
void _pack_score(uint8_t char0, uint8_t char1, uint8_t char2, uint16_t time, uint8_t *packed0, uint8_t *packed1, uint8_t *packed2) {
  uint32_t pack = ((uint32_t) char0%26) + (((uint32_t) char1%26)*26) + (((uint32_t) char2%26)*26*26) + (((uint32_t) time%900)*26*26*26);
  *packed0 = pack&0xFF;
  *packed1 = (pack>>8)&0xFF;
  *packed2 = (pack>>16)&0xFF;
}

/*Helper to unpack score. 256 because it's size of uint8*/
void _unpack_score(uint8_t *char0, uint8_t *char1, uint8_t *char2, uint16_t *time, uint8_t packed0, uint8_t packed1, uint8_t packed2) {
  uint32_t pack = ((uint32_t) packed0) + (((uint32_t) packed1) * 256) + (((uint32_t) packed2) *256*256);
  *char0 = pack%26;
  pack /= 26;
  *char1 = pack%26;
  pack /= 26;
  *char2 = pack%26;
  pack /= 26;
  *time = pack%900;
}
