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
 * `statvfs *` -> `lean_object *`(`Statvfs`) conversion
 */
lean_object *statvfs_box(statvfs_t *s)
{
    lean_object *o;
    o = lean_alloc_ctor(1, 0, 11 * sizeof(uint64_t));
    lean_ctor_set_uint64(o, 0 * sizeof(uint64_t), (uint64_t)s->f_bsize);
    lean_ctor_set_uint64(o, 1 * sizeof(uint64_t), (uint64_t)s->f_frsize);
    lean_ctor_set_uint64(o, 2 * sizeof(uint64_t), (uint64_t)s->f_blocks);
    lean_ctor_set_uint64(o, 3 * sizeof(uint64_t), (uint64_t)s->f_bfree);
    lean_ctor_set_uint64(o, 4 * sizeof(uint64_t), (uint64_t)s->f_bavail);
    lean_ctor_set_uint64(o, 5 * sizeof(uint64_t), (uint64_t)s->f_files);
    lean_ctor_set_uint64(o, 6 * sizeof(uint64_t), (uint64_t)s->f_ffree);
    lean_ctor_set_uint64(o, 7 * sizeof(uint64_t), (uint64_t)s->f_favail);
    lean_ctor_set_uint64(o, 8 * sizeof(uint64_t), (uint64_t)s->f_fsid);
    lean_ctor_set_uint64(o, 9 * sizeof(uint64_t), (uint64_t)s->f_flag);
    lean_ctor_set_uint64(o, 10 * sizeof(uint64_t), (uint64_t)s->f_namemax);
    return o;
}

/**
 * Initialize statvfs environment.
 *
 * This function does the following things: (Noop at the moment)
 *
 * This function should always be called with `builtin_initialize`.
 */
lean_obj_res lean_statvfs_initialize()
{
    return lean_io_result_mk_ok(lean_box(0));
}

/**
 * constant Statvfs.of_path (a : @& FilePath) : IO Statvfs
 */
lean_obj_res lean_statvfs_of_path(b_lean_obj_arg a, lean_obj_arg w)
{
    statvfs_t stat;
    const char *path = lean_string_cstr(a);
    int err = statvfs(path, &stat);
    if (err == 0) {
        return lean_io_result_mk_ok(statvfs_box(&stat));
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
    statvfs_t stat;
    FILE *fp = io_unbox_handle(a);
    int err = fstatvfs(fileno(fp), &stat);
    if (err == 0) {
        return lean_io_result_mk_ok(statvfs_box(&stat));
    } else {
        lean_object *details = lean_mk_string(strerror(err));
        return lean_io_result_mk_error(lean_mk_io_user_error(details));
    }
}
