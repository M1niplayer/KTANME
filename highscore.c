#include "highscore.h"

void save_highscore(uint8_t char0, uint8_t char1, uint8_t char2, uint8_t score){
    PORTE =0;
    //optimized to reduce amount of page writes
    //check how many scores there are
    uint8_t bitpackedByte0 = 0;
    uint8_t bitpackedByte1 = 0;
    uint8_t bitpackedByte2 = 0;
    _pack_score(char0, char1, char2, score, &bitpackedByte0, &bitpackedByte1, &bitpackedByte2);


    uint8_t ctScores = read_single_byte(0x003f);

    uint8_t scoreList[64]; 
    PORTE|=1;
    if (ctScores == 0) {
        //save at first place at score list and increment score count
        //bit packing fun time
        scoreList[0] = bitpackedByte0;
        scoreList[1] = bitpackedByte1;
        scoreList[2] = bitpackedByte2;
        scoreList[63] = 1;
        write_page(0x0000, scoreList); //will include a bunch of crap
        return;
    }
    read_page(0x0000, scoreList);

    int i = 0;
    uint16_t tempScore = 0;
    uint8_t* dummyName;
    for (i = 0; i < ctScores; i++){
        if (i == 10) return; //only 10 scores allowed
        bitpackedByte0 = read_single_byte(i*3);
        bitpackedByte1 = read_single_byte(i*3 + 1);
        bitpackedByte2 = read_single_byte(i*3 + 2);
        _unpack_score(&dummyName[0], &dummyName[1], &dummyName[2], &tempScore, bitpackedByte0, bitpackedByte1, bitpackedByte2);
        PORTE|=8;
        if (score > tempScore){
            //shift all scores down by one
            int j = 0;
            for (j = ctScores; j > i; j--){
                scoreList[j*3] = scoreList[(j-1)*3];
                scoreList[j*3 + 1] = scoreList[(j-1)*3 + 1];
                scoreList[j*3 + 2] = scoreList[(j-1)*3 + 2];
            }
            //insert new score
            _pack_score(char0, char1, char2, score, &bitpackedByte0, &bitpackedByte1, &bitpackedByte2);
            scoreList[i*3] = bitpackedByte0;
            scoreList[i*3 + 1] = bitpackedByte1;
            scoreList[i*3 + 2] = bitpackedByte2;
            scoreList[63] += 1;
            write_page(0x0000, scoreList);
            PORTE|=16;
            return;
        }
    }


}
void load_highscore(uint8_t *highscores) {
    uint8_t scoreList[64]; 
    uint8_t ctScores = read_single_byte(0x003f);
    highscores[0] = ctScores;
    read_page(0x0000, scoreList);
    int i = 0;
    for (i = 0; i < ctScores; i++){
        if (i == 8) return; //only 8 scores allowed
        uint8_t bitpackedByte0 = read_single_byte(i*3);
        uint8_t bitpackedByte1 = read_single_byte(i*3 + 1);
        uint8_t bitpackedByte2 = read_single_byte(i*3 + 2);
        uint8_t char0;
        uint8_t char1;
        uint8_t char2;
        uint16_t time;
        _unpack_score(&char0, &char1, &char2, &time, bitpackedByte0, bitpackedByte1, bitpackedByte2);
        highscores[(i*5)+1] = char0;
        highscores[(i*5)+2] = char1;
        highscores[(i*5)+3] = char2;
        highscores[(i*5)+4] = (time>>8);
        highscores[(i*5)+5] = (time&0xFF);
    }
}

void _pack_score(uint8_t char0, uint8_t char1, uint8_t char2, uint16_t time, uint8_t *packed0, uint8_t *packed1, uint8_t *packed2) {
  int pack = (char0%26) + ((char1%26)*26) + ((char2%26)*26*26) + ((time%900)*26*26*26);
  *packed0 = pack&0xFF;
  *packed1 = (pack>>8)&0xFF;
  *packed2 = (pack>>16)&0xFF;
}

void _unpack_score(uint8_t *char0, uint8_t *char1, uint8_t *char2, uint16_t *time, uint8_t packed0, uint8_t packed1, uint8_t packed2) {
  int pack = packed0 + (packed1*256) + (packed2*256*256);
  *char0 = pack%26;
  pack /= 26;
  *char1 = pack%26;
  pack /= 26;
  *char2 = pack%26;
  pack /= 26;
  *time = pack%900;
}
