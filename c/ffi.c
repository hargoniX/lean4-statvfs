/**
  Copyright (c) 2021 Henrik Böving. All rights reserved.
  Released under MIT license as described in the file LICENSE.
  Authors: Henrik Böving
*/
#include <lean/lean.h>

#include <sys/statvfs.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

typedef struct statvfs statvfs_t;

/**
 * External class for `Statvfs`.
 *
 * This class registers `statvfs *` as a lean external class.
 */
static lean_external_class *g_statvfs_external_class = NULL;

/**
 * `lean_object *`(`Statvfs`) -> `statvfs *` conversion
 */
statvfs_t *statvfs_unbox(lean_object *s)
{
    return (statvfs_t *)(lean_get_external_data(s));
}

/**
 * `statvfs *` -> `lean_object *`(`Statvfs`) conversion
 */
lean_object *statvfs_box(statvfs_t *s)
{
    return lean_alloc_external(g_statvfs_external_class, s);
}

/**
 * A do nothing iterator.
 */
inline static void noop_foreach(void *mod, b_lean_obj_arg fn) {}

/**
 * `Statvfs` destructor.
 */
inline static void statvfs_finalizer(void *stat)
{
    free((statvfs_t *)stat);
}

/**
 * Initialize statvfs environment.
 *
 * This function does the following things:
 * 1. register (`Statvfs`)`g_statvfs_external_class` class
 *
 * This function should always be called with `builtin_initialize`.
 */
lean_obj_res lean_statvfs_initialize()
{
    g_statvfs_external_class = lean_register_external_class(statvfs_finalizer, noop_foreach);
    return lean_io_result_mk_ok(lean_box(0));
}

/**
 * The C based constructor of the Lean `Statvfs` type.
 */
lean_obj_res lean_statvfs_mk(uint64_t bsize, uint64_t frsize, uint64_t blocks, uint64_t bfree, uint64_t bavail, uint64_t files, uint64_t ffree, uint64_t favail, uint64_t fsid, uint64_t flag, uint64_t namemax)
{
    statvfs_t *stat = malloc(sizeof(statvfs_t));
    stat->f_bsize = bsize;
    stat->f_frsize = frsize;
    stat->f_blocks = blocks;
    stat->f_bfree = bfree;
    stat->f_bavail = bavail;
    stat->f_files = files;
    stat->f_ffree = ffree;
    stat->f_favail = favail;
    stat->f_fsid = fsid;
    stat->f_flag = flag;
    stat->f_namemax = namemax;
    return statvfs_box(stat);
}

/**
 * constant Statvfs.of_path (a : @& FilePath) : IO Statvfs
 */
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

/**
 * `lean_object *`(`IO.FS.Handle`) -> `FILE *` conversion
 */
FILE *io_unbox_handle(lean_object *h) {
    return (FILE *)(lean_get_external_data(h));
}

/**
 * constant Statvfs.of_handle (a : @& IO.FS.Handle) : IO Statvfs
 */
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
