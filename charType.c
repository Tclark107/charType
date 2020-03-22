//-----------------------------------------------------------------------------
// charType.c
// This is a small exercise in proper handling of memory allocation and freeing
// heap space.  The algorithm seems a little hacky, but it works. It still runs
// in N time.
// Tristan Clark
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<assert.h>

#define MAX_STRING_LENGTH 100

// global variables
int alphacount = 0;
int numcount = 0;
int punccount = 0;
int spacecount = 0;

// function prototype 
void extract_chars(char* s, char* a, char* d, char* p, char* w);

// function main which takes command line arguments 
int main(int argc, char* argv[]){
   FILE* in;         // handle for input file                  
   FILE* out;        // handle for output file                 
   char* line;       // string holding input line              
   char* alpha;      // string holding all alphabet chars
   char* num;        // string holding all numeric chars
   char* punc;       // string holding all punctuation chars
   char* space;      // string holding all whitespace chars
   int linecount = 1; 

   // check command line for correct number of arguments 
   if( argc != 3 ){
      printf("Usage: %s input-file output-file\n", argv[0]);
      exit(EXIT_FAILURE);
   }

   // open input file for reading 
   if( (in=fopen(argv[1], "r"))==NULL ){
      printf("Unable to read from file %s\n", argv[1]);
      exit(EXIT_FAILURE);
   }

   // open output file for writing 
   if( (out=fopen(argv[2], "w"))==NULL ){
      printf("Unable to write to file %s\n", argv[2]);
      exit(EXIT_FAILURE);
   }

   // allocate strings line and alpha_num on the heap 
   line = calloc(MAX_STRING_LENGTH+1, sizeof(char) );
   alpha = calloc(MAX_STRING_LENGTH+1, sizeof(char) );
   num = calloc(MAX_STRING_LENGTH+1, sizeof(char) );
   punc = calloc(MAX_STRING_LENGTH+1, sizeof(char) );
   space = calloc(MAX_STRING_LENGTH+1, sizeof(char) );
   assert( line!=NULL && alpha!=NULL && num!=NULL &&
           punc!=NULL && space!=NULL );

   // read each line in input file, extract alpha-numeric characters 
   while( fgets(line, MAX_STRING_LENGTH, in) != NULL ){
      fprintf(out, "line %d contains: \n", linecount);
      extract_chars(line, alpha, num, punc, space);
      fprintf(out, "%d alphabetic characters: %s\n", alphacount, alpha);
      fprintf(out, "%d numeric characters: %s\n", numcount, num);
      fprintf(out, "%d punctiation characters: %s\n", punccount, punc);
      fprintf(out, "%d whitespace characters: %s\n", spacecount, space);
      linecount++;
      alphacount = 0;
      numcount = 0;
      spacecount = 0;
      punccount = 0;
   }

   // free heap memory 
   free(line);
   free(alpha);
   free(num);
   free(punc);
   free(space);

   // close input and output files 
   fclose(in);
   fclose(out);

   return EXIT_SUCCESS;
}

// function definition 
void extract_chars(char* s, char* a, char* d, char* p, char* w){
   int i=0, alphaiter=0, numiter=0, punciter=0, spaceiter=0;
   while(s[i]!='\0' && i<MAX_STRING_LENGTH){
      if( isalpha( (int) s[i]) ) {
         a[alphaiter++] = s[i];
         alphacount++;
      } else if (isdigit((int)s[i])) {
         d[numiter++] = s[i];
         numcount++;
      } else if (ispunct((int)s[i])) {
         p[punciter++] = s[i];
         punccount++;
      } else if (isspace((int)s[i])) {
         w[spaceiter++] = s[i];
         spacecount++;
      }
      i++;
   }
   a[alphaiter] = '\0';
   d[numiter] = '\0';
   p[punciter] = '\0';
   w[spaceiter] = '\0';
}
