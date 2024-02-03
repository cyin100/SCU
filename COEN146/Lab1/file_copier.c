//
//  Created by Behnam Dezfouli
//  CSEN, Santa Clara University
//
//
// This program offers two options to the user:
// -- Option 1: enables the user to copy a file to another file.
// The user needs to enter the name of the source and destination files.
// -- Option 2: enables the user to measure the performance of file copy.
// In addition to the name of source and destination files, the user needs to enter the maximum source file size as well as the step size to increment the source file size.
//
//
// double copier(FILE *s_file, FILE *d_file)
// Precondition: s_file is a pointer to a file opened in read mode, d_file is a file pointer opened in write mode
// Postcondition: Copies the contents of the file pointed to by s_file to the file pointed to by d_file
//

#include <stdio.h>
#include <stdlib.h> // For exit()
#include <fcntl.h>
#include <time.h>

#define SIZE 1
#define DUM_CHAR 'A'

double copyFunctionCall(FILE *sourceFile, FILE *destFile){

    // Read and write from buffer until end of file, then close files
    char buffer[100];
    int size;
    while((size = fread(buffer, sizeof(char), 100, sourceFile))>0){
        fwrite(buffer, sizeof(char), size, destFile);
    }
    fclose(sourceFile);
    fclose(destFile);  
}

double copySystemCall(int sourceFile, int destFile){

    // Read and write from buffer until end of file
    char buffer[100];
    int size;
    while((size = read(sourceFile, buffer, 100))>0){
        write(destFile, buffer, size);
    }
}

int main(){

    // Ask user for which option 
    int option;
    printf("1: File Copy\n");
    printf("2: File Copy with Time Performance\n");
    scanf("%d", &option);
    
    // Ask user for source and destination file names
    char sourceFileName[100], destFileName[100], destFileName2[100];
    scanf("%s", sourceFileName);
    scanf("%s", destFileName);
    
    if ( option == 1 ) // File copy
    {
        // Use fopen to open files for read/write, then copy with function call  
        FILE *sourceFile, *destFile;
        sourceFile = fopen(sourceFileName, "r");
        destFile = fopen(destFileName, "w");
        copyFunctionCall(sourceFile, destFile);
        
        // Use open to open files for read/write, then copy with system call
        scanf("%s", destFileName2);
        int sourceFile_, destFile2;
        sourceFile_ = open(sourceFileName, O_RDONLY);
        destFile2 = open(destFileName2, O_WRONLY);
        copySystemCall(sourceFile_, destFile2);
    }
   
    else if ( option == 2 ) // File copy with performance measurement
    {
        // Ask user for maximum file size and step sixe
        int maximum_file_size;
        int step_size;
        int current_size = 0;
        scanf("%d", &maximum_file_size);
        scanf("%d", &step_size);

        while(current_size < maximum_file_size )
        {
            // Initialize clock variables for time tracking
            clock_t start, end;
            double cpu_time_used;
            current_size = current_size + step_size;

            // Use fopen to open files and start clock
            FILE *sourceFile, *destFile;
            sourceFile = fopen(sourceFileName, "w");
            destFile = fopen(destFileName, "w");
            start = clock();

            // Populate source file with current_size characters
            int i;
            for(i=0; i<current_size; i++){
                fputc(DUM_CHAR, sourceFile);
            }
            fclose(sourceFile);

            // Open source file to read and copy function call
            sourceFile = fopen(sourceFileName, "r");
            copyFunctionCall(sourceFile, destFile);

            // Report time to copy
            end = clock();
            cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
            printf("File Size: %d; Time to copy: %f\n", current_size, cpu_time_used);
        }
    }
   
    else
    {
        printf("Invalid option!");
        return 0;
    }
   
    return 0;
}