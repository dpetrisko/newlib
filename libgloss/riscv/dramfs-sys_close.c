/*
 * Copyright (c) 2024, Univerisity of Washington
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <errno.h>

#include "dramfs_fdtable.h"
#include "dramfs_intf.h"

extern lfs_t lfs;
extern const struct lfs_config lfs_config;
extern int errno;

/* Close a file.  */
int _close (int fd) {
  int ret;

  if (fd < LFSBASE_FILENO) {
    errno = EBADF;
    return -1;
  }

  struct fdentry *fdentry = __get_fdentry(fd);
  if (!fdentry) {
    return -1;
  }

  if ((ret = lfs_file_close(&lfs, &fdentry->file)) < 0) {
    errno = ret;
    return -1;
  }

  __remove_fdentry(fd);
  return 0;
}
