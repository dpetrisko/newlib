multilibtool_DATA += %D%/dramfs.specs
multilibtool_LIBRARIES += %D%/libdramfs.a
%C%_libdramfs_a_CPPFLAGS  = -I$(srcdir)/%D%
%C%_libdramfs_a_CPPFLAGS += -I$(LITTLEFS_DIR)
%C%_libdramfs_a_SOURCES = \
    %D%/sys_close.c \
    %D%/sys_execve.c \
    %D%/sys_exit.c \
    %D%/sys_fork.c \
    %D%/sys_fstat.c \
    %D%/sys_getpid.c \
    %D%/sys_gettimeofday.c \
    %D%/sys_isatty.c \
    %D%/sys_kill.c \
    %D%/sys_link.c \
    %D%/sys_lseek.c \
    %D%/sys_open.c \
    %D%/sys_read.c \
    %D%/sys_sbrk.c \
    %D%/sys_stat.c \
    %D%/sys_times.c \
    %D%/sys_unlink.c \
    %D%/sys_wait.c \
    %D%/sys_write.c \
    %D%/machine/dramfs_fdtable.c \
    %D%/machine/dramfs_fs.c \
    %D%/bd/lfs_stubbd.c \
    $(LITTLEFS_DIR)/lfs.c \
    $(LITTLEFS_DIR)/lfs_util.c \
    $(LITTLEFS_DIR)/bd/lfs_emubd.c \
    $(LITTLEFS_DIR)/bd/lfs_filebd.c \
    $(LITTLEFS_DIR)/bd/lfs_rambd.c

includemachinetool_DATA += %D%/machine/dramfs_fdtable.h
includemachinetool_DATA += %D%/machine/dramfs_fs.h

includetool_DATA += $(LITTLEFS_DIR)/lfs.h
includetool_DATA += $(LITTLEFS_DIR)/lfs_util.h

includebdtooldir = $(tooldir)/include/bd
includebdtool_DATA  = %D%/bd/lfs_stubbd.h
includebdtool_DATA += $(LITTLEFS_DIR)/bd/lfs_emubd.h
includebdtool_DATA += $(LITTLEFS_DIR)/bd/lfs_rambd.h
includebdtool_DATA += $(LITTLEFS_DIR)/bd/lfs_filebd.h

