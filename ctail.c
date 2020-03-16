/*  Imtiaz Bin Mujib
    29383412
    Start:27/08/2019
    Last Modified:30/08/2019
    Description: This program can read the last characters of a file. Depending on the given
    command arguments the amount of characters printed can be changed and also this program can
    print lines instead of printing characters.
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#

int opFile,n,L,filToOpen;
char *str;
int task1 ();
int task2(char *argv[],int argc);
int task3(char *argv[],int argc);
int readWrite(openedFile,buffer,lines);
int parseArg(char *argv[],int argc);

void main(int argc, char *argv []){
    n=200;                          //Default n value
    filToOpen="logfile.txt";        //Default file
    L=10;                           //Default Line value
    parseArg(argv,argc);
    }

int parseArg(char *argv[],int argc){
//This function parses through the command arguments to find which function needs to be called
    int i;
    if (argc==1){
// SInce no arguments are given it defauits to task 1
        task1();
    }
    else{
        for(i=0;i<argc;i++){
// for loop to check through all the arguments to make sure the correct function is called
            if(0 == strcmp(argv[i], "-L")){
            //Checking if L argument is given
                task3(argv,argc);
            }
            if(0 == strcmp(argv[i], "-n")) {
            //Checking if n argument is given
                task2(argv,argc);
            }
        }
    }
    if(argc==2 && (0 != strcmp(argv[1],"-L"))){
        // If only the filename in provided
        task2(argv,argc);
    }

}
int readWrite(openedFile,buffer,lines){

    lseek(openedFile,-lines, SEEK_END);                 //Set file offset lines bytes from file end
    read(openedFile, buffer, lines);                    //Store lines bytes from opFile into buffer
    write (1, buffer, lines);                           //Write buffer to Terminal
}

int chckFileExistence(openedfile){
    int openFile;
    if ((openFile= open(openedfile, O_RDONLY))<0){
    //If file doesnt exist write to Standard Error and exit
		write (2, "File doesn't Exist.\n", 25);
		exit(1);
	}
	else{
        return openFile;
	}

}
int task1 (){
/*This function is called when none of the optional arguments are provided. It prints the last 200 chars from logfile */
    str=(char *) malloc(n);                     //Buffer to store read info
    opFile=chckFileExistence(filToOpen);
    readWrite(opFile,str,n);
    close(opFile);                              //CLose opFile to free up resources
    free(str);                                  //Free allocated memory
    exit(0);                                    //Exit with code 0
}

int task2(char *argv[],int argc){
/*This function is called the optional argument n is called or the file path is specified. If just n is given this file
  prints the last n characters of logfile and if only the file is given it prints the last 200 chars from the file.
  But if both n and file path is provided then this function writes the last n characters from the given file.
*/
    if(0 == strcmp(argv[1], "-n")){
    //If only n is provided
        n=atoi(argv[2]);
    }
    else if (argc>2){
    //If both n and file path are provided
        n=atoi(argv[3]);
        filToOpen=argv[1];
    }
    else{
    //If only file path is provided
        filToOpen=argv[1];
    }
    str=(char *) malloc(n);                     //Buffer to store read info
    opFile=chckFileExistence(filToOpen);
    readWrite(opFile,str,n);
    close(opFile);                              //CLose opFile to free up resources
    free(str);                                  //Free allocated memory
    exit(0);                                    //Exit with code 0
}
int task3(char *argv[],int argc){
/*This function is called the optional argument L is called .If L is called instead of printing characters the program prints lines. If only
  L is provided it prints last 10 lines from logfile. If L and filepath is provided it prints last 10 lines from given file. And if n argument is
  also added then it prints the amount of lines specified by n.
*/
    int buff=1,chck,xtraByte;                                 //Buffer to store characters
    if (argc==3){
    //if the only inputs are L and filepath
        filToOpen=argv[1];
    }
    if(argc>3){
    //If other inputs are provided
        if (0 == strcmp(argv[1], "-L")){
        //If the n cahrs are input
            L=atoi(argv[3]);
        }
        else{
        //if all the inputs are provided
            filToOpen=argv[1];
            L=atoi(argv[4]);
        }
    }
    str=(char *) malloc(buff);              //Str to store info
    opFile=chckFileExistence(filToOpen);
	while(chck!=L+1){
    //Checks the amount of lines until the Input lines are reached or the start of the file is found
        lseek(opFile,-buff, SEEK_END);
        read(opFile, str,1);
        if (0 == strcmp(str, "\n")){
        //chck increases if a new line is found
                chck++;
            }
        buff++;
        if(lseek(opFile,-buff, SEEK_END)==0){
        //If the file offset reaches the start of the file this stops the loop
            xtraByte=1;                     //Xtrabyte to insure that more than the specified chars are not printed
            break;
        }
	}
	if(xtraByte!=1){
    //To get rid of extra char from the buff
        buff--;
	}
    readWrite(opFile,str,buff);
    close(opFile);                                  //CLose opFile to free up resources
    free(str);                                      //Free allocated memory
    exit(0);                                        //Exit with code 0
}
