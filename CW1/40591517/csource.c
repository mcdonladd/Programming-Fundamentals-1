/*
The purpose of this program is to analyse a C source code file, in order to
 find the number of lines
 find the number of characters
 find the number of comments
 and the number of variables declared

 Program written  by Sam McDonald
*/

#include "csource.h"


int main(int argc, char *argv[]){

  //input file using command line argument
  FILE *input_file = fopen(argv[1], "r");

  char c;
  char line [LINE_LENGTH];
  char is_comment = '/';

  int lines = 0;
  int chars = 0;
  int comms = 0;
  int vars = 0;
  int is_function = 0;

  char *delims = " .,\n\t";
  char *token;
  char *search_comments = "//";


  //if the file is not found or is empty - end the process
  if (input_file == NULL)
  {
    printf("FILE NOT FOUND\n");
    return 0;
  }

//Find the number of lines and characters

{
    //extracted characters are stored in char c
    for(c = getc(input_file); c != EOF; c = getc(input_file))
    {
      if (c == '\n')
      {
        lines++; //add to the counter
      }
      else if (c != ' ' && c !='\n' && c != '\t')
       {
        chars++; //add to the counter
      }
    }
    //Resets the pointer to the start of the file
    fseek(input_file, 0, SEEK_SET);
}

//Find the number of comments

    while(fgets(line, LINE_LENGTH, input_file) != NULL)
    {
      token = strtok(line, delims); // gets first token
      while(token != NULL)
      {
        if(strcmp(token, search_comments)== 0) //if the token is a comment
        {
          comms++; //add to the counter
        }
       token = strtok(NULL, delims);
      }
}

//Resets the pointer to the start of the file
fseek(input_file, 0, SEEK_SET);

//Find the number of variables declared

  while(fgets(line, LINE_LENGTH, input_file) != NULL)
    {
      //if the line begins with comments, skip the line
      if((line[0] == is_comment) && (line[1] == is_comment))
      {
        continue;
      }

          token = strtok(line, delims); // get first token

          //loops through all tokens
          while (token != NULL)
          {
            if (strcmp(token, "int" ) == 0)
            {
              vars++; //add to the counter
              token = strtok(NULL, delims); //gets next token

              //find if it is a function -
              //looking for the pattern "int ___ ( "

              if (token != NULL && isalpha(token[0])) // finds if token is a word
              {
                token = strtok(NULL, " "); //gets next token
                if (strcmp(token, "(" ) == 0)
                {
                  is_function++; // if the pattern is found - add to the counter
                }
              }
            }

            //repeat the same process for double and char

            else if (strcmp(token, "double" ) == 0)
            {
              vars++;
              token = strtok(NULL, delims); //gets next token

              //looking for the pattern "double ___ ( "

              if (token != NULL && isalpha(token[0])) // finds if token is a word
              {
                token = strtok(NULL, " "); //gets next token
                if (strcmp(token, "(" ) == 0)
                {
                  is_function++; // if the pattern is found - add to the counter
                }
              }
            }

            else if (strcmp(token, "char" ) == 0)
            {
              vars++;
              token = strtok(NULL, delims); //gets next token

              //looking for the pattern "double ___ ( "

              if (token != NULL && isalpha(token[0])) // finds if token is a word
              {
                token = strtok(NULL, " "); //gets next token
                if (strcmp(token, "(" ) == 0)
                {
                  is_function++; // if the pattern is found - add to the counter
                }
              }
            }
            token = strtok(NULL, delims); //get next token
          }
        }

        fclose(input_file);

    // final number of variables
     vars = vars - is_function;

//counts the numbers of lines
printf("Total number of lines: %d\n", lines);

//count the number of characters
printf("Total number of characters: %d\n", chars);

//count the number of comments
printf("Total number of comments: %d\n", comms);

//count the number of variables
printf("Total number of variables: %d\n", vars);

return 0;
}
