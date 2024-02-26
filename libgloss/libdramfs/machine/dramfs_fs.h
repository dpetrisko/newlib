#ifndef DRAMFS_FS_H
#define DRAMFS_FS_H

#include <lfs.h>

// Toplevel filesystem struct
extern lfs_t dramfs_fs;

// File system configuration structure
// Initalized externally and can be generated by dramfs_mklfs
extern struct lfs_config dramfs_fs_cfg;

// Array with initial LFS image
// Initialized externally and can be generated by dramfs_mklfs
extern uint8_t lfs_mem[];

// Exit routine: exit() calls this routine
// Definition provided externally by user
extern void dramfs_exit(int);

// Utility to print a char to console
// Definition provided externally by user
extern void dramfs_sendchar(char);

// Utility to get a char from console
// Definition provided externally by user
extern int dramfs_getchar(void);

// LFS init routine: Should be called before calling main
int dramfs_fs_init(void) __attribute__((weak));

#endif // DRAMFS_FS_H
