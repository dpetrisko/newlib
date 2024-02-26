/*
 * Copyright (c) 2024, Univerisity of Washington
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <errno.h>
#include <unistd.h>
#include <sys/types.h>

#include "dramfs_fdtable.h"
#include "dramfs_intf.h"

extern lfs_t lfs;
extern const struct lfs_config lfs_config;
extern int errno;

/* Read from a file.  */
ssize_t _read (int fd, void* ptr, size_t len) {
  struct fdentry *fdentry = __get_fdentry(fd);
  if (!fdentry) {
    return -1;
  }

  // Special case for stdin
  if (fd == STDIN_FILENO) {
    uint8_t* data = (uint8_t*)ptr;

    // Return early on len == 0
    if (len == 0)
      return (ssize_t)0;

    int ch;
    // Block to read just 1 character to start
    while ((ch = dramfs_getchar ()) == -1)
      ;

    // Keep reading until new
    int i = 0;
    do {
      data[i++] = ch;
      if (i == len)
        break;
    } while ((ch = dramfs_getchar ()) != -1);

    return (ssize_t)i;
  }

  return (ssize_t)lfs_file_read(&lfs, &fdentry->file, ptr, (lfs_size_t)len);
}
