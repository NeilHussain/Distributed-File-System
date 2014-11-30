#include <stdio.h>
#include <time.h>


//void PrintInstruction(FILE * outfile, Instruction * instr);
//void PrintInstructionList(FILE * outfile, Instruction * instr);

#ifndef CLIENT_SNFS_H
#define CLIENT_SNFS_H

struct fileStat{
size_t file_size;
time_t access_time;
time_t mod_time;
};

extern void setServer(char* serverIdent, int port);
extern int openFile(char *name);
extern int readFile(int fd, void *buf);
extern int writeFile(int fd, void *buf);
extern int statFile(int fd, struct fileStat *buf);
extern int closeFile(int fd);

#endif
