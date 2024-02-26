/*
 * Copyright (c) 2024, Univerisity of Washington
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

#include "dramfs_fdtable.h"
#include "dramfs_intf.h"

extern lfs_t lfs;
extern const struct lfs_config lfs_config;

extern int _open (const char*, int, ...);

// Initialize fdtable with stdin/stdout/stderr and mounted filesystem
void __attribute__ ((constructor))
init_dramfs_fd (void) {
  for (int i = 0; i < RISCV_MAX_OPEN_FILES; i++) {
    fdtable[i].active = false;
  }

  // Stub files to pass NULL checks
  fdtable[STDIN_FILENO].active = true;
  fdtable[STDOUT_FILENO].active = true;
  fdtable[STDERR_FILENO].active = true;

  // Mount the files, if any
  if (lfs_mount(&lfs, &lfs_config) < 0) {
      return;
  }
}

// Add an entry to fdtable
int
__add_fdentry (lfs_file_t file) {
  for (int fd = LFSBASE_FILENO; fd < RISCV_MAX_OPEN_FILES; fd++) {
    if (!fdtable[fd].active) {
      fdtable[fd].active = true;
      fdtable[fd].file = file;
      return fd;
    }
  }

  errno = ENFILE;
  return -1;
}

// Get an fdentry from the table
struct fdentry *
__get_fdentry (int fd)
{
    if (fd < 0 || fd >= RISCV_MAX_OPEN_FILES || !fdtable[fd].active)
    {
        errno = EBADF;
        return NULL;
    }
    return &fdtable[fd];
}

// Remove an fdentry from the table
void
__remove_fdentry (int fd)
{
    fdtable[fd].active = false;
}

