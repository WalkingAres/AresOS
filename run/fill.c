#include <stdio.h>

int main(void) {
    FILE *fp;
    fp = fopen("/Users/Ares/magic/AresOS/run/diskb.img","wb");
    int c=2;
    int num=0;
    for(int i=0; i < 2880*512; i++) {
        if( i%512 == 0) {
            fwrite(&num,1,1,fp);
            num++;
        }
        else {
            fwrite(&c,1,1,fp);
        }
    }
    fclose(fp);
    return 0;
}