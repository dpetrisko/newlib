/*
 * Copyright (c) 2024, Univerisity of Washington
 * Copyright (c) 2019, Bandhav Veluri
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include "lfs.h"
#include <sys/types.h>

#ifndef DRAMFS_FDTABLE_H
#define DRAMFS_FDTABLE_H

#ifndef RISCV_MAX_OPEN_FILES
#define RISCV_MAX_OPEN_FILES 16
#endif

// STDIN_FILENO   0
// STDOUT_FILENO  1
// STDERR_FILENO  2
#define LFSBASE_FILENO 3

void __attribute__ ((constructor)) init_dramfs (void);

int __add_fdentry (lfs_file_t file);

struct fdentry* __get_fdentry (int fd);

void __remove_fdentry (int fd);

struct fdentry {
  bool active;
  lfs_file_t file;
};

// Keep track of stdin/stdout/stderr as well as normal files
static struct fdentry fdtable[RISCV_MAX_OPEN_FILES];

#endif
