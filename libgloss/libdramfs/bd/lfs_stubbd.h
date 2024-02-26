/************************************************
 * Block device driver to interface with LittleFS
 ************************************************/

#ifndef LFS_STUBBD_H
#define LFS_STUBBD_H

#include <lfs.h>

#ifdef __cplusplus
extern "C" {
#endif

int lfs_stub_read(const struct lfs_config *c, lfs_block_t block, lfs_off_t off
        , void *buffer, lfs_size_t size);

int lfs_stub_prog(const struct lfs_config *c, lfs_block_t block, lfs_off_t off
        , const void *buffer, lfs_size_t size);

int lfs_stub_erase(const struct lfs_config *c, lfs_block_t block);

int lfs_stub_sync(const struct lfs_config *c);

#ifdef __cplusplus
}
#endif

#endif
