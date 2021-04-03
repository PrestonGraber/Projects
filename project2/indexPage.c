#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

struct tNode {
    int count;
    struct tNode* children[26];
};

//Done
struct tNode* indexPage(const char* url);
// done 
int addWordOccurrence(const char* word, const int wordLength, struct tNode* node);
//done
void printTrieContents(struct tNode* root, char* buffer, int bufferI);
//done 
int freeTrieMemory(struct tNode* root);
//done 
int getText(const char* srcAddr, char* buffer, const int bufSize);
//done
struct tNode* initNode();

int main(int argc, char** argv){
    if (argc > 2 || argc < 2) {
        printf("Unexpected argument count; only takes one URL argument.\n");
        return 1;
    }
    printf("%s\n", argv[1]);

    //Populate root trie node from indexPage given argv[0] URL
    struct tNode* root;
    root = indexPage(argv[1]);
    if (!root) return 2;
    

    //Print tree from root
    char* printBuffer = malloc(sizeof(char) * 100);
    if (!printBuffer) return 3;
    printTrieContents(root, printBuffer, 0);
    free(printBuffer);
    
    //Free up the trie tree
    freeTrieMemory(root);

    return 0;
}

struct tNode* initNode() {

  struct tNode* node = malloc(sizeof(struct tNode));
  if (!node) return NULL;
  node->count = 0;
  for (int i = 0; i < 26; i++) node->children[i] = NULL;
  return node;

}

//Collin
int addWordOccurence(const char* word, const int wordLength, struct tNode* node){
  
    if (wordLength == 0) {

        node->count++;

    } else {

        int index = word[0] - 'a';

        if (!node->children[index]) {

            node->children[index] = initNode();
            if (!node->children[index]) return 1; // malloc failed

        } 

        addWordOccurence(&word[1], wordLength - 1, node->children[index]);
        
    }

    return 0;
}

//Preston
void printTrieContents(struct tNode* root, char* buffer, int bufferI){
    
    //no need to print if it == null so i break it from method
    if (root == NULL){
        return;
    }
    //if != 0 it will fall through and print the buffer
    if(root -> count != 0){
        buffer[bufferI] = '\0';
        printf("%s: %d\n", buffer, root -> count);
        
    }
    //For loop no greater than 26 predetermined (children)
    for(int i = 0; i < 26; i++){
        //one last check then will call itself
        if(root -> children[i]){

            buffer[bufferI] = i + 'a';

            printTrieContents(root -> children[i], buffer, bufferI + 1);
        }
    }
    
    
}
//Takes url string, calls getText with that url, and returns the root node of a trie tree with the words from that webpage
//Collin
struct tNode* indexPage(const char* url) {

    //Declare and fill buffer w/ site's characters, and put in lowercase for tokenizing
    const int BUFFER_SIZE = 300000;
    char* buffer = malloc(sizeof(char) * BUFFER_SIZE);
    if (!buffer) return NULL;
    getText(url, buffer, BUFFER_SIZE);
    for(int i = 0; i < BUFFER_SIZE; i++) { 
      buffer[i] = tolower(buffer[i]); 
      if (buffer[i] == '\0') break;
    }

    //Take all words (groups of letters between non-letters) and put them in an array of char*s
    char** wordIndex = malloc(sizeof(char*) * BUFFER_SIZE / 2); //Max number of words is half the buffer size, given that there must be at least 1 space between each
    int wordCount = 0;
    for (int i = 0; i < BUFFER_SIZE; i++) { //search through the buffer for words
        if (buffer[i] == '\0')  { break; }
        else if (buffer[i] >= 'a' && buffer[i] <= 'z') {
            int wordLength = 0;
            do {
                wordLength++;
                i++;
            } while (buffer[i] >= 'a' && buffer[i] <= 'z'); //count length of word
            wordIndex[wordCount] = malloc(sizeof(char) * (wordLength + 1)); //create a char* of that length, + 1 for termination
            if (!wordIndex[wordCount]) return NULL;
            for (int l = i - wordLength; l < i; l++) { //copy letters in buffer to that char*
                wordIndex[wordCount][wordLength - i + l] = buffer[l];
            }
            wordIndex[wordCount][wordLength] = '\0'; //terminate char* for string
            wordCount++;
        }
    }

    free(buffer);

    //Create our trie tree and populate each of the indexed words, then return
    struct tNode* root = initNode();
    if (!root) return NULL;
    for (int i = 0; i < wordCount; i++) { 
        printf("\t%s\n", wordIndex[i]);
        addWordOccurence(wordIndex[i], strlen(wordIndex[i]), root); 
        free(wordIndex[i]);
    }
    free(wordIndex);
    return root;

}
//Preston
int freeTrieMemory(struct tNode* node){

    //if the tnode does not equal null it will fall through to the for loop (26) for each character 
    if (node != NULL){
        for(int i = 0; i < 26; i++){

            if(node -> children[i] != NULL){
                freeTrieMemory(node -> children[i]);
            }
        }
        //freeing the node then setting to null so the current node doesnt follow through if statement again, but moves on to next node
        free(node);
        node = NULL;
        return 0;
    }
    return 1;
}
/* You should not need to modify this function */
int getText(const char* srcAddr, char* buffer, const int bufSize){
  FILE *pipe;
  int bytesRead;

  snprintf(buffer, bufSize, "curl -s \"%s\" | python getText.py", srcAddr);

  pipe = popen(buffer, "r");
  if(pipe == NULL){
    fprintf(stderr, "ERROR: could not open the pipe for command %s\n",
	    buffer);
    return 0;
  }

  bytesRead = fread(buffer, sizeof(char), bufSize-1, pipe);
  buffer[bytesRead] = '\0';

  pclose(pipe);

  return bytesRead;