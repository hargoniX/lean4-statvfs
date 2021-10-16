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
constant Statvfs : Type

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

@[extern "lean_statvfs_bsize"]
constant bsize (a : @& Statvfs) : UInt64

@[extern "lean_statvfs_frsize"]
constant frsize (a : @& Statvfs) : UInt64

@[extern "lean_statvfs_fsid"]
constant fsid (a : @& Statvfs) : UInt64

@[extern "lean_statvfs_flag"]
constant flag (a : @& Statvfs) : UInt64

@[extern "lean_statvfs_namemax"]
constant namemax (a : @& Statvfs) : UInt64

@[extern "lean_statvfs_blocks"]
constant blocks (a : @& Statvfs) : UInt64

@[extern "lean_statvfs_bfree"]
constant bfree (a : @& Statvfs) : UInt64

@[extern "lean_statvfs_bavail"]
constant bavail (a : @& Statvfs) : UInt64

@[extern "lean_statvfs_files"]
constant files (a : @& Statvfs) : UInt64

@[extern "lean_statvfs_ffree"]
constant ffree (a : @& Statvfs) : UInt64

@[extern "lean_statvfs_favail"]
constant favail (a : @& Statvfs) : UInt64

instance : Repr Statvfs where
  reprPrec m prec := Repr.addAppParen
    ("{" ++
     s!"bsize := {m.bsize}\n" ++
     s!"frsize := {m.frsize}\n" ++
     s!"fsid := {m.fsid}\n" ++
     s!"flag := {m.flag}\n" ++
     s!"namemax := {m.namemax}\n" ++
     s!"blocks := {m.blocks}\n" ++
     s!"bfree := {m.bfree}\n" ++
     s!"bavail := {m.bavail}\n" ++
     s!"files := {m.files}\n" ++
     s!"ffree := {m.ffree}\n" ++
     s!"favail := {m.favail}\n" ++
     "}") prec

end Statvfs
