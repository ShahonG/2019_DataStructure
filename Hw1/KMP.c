#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MaxLenGth 3000  // input string limit
#define MaxTarget 1000   // search string limit
#define MaxAnswer 100    // answer limit
typedef struct Table Table;
struct Table{
    char line[MaxLenGth];   // Prefix Table string
    int num[MaxLenGth];     // Prefix Table Number (important)
};

Table Create_PrefixTable(Table pTable , char line[]){
    pTable.num[0] = 0;
    int len = strlen(line);
    int MaxPnum = 0;
    int i = 1;
    while(i < len){                     // use while instead for because sometimes you don't need i++
        if(line[MaxPnum] == line[i]){   // Match
            MaxPnum++;
            pTable.num[i] = MaxPnum;
            i++;
        }
        else{
            if(MaxPnum > 0)
                MaxPnum = pTable.num[MaxPnum-1];    // Back to pTable.num[MaxPnum-1] because you already make sure that it is match
            else{
                pTable.num[i] = MaxPnum;            // If you are in the First of the pattern
                i++;
            }
        }
    }
    return pTable;
}

int KMP(Table pTable , char pattern[] , char article[] , int key[]){
    int art_len = strlen(article);
    int pat_len = strlen(pattern);
    int i = 0;  // for "article" length
    int j = 0;  // for "pattern" length
    int k = 0;  // for number of key
    while(i < art_len){
        if(article[i] == pattern[j]){
            i++;j++;
        }
        if(j == pat_len){
            key[k] = i - j;
            k++;
            j = pTable.num[j - 1];
        }
        else if (i < art_len && pattern[j] != article[i]){
            if(j != 0)
                j = pTable.num[j - 1];
            else
                i++;
        }
    } 
    return k;
}
void ROT13(char source[] , char pattern[]){
    int len = strlen(source);
    for(int i = 0 ; i < len ; i++){
        if(source[i] >= 'A' && source[i] <= 'Z')
            source[i] = ((source[i] - 'A') + 13) % 26 + 'A';
        else if(source[i] >= 'a' && source[i] <= 'z')
            source[i] = ((source[i] - 'a') + 13) % 26 + 'a';

    }
    for(int i = 0 ; i < 5 ; i++)
        pattern[i] = source[i];
    pattern[5] = '\0';
}


int main(){
    char ciphertext[MaxLenGth];
    char article[MaxLenGth];
    char answer_dic[MaxAnswer][200];
    char pattern[6];
    Table pTable;
    int key[10];
    int numOfkey = 0;
    char *buffer;
    buffer = (char*)malloc(sizeof(char) * MaxLenGth);

    // data in
    fgets(ciphertext , MaxLenGth , stdin);
    fgets(article , MaxLenGth , stdin);
    if(ciphertext[strlen(ciphertext) - 1] == '\n') ciphertext[strlen(ciphertext) - 1] = '\0';
    if(article[strlen(article) - 1] == '\n') article[strlen(article) - 1] = '\0';
    while(fgets(buffer , MaxLenGth , stdin)){
        if(buffer[strlen(buffer) - 1] == '\n') buffer[strlen(buffer) - 1] = '\0';
        char *pos = buffer + 2;         // shift 2 element to avoid "%c,"
        char ans_pos = buffer[0];
        strcpy(answer_dic[(int)ans_pos - (int)'A'] , pos);
    }
    // ROT13 
    ROT13(ciphertext , pattern);
    printf("%s\n" , ciphertext);
    printf("%s\n" , pattern);

    // KMP algorithm Preprocessing
    pTable = Create_PrefixTable(pTable , pattern);   // Create Prefix Table to Run KMP algorithm
    int lps = 0;

        //calculate prefix number's sum
    for(int i = 0 ; i < 5 ; i++)    
        lps += pTable.num[i];
    printf("%d\n" , lps);

        // shift prefix table (easier to write KMP algorithm's code)
    /*
    for(int i = 0 ; i < 5 ; i++)
        pTable.num[i+1] = pTable.num[i];
    pTable.num[0] = -1;
    */

        // Call KMP algorithm 
    numOfkey = KMP(pTable , pattern , article , key);
    for(int i = 0 ; i < numOfkey ; i++){
        key[i] += lps;
        printf("%d\n" , key[i]);
    }
    for(int i = 0 ; i < numOfkey ; i++)
        printf("%s " , answer_dic[key[i] - (int)'A']);
    printf("\n");
    return 0;
}
