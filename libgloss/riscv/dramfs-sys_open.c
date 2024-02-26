/*
 * Copyright (c) 2024, Univerisity of Washington
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#include "dramfs_fdtable.h"
#include "dramfs_intf.h"

extern lfs_t lfs;
extern const struct lfs_config lfs_config;
extern int errno;

/* Open a file.  */
int _open (const char* name, int flags, int mode) {
  int lfs_flags = 0;

  // File open flags mapping
  lfs_flags |= (flags & O_RDONLY) ? LFS_O_RDONLY : 0;
  lfs_flags |= (flags & O_WRONLY) ? LFS_O_WRONLY : 0;
  lfs_flags |= (flags & O_RDWR) ? LFS_O_RDWR : 0;
  lfs_flags |= (flags & O_APPEND) ? LFS_O_APPEND : 0;
  lfs_flags |= (flags & O_CREAT) ? LFS_O_CREAT : 0;
  lfs_flags |= (flags & O_TRUNC) ? LFS_O_TRUNC : 0;
  lfs_flags |= (flags & O_EXCL) ? LFS_O_EXCL : 0;

  int rem_flags = flags;
  rem_flags &= ~O_RDONLY;
  rem_flags &= ~O_WRONLY;
  rem_flags &= ~O_RDWR;
  rem_flags &= ~O_APPEND;
  rem_flags &= ~O_CREAT;
  rem_flags &= ~O_TRUNC;
  rem_flags &= ~O_EXCL;

  // Unsupported flag set;
  if (rem_flags) {
    errno = EINVAL;
    return -1;
  }

  if (!strcmp("stdin", name)) {
    return STDIN_FILENO;
  } else if (!strcmp("stdout", name)) {
    return STDOUT_FILENO;
  } else if (!strcmp("stderr", name)) {
    return STDERR_FILENO;
  }

  int ret;
  lfs_file_t lfs_file;
  if ((ret = lfs_file_open(&lfs, &lfs_file, name, lfs_flags)) < 0) {
    errno = ret;
    return -1;
  }

  return __add_fdentry(lfs_file);
}
