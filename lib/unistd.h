#ifndef UNISTD_H

int fork(void);

int exit(int state);

int wait(void);

int execv(unsigned int ptr_func);

#endif