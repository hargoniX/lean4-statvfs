/-
  Copyright (c) 2021 Henrik Böving. All rights reserved.
  Released under MIT license as described in the file LICENSE.
  Authors: Henrik Böving
-/
open System

/--
  Initialize the statvfs environment.

  This function does the following things:
  1. register (`Statvfs`)`g_statvfs_external_class` class

  This function should always be called with `builtin_initialize initStatvfs`.
-/
@[extern "lean_statvfs_initialize"] constant initStatvfs : IO Unit

builtin_initialize initStatvfs


abbrev Fsblkcnt := UInt64
abbrev Fsfilcnt := UInt64

/--
  Represents a statvfs struct from <sys/statvfs.h>.

  Note that the C statvfs struct uses a type called `fsfilcnt_t` for
  some of its members. On Linux 64 bit this is just a `UInt64` so
  this structure represents it as one.
-/
structure Statvfs where
  bsize : UInt64
  frsize : UInt64
  blocks : Fsblkcnt
  bfree : Fsblkcnt
  bavail : Fsblkcnt
  files : Fsfilcnt
  ffree : Fsfilcnt
  favail : Fsfilcnt
  fsid : Fsfilcnt
  flag : Fsfilcnt
  namemax : Fsfilcnt
  deriving Repr, Inhabited, BEq, DecidableEq

namespace Statvfs

/--
  Obtains statvfs information of a `FilePath` by internally calling
  C's `statvfs` onto it.
-/
@[extern "lean_statvfs_of_path"]
constant of_path (a : @& FilePath) : IO Statvfs

/--
  Obtains statvfs information of a `IO.FS.Handle` by internally calling
  C's `fstatvfs` onto the file descriptor it is carrying.
-/
@[extern "lean_statvfs_of_handle"]
constant of_handle (a : @& IO.FS.Handle) : IO Statvfs

end Statvfs
