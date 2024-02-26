/*
 * Copyright (c) 2024, Univerisity of Washington
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <unistd.h>

#include "dramfs_fdtable.h"
#include "dramfs_intf.h"

extern lfs_t lfs;
extern const struct lfs_config lfs_config;

/* Exit a program without cleaning up files.  */
void _exit (int exit_status) {
  dramfs_exit(exit_status);
  __builtin_unreachable();
}
