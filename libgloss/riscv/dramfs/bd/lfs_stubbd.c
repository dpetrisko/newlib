/*
 * Copyright (c) 2024, Univerisity of Washington
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <string.h>

#include "lfs_stubbd.h"

int lfs_stub_read(const struct lfs_config *c, lfs_block_t block, lfs_off_t off,
                  void *buffer, lfs_size_t size) {
  memcpy(buffer, lfs_mem + (block * c->block_size) + off, size);
  return 0;
}

int lfs_stub_prog(const struct lfs_config *c, lfs_block_t block, lfs_off_t off,
                  const void *buffer, lfs_size_t size) {
  memcpy(lfs_mem + (block * c->block_size) + off, buffer, size);
  return 0;
}

int lfs_stub_erase(const struct lfs_config *c, lfs_block_t block) {
  memset(lfs_mem + (block * c->block_size), 0, c->block_size);
  return 0;
}

int lfs_stub_sync(const struct lfs_config *c) {
  (void)(c); // unused
  return 0;
}
