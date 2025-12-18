#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define DEFAULT_CHILD_NUM 4
typedef struct directory* child;

typedef struct directory {
	char name[50];
	int size;
	int childNum;

	child* subDir;
} Directory;

child createNewDir(child, char[50]);
int printDir(child);
child removeDir(child, char[50]);
int removeSubDir(child);
child changeDir(child, char[50]);
child makeDirectory(child, char[50]);

int main() {
	child currentDir = NULL;
	child temp = NULL;
	child Root = NULL;
	char commandLine[50] = "";
	char dirName[50] = "";
	char currentPath[50] = "";
	char tempPath[50] = "";
	char command[10] = "";
	int isExit = 0, pathLength = 0, checkInput = 0;

	Root = (child)malloc(sizeof(Directory));
	if (Root == NULL) {
		printf("Error starting program\n");
		return -1;
	}
	temp = Root;
	Root = createNewDir(Root, "C:");
	if (Root == NULL) {
		printf("Error starting program\nShuting down\n");
		return -1;
	}
	Root->subDir[1] = Root;
	free(temp);

	currentDir = Root;
	strcat(currentPath, Root->name);
	pathLength += (int)strlen(Root->name);

	while (isExit == 0) {
		printf("\n%s>", currentPath);
		fgets(commandLine, 50, stdin);
		checkInput = sscanf(commandLine, "%9s %s\n", command, dirName);

		if (checkInput == 0) {
			printf("Something is wrong with input\n");
			continue;
		}
		for (int i = 0; i < (int)strlen(command); i++)
			command[i] = tolower(command[i]);

		if (strcmp(command, "dir") == 0) {
			printDir(currentDir);
		}
		else if (strcmp(command, "exit") == 0) {
			isExit = 1;
		}
		else if (strcmp(command, "help") == 0) {
			printf("cd - move to directory\n");
			printf("md - create directory\n");
			printf("dir - print directory\n");
			printf("rm - remove directory\n");
			printf("exit - exit program\n");
		}
		else if (strncmp(command, "cd", 2) == 0) {
			if (command[2] == '.') {
				if (command[3] == '.')
					strcpy(dirName, "..");
				else
					strcpy(dirName, ".");
			}
			temp = currentDir;
			currentDir = changeDir(currentDir, dirName);
			if (temp != currentDir) {
				if (strcmp(dirName, "..") == 0) {
					pathLength = pathLength - ((int)strlen(temp->name) + 1);
					strcpy(tempPath, currentPath);
					strncpy(currentPath, tempPath, pathLength);
					currentPath[pathLength] = '\0';
				}
				else {
					strcat(currentPath, "\\");
					strcat(currentPath, dirName);
					pathLength += (int)strlen(dirName) + 1;
				}
			}
		}
		else if (strcmp(command, "md") == 0) {
			temp = makeDirectory(currentDir, dirName);
			if (temp == NULL)
				printf("Error creating directory\n");
		}
		else if (strcmp(command, "rm") == 0) {
			removeDir(currentDir, dirName);
		}
		else
			printf("Command not recognised\n");
	}
	removeSubDir(Root);

	return 0;
}

int printDir(child p) {
	printf(".\n");
	printf("..\n");
	for (int i = 2; i < p->childNum; i++)
		printf("%s\n", p->subDir[i]->name);
	return 0;
}

child removeDir(child p, char name[50]) {
	child temp = NULL;
	int i;

	if (strcmp(name, ".") == 0 || strcmp(name, "..") == 0)
	{
		printf("Directory cannot be removed\n");
		return p;
	}
	for (i = 2; i < p->childNum; i++) {
		if (strcmp(name, p->subDir[i]->name) == 0)
		{
			temp = p->subDir[i];
			break;
		}
	}
	
	if (temp == NULL) {
		printf("Cannot find directory\n");
		return p;
	}
	removeSubDir(temp);
	for (i; i < p->childNum; i++) {
		p->subDir[i] = p->subDir[i + 1];
	}
	p->subDir[p->childNum - 1] = NULL;
	p->childNum--;
	return p;
}

int removeSubDir(child p) {
	if (p->childNum != 2)
		for (int i = 2; i < p->childNum; i++)
			removeSubDir(p->subDir[i]);
	free(p->subDir);
	free(p);
	return NULL;
}

child changeDir(child p, char name[50]) {
	int i;
	if (strcmp(name, ".") == 0)
		return p;
	if (strcmp(name, "..") == 0)
		return p->subDir[1];
	for(i =2; i<p->childNum; i++)
		if(strcmp(name, p->subDir[i]->name) == 0)
			return p->subDir[i];
	printf("Directory not found\n");
	return p;
}

child createNewDir(child p, char name[50]) {

	child q = (child)malloc(sizeof(Directory));
	if (!q) return NULL;
	q->subDir = (child*)malloc(DEFAULT_CHILD_NUM * sizeof(child));
	if (!q->subDir) return NULL;
	strcpy(q->name, name);
	q->size = 4;
	q->childNum = 2;
	q->subDir[0] = q;
	q->subDir[1] = p;
	q->subDir[2] = NULL;
	q->subDir[3] = NULL;

	return q;
}

child makeDirectory(child p, char name[50]) {
	child* tempSubDir = p->subDir;
	child temp = NULL;
	int i = 0, j = 0, k = 0;
	if (p->childNum == p->size)
	{
		p->subDir = (child*)realloc(tempSubDir, 2 * p->size * sizeof(child));
		if (p->subDir == NULL) {
			printf("Memory allocation error\n");
			return NULL;
		}
		p->size *= 2;
		for (i = p->childNum; i < p->size; i++)
			p->subDir[i] = NULL;
	}
	for (i = 2; i < p->childNum; i++) {
		if (strcmp(name, p->subDir[i]->name) == 0) {
			printf("Directory exists. Please try again\n");
			return NULL;
		}
		if (strcmp(name, p->subDir[i]->name) < 0) {
			for (j = p->childNum; j > i; j--) {
				for (k = 0; k < 50; k++)
					p->subDir[j]->name[k] = p->subDir[j - 1]->name[k];
			}
			break;
		}
	}
	p->subDir[i] = createNewDir(p, name);
	if (p->subDir[i] == NULL) {
		for (i; i < p->childNum; i++)
			p->subDir[i] = p->subDir[i + 1];
		p->subDir[i] = NULL;
		return NULL;
	}
	p->childNum++;
	return p->subDir[i];
}