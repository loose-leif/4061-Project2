#include<stdlib.h>
#include<stdio.h>
#include <unistd.h>
#include<string.h>
#include <stdbool.h>
#include <dirent.h>

//int currentDirStorInt = 0;


void ls(char *path, bool recurse_flag) 
{
	char recursiveDirectoryStorage[200][200];
	
   	struct dirent *directoryPointer;
   	DIR *mydir;

	int currentDirStorInt = 0;
	
	int excludePeriods = 0;
	
	if(path == NULL) //gets the cwd and sets it equal to path
	{
		size_t Max_Path_Size = 1000; //Just a random number I picked
		char curDir[Max_Path_Size]; //array that will represent our current directory
		
		if(getcwd(curDir, Max_Path_Size) == NULL) //Error checking
		{
			printf("CWD Error %s\n", curDir);
			return;
		}
		else //if no error, sets our current path to path
		{
			path = curDir; 
		}
	}

  	if ((mydir = opendir(path)) == NULL) //error checking to see if the path is valid
	{
		printf("Can't open %s\n", path);
      		return;
   	}
		
	printf("In directory: %s\n", path); //formatting
	
   	while ((directoryPointer = readdir(mydir)) != NULL) 
	{
		if(excludePeriods < 2) //checking for the undesireable outputs
		{
			excludePeriods++;
		}
		//checks if we want to recurse and if it is a folder to enter into
		else if (directoryPointer->d_type == 4 && recurse_flag == true)
		{
         		sprintf(recursiveDirectoryStorage[currentDirStorInt], "%s/%s", path, directoryPointer->d_name); //appends the path into the array
         		currentDirStorInt++;
			printf(" %s ", directoryPointer->d_name);
      		}
      		else //Outputs all file names
		{
         		printf(" %s ", directoryPointer->d_name);
		}
	}
		
	printf("\n"); //formatting
		
	for (int i = 0; i < currentDirStorInt; i++)
	{
		ls(recursiveDirectoryStorage[i], true);

	}

   closedir(mydir); //closes files
	
}

int main(int argc, char *argv[]){

	//This printf was necessary to fix a weird bug. Reference emails for context. The emoji is just there for (shits && giggles)
	printf("😂");


	if(argc < 2){ // No -R flag and no path name
		ls(NULL, false);
	} else if(strcmp(argv[1], "-R") == 0) { 
		if(argc == 2) { // only -R flag
			ls(NULL, true);
		} else { // -R flag with some path name
			ls(argv[2], true);
		}
	}else { // no -R flag but path name is given
    	ls(argv[1], false);
  }
	return 0;
}
