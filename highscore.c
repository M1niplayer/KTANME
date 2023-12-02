#include "highscore.h"

void save_highscore(char *name, uint8_t score){
    //optimized to reduce amount of page writes
    //check how many scores there are
    uint8_t bitpackedByte = 0;
    uint8_t bitpackedByte1 = 0;
    uint8_t bitpackedByte2 = 0;
    _pack_score(name[0], name[1], name[2], score, &bitpackedByte, &bitpackedByte1, &bitpackedByte2);

    uint8_t ctScores = read_single_byte(0x0000003f);
    uint8_t scoreList[64]; 
    if (ctScores == 0) {
        //save at first place at score list and increment score count
        //bit packing fun time
        scoreList[0] = bitpackedByte;
        scoreList[1] = bitpackedByte1;
        scoreList[2] = bitpackedByte2;
        scoreList[63] = 1;
        //write_page(0x00000000, scoreList); //will include a bunch of crap
        return;
    }

    int i = 0;
    uint8_t tempScore = 0;
    for (i = 0; i < ctScores; i++){
        read_page(0x00000000, scoreList);
        //unpack scoreList which somehow means you have to get the time
        //tempscore = readsinglebyte(0x00000000 + offset) & whaterver;
        
        //if (score > tempscore) break;
    }
    //write_page(0x00000000, scoreList);

}
void load_highscore(highscore_t *highscores){
    uint8_t counter = 0;
    //read_page(0x0000003f, counter)
    //some logic to return highscores I suppose
}
void _pack_score(uint8_t c0, uint8_t c1, uint8_t c2, uint16_t time, uint8_t *packed0, uint8_t *packed1, uint8_t *packed2) {
  int pack = (c0%26) + ((c1%26)*26) + ((c2%26)*26*26) + ((time%900)*26*26*26);
  *packed0 = pack&0xFF;
  *packed1 = (pack>>8)&0xFF;
  *packed2 = (pack>>16)&0xFF;
}

void _unpack_score(uint8_t *c0, uint8_t *c1, uint8_t *c2, uint16_t *time, uint8_t packed0, uint8_t packed1, uint8_t packed2) {
  int pack = packed0 + (packed1*256) + (packed2*256*256);
  *c0 = pack%26;
  pack /= 26;
  *c1 = pack%26;
  pack /= 26;
  *c2 = pack%26;
  pack /= 26;
  *time = pack%900;
}