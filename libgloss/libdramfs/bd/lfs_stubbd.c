#include <bd/lfs_stubbd.h>
#include <string.h>

int lfs_stub_read(const struct lfs_config *c, lfs_block_t block, lfs_off_t off
        , void *buffer, lfs_size_t size) {
    uint8_t *lfs_ptr = (uint8_t *)c->context;
    memcpy(buffer, lfs_ptr + (block * c->block_size) + off, size);
    return 0;
}

int lfs_stub_prog(const struct lfs_config *c, lfs_block_t block, lfs_off_t off
        , const void *buffer, lfs_size_t size) {
    uint8_t *lfs_ptr = (uint8_t *)c->context;
    memcpy(lfs_ptr + (block * c->block_size) + off, buffer, size);
    return 0;
}

int lfs_stub_erase(const struct lfs_config *c, lfs_block_t block) {
    uint8_t *lfs_ptr = (uint8_t *)c->context;
    memset(lfs_ptr + (block * c->block_size), 0, c->block_size);
    return 0;
}

int lfs_stub_sync(const struct lfs_config *c) {
    (void) (c); // unused
    return 0;
}
