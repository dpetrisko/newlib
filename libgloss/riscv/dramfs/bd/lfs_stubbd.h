/*
 * Copyright (c) 2024, Univerisity of Washington
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef LFS_STUBBD_H
#define LFS_STUBBD_H

#include "lfs.h"

#ifdef __cplusplus
extern "C" {
#endif

// Address of the file system pointer 
extern uint8_t __attribute__((weak)) *lfs_mem;

int lfs_stub_read(const struct lfs_config *c, lfs_block_t block, lfs_off_t off,
                  void *buffer, lfs_size_t size);

int lfs_stub_prog(const struct lfs_config *c, lfs_block_t block, lfs_off_t off,
                  const void *buffer, lfs_size_t size);

int lfs_stub_erase(const struct lfs_config *c, lfs_block_t block);

int lfs_stub_sync(const struct lfs_config *c);

#ifdef __cplusplus
}
#endif

#endif
