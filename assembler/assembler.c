#include<stdio.h>
#include<stdlib.h>
#include<regex.h>
#include<string.h>

const char *file_name; // name of the assembly file, provided through command line args.

// this is an assembler file, will take input.txt in assembly format, and will generate an output.txt in machine code format.
int main(int argc, char const *argv[])
{
    if( argc == 2 ) {
        printf("Selected file is:  %s\n", argv[1]);
        (file_name) = argv[1];
    }     
        
   else {
        printf("Exactly one argument is expected.\n");
        return 1;
    }
      
    FILE *fp;
    char *instr = NULL; // hold the instruction of the current line
    fp = fopen(file_name, "r");
    size_t len = 0;
    ssize_t read;
    char *delimiter = " "; // to clear comments
    char *delimiter_commenbts = "//";
    char **instr_list; // holds instructions seperately for better control.

    if (fp == NULL)
        return 1;
    
    // instructions are retrieved here
    printf("Contents: \n");
    while ((read = getline(&instr, &len, fp)) != -1) {
        //printf("Retrieved line of length %zu:\n", read);
        printf("%s", instr);

        int count = 0;
        char *token = strtok(instr, delimiter_commenbts); // removes comments from instruction.

        token = strtok(instr, delimiter); // retokenizes the string.
        while (token != NULL)
        {
            instr_list[count] = (char *)token;
            printf("Token no: %d, str: %s\n", count, token);
            token = strtok(NULL, delimiter);
            
            count++;
        }
        instr_list[count] = NULL;

        
    }
    size_t i = 0;
    printf("Commencing str test: \n");
    while (instr_list[i] != NULL)
    {
        
        printf("%ld: %s\n", i+1, instr_list[i]);
        i++;
    }
    

    printf("\n");

    fclose(fp);
    if (instr)
        free(instr);

    return 0;
}
