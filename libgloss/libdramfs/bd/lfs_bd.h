#ifndef LFS_BD_H

#include <bd/lfs_stubbd.h>
#include <bd/lfs_emubd.h>
#include <bd/lfs_filebd.h>
#include <bd/lfs_rambd.h>

#define LFS_BD_STUB 0
#define LFS_BD_EMU  1
#define LFS_BD_FILE 2
#define LFS_BD_RAM  3

#ifndef LFS_BD_TYPE
#define LFS_BD_TYPE LFS_BD_STUB
#endif

#define LFS_MK_FN(BD) \
    inline int lfs_read(const struct lfs_config *c, lfs_block_t block, lfs_off_t off \
            , void *buffer, lfs_size_t size) { \
        return lfs_ ## BD ## _read(c, block, off, buffer, size); \
    } \
    inline int lfs_prog(const struct lfs_config *c, lfs_block_t block, lfs_off_t off \
            , const void *buffer, lfs_size_t size) { \
        return lfs_ ## BD ## _prog(c, block, off, buffer, size); \
    } \
    inline int lfs_erase(const struct lfs_config *c, lfs_block_t block) { \
        return lfs_ ## BD ## _erase(c, block); \
    } \
    inline int lfs_sync(const struct lfs_config *c) { \
        return lfs_ ## BD ## _sync(c); \
    }

#if LFS_BD_TYPE == LFS_BD_STUB
LFS_MK_FN(stub)
#elif LFS_BD_TYPE == LFS_BD_EMU
LFS_MK_FN(emu)
#elif LFS_BD_TYPE == LFS_BD_FILE
LFS_MK_FN(file)
#elif LFS_BD_TYPE == LFS_BD_RAM
LFS_MK_FN(ram)
#else
#error INVALID LFS_BD_TYPE
#endif


#endif
