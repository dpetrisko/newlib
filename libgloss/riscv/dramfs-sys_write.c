/*
 * Copyright (c) 2024, Univerisity of Washington
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <errno.h>
#include <sys/types.h>
#include <unistd.h>

#include "dramfs_fdtable.h"
#include "dramfs_intf.h"

extern lfs_t lfs;
extern const struct lfs_config lfs_config;
extern int errno;

/* Write to a file.  */
ssize_t _write (int fd, const void* ptr, size_t len) {
  struct fdentry* fdentry = __get_fdentry (fd);
  if (!fdentry) {
    return -1;
  }

  // Special case for stdout/stderr
  if (fd == STDOUT_FILENO || fd == STDOUT_FILENO) {
    char* cptr = (char*)ptr;
    for (int i = 0; i < len; i++) {
      dramfs_putchar(cptr[i]);
    }
    return len;
  }

  return (ssize_t)lfs_file_write (&lfs, &fdentry->file, ptr, (lfs_size_t)len);
}
