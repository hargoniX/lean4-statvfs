open System

@[extern "lean_statvfs_initialize"] constant initStatvfs : IO Unit

builtin_initialize initStatvfs

/- Represents a statvfs struct from <sys/statvfs.h>. -/
constant Statvfs : Type

namespace Statvfs

@[extern "lean_statvfs_of_path"]
constant of_path (a : @& FilePath) : IO Statvfs
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

/- The following functions actually return C fsfilcnt_t values
   but those are just UInt64 on my platform so I'll use UInt64 here
-/

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
    (s!"\{ bsize := {m.bsize}, frsize := {m.frsize}, blocks := {m.blocks}, " ++
     s!"bfree := {m.bfree}, bavail := {m.bavail}, files := {m.files}, " ++
     s!"ffree := {m.ffree}, favail := {m.favail}, fsid := {m.fsid}, " ++
     s!"flag := {m.flag}, namemeax := {m.namemax} }" ) prec

end Statvfs
