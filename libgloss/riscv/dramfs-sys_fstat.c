/*
 * Copyright (c) 2024, Univerisity of Washington
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <errno.h>
#include <sys/stat.h>

#include "dramfs_fdtable.h"
#include "dramfs_fs.h"

extern lfs_t lfs;
extern const struct lfs_config lfs_config;
extern int errno;

int _fstat (int fd, struct stat* st) {
  struct fdentry *fdentry = __get_fdentry(fd);
  if (!fdentry) {
    return -1;
  }

  st->st_mode = S_IFREG;
  st->st_blksize = (blksize_t)lfs_config.block_size;
  st->st_blocks = (blkcnt_t)lfs_config.block_count;

  if (fd < LFSBASE_FILENO) {
    st->st_size = (off_t)0;
  } else {
    st->st_size = (off_t)fdentry->file.ctz.size;
  }

  return 0;
}
