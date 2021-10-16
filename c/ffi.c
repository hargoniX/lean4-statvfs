#include <lean/lean.h>

#include <sys/statvfs.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

typedef struct statvfs statvfs_t;

static lean_external_class *g_statvfs_external_class = NULL;

statvfs_t *statvfs_unbox(lean_object *s)
{
    return (statvfs_t *)(lean_get_external_data(s));
}

lean_object *statvfs_box(statvfs_t *s)
{
    return lean_alloc_external(g_statvfs_external_class, s);
}

inline static void noop_foreach(void *mod, b_lean_obj_arg fn) {}

inline static void statvfs_finalizer(void *stat)
{
    free((statvfs_t *)stat);
}

lean_obj_res lean_statvfs_initialize()
{
    g_statvfs_external_class = lean_register_external_class(statvfs_finalizer, noop_foreach);
    return lean_io_result_mk_ok(lean_box(0));
}

lean_obj_res lean_statvfs_of_path(b_lean_obj_arg a, lean_obj_arg w)
{
    const char *path = lean_string_cstr(a);
    statvfs_t *stat = malloc(sizeof(statvfs_t));
    int err = statvfs(path, stat);
    if (err == 0) {
        return lean_io_result_mk_ok(statvfs_box(stat));
    } else {
        lean_object *details = lean_mk_string(strerror(errno));
        return lean_io_result_mk_error(lean_mk_io_user_error(details));
    }
}

FILE *io_unbox_handle(lean_object *h) {
    return (FILE *)(lean_get_external_data(h));
}

lean_obj_res lean_statvfs_of_handle(b_lean_obj_arg a, lean_obj_arg w)
{
    FILE *fp = io_unbox_handle(a);
    statvfs_t *stat = malloc(sizeof(statvfs_t));
    int err = fstatvfs(fileno(fp), stat);
    if (err == 0) {
        return lean_io_result_mk_ok(statvfs_box(stat));
    } else {
        lean_object *details = lean_mk_string(strerror(err));
        return lean_io_result_mk_error(lean_mk_io_user_error(details));
    }
}


uint64_t lean_statvfs_bsize(b_lean_obj_arg a, lean_obj_arg w)
{
    return statvfs_unbox(a)->f_bsize;
}

uint64_t lean_statvfs_frsize(b_lean_obj_arg a, lean_obj_arg w)
{
    return statvfs_unbox(a)->f_frsize;
}

uint64_t lean_statvfs_fsid(b_lean_obj_arg a, lean_obj_arg w)
{
    return statvfs_unbox(a)->f_fsid;
}

uint64_t lean_statvfs_flag(b_lean_obj_arg a, lean_obj_arg w)
{
    return statvfs_unbox(a)->f_flag;
}

uint64_t lean_statvfs_namemax(b_lean_obj_arg a, lean_obj_arg w)
{
    return statvfs_unbox(a)->f_namemax;
}

uint64_t lean_statvfs_blocks(b_lean_obj_arg a, lean_obj_arg w)
{
    return statvfs_unbox(a)->f_blocks;
}

uint64_t lean_statvfs_bfree(b_lean_obj_arg a, lean_obj_arg w)
{
    return statvfs_unbox(a)->f_bfree;
}

uint64_t lean_statvfs_bavail(b_lean_obj_arg a, lean_obj_arg w)
{
    return statvfs_unbox(a)->f_bavail;
}

uint64_t lean_statvfs_files(b_lean_obj_arg a, lean_obj_arg w)
{
    return statvfs_unbox(a)->f_files;
}

uint64_t lean_statvfs_ffree(b_lean_obj_arg a, lean_obj_arg w)
{
    return statvfs_unbox(a)->f_ffree;
}

uint64_t lean_statvfs_favail(b_lean_obj_arg a, lean_obj_arg w)
{
    return statvfs_unbox(a)->f_favail;
}

