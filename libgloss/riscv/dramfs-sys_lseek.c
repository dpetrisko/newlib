/*
 * Copyright (c) 2024, Univerisity of Washington
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <errno.h>
#include <sys/types.h>

#include "dramfs_fdtable.h"
#include "dramfs_fs.h"

extern lfs_t lfs;
extern const struct lfs_config lfs_config;
extern int errno;

/* Set position in a file.  */
off_t _lseek (int fd, off_t ptr, int dir) {
  struct fdentry *fdentry = __get_fdentry(fd);
  if (!fdentry) {
    return -1;
  }

  if (fd < LFSBASE_FILENO) {
    errno = EBADF;
    return -1;
  }

  return lfs_file_seek (&dramfs_fs, &fdentry->file, ptr, dir);
}
