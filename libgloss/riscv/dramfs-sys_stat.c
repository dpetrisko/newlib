/*
 * Copyright (c) 2024, Univerisity of Washington
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <errno.h>
#include <sys/stat.h>
#include <unistd.h>

#include "lfs.h"
#include "dramfs_fdtable.h"
#include "dramfs_fs.h"

extern lfs_t lfs;
extern const struct lfs_config lfs_config;
extern int errno;

/* Status of a file (by name).  */
int _stat (const char* name, struct stat* st) {
  struct lfs_info finfo;

  st->st_mode = S_IFREG;
  st->st_blksize = (blksize_t)lfs_config.block_size;
  st->st_blocks = (blkcnt_t)lfs_config.block_count;
 

   if (!strcmp("stdin", name)) {
     return STDIN_FILENO;
   } else if (!strcmp("stdout", name)) {
     return STDOUT_FILENO;
   } else if (!strcmp("stderr", name)) {
     return STDERR_FILENO;
   }

  int res;
  if (!strcmp("stdin", name)) {
     st->st_size = (off_t)0;
  } else if (!strcmp("stdout", name)) {
     st->st_size = (off_t)0;
  } else if (!strcmp("stderr", name)) {
     st->st_size = (off_t)0;
  } else if ((res = lfs_stat(&lfs, name, &finfo)) < 0) {
    errno = res;
    return -1;
  } else {
    st->st_size = (off_t)finfo.size;
  }

  return 0;
}
