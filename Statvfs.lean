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

/--
  Represents a statvfs struct from <sys/statvfs.h>.

  Note that the C statvfs struct uses a type called `fsfilcnt_t` for
  some of its members. On Linux 64 bit this is just a `UInt64` so
  this structure represents it as one.
-/
structure Statvfs where
  bsize : UInt64
  frsize : UInt64
  blocks : UInt64
  bfree : UInt64
  bavail : UInt64
  files : UInt64
  ffree : UInt64
  favail : UInt64
  fsid : UInt64
  flag : UInt64
  namemax : UInt64

namespace Statvfs

attribute [extern "lean_statvfs_mk"] mk

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

instance : Repr Statvfs where
  reprPrec m prec := Repr.addAppParen
    (s!"\{ bsize := {m.bsize}, frsize := {m.frsize}, blocks := {m.blocks}, " ++
     s!"bfree := {m.bfree}, bavail := {m.bavail}, files := {m.files}, " ++
     s!"ffree := {m.ffree}, favail := {m.favail}, fsid := {m.fsid}, " ++
     s!"flag := {m.flag}, namemeax := {m.namemax} }" ) prec

end Statvfs
