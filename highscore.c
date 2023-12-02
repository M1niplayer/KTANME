#include "highscore.h"

void save_highscore(char *name, uint8_t score){
    //optimized to reduce amount of page writes
    //check how many scores there are
    uint8_t ctScores = read_single_byte(0x0000003f);
    uint8_t scoreList[64]; 
    if (ctScores == 0) {
        //save at first place at score list and increment score count
        //bit packing fun time
        //scoreList[0] = bitpackedByte 1
        //scoreList[1] = bitpackedByte 2
        //scoreList[2] = bitpackedByte 3
        //scoreList[63] = 1;
        //write_page(0x00000000, scoreList); //will include a bunch of crap
        return;
    }
    int i = 0;
    uint8_t tempScore = 0;
    for (i = 0; i < ctScores; i++){
        //read_page(0x00000000, scoreList);
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