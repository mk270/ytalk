# Provenance

Where the code came from, and how to check it.

## Source files

| File | SHA-256 |
| --- | --- |
| `ytalk_3.3.0.orig.tar.gz` | `6ecb34f71f723a7b96f90e411c78dff2735c08dc4228c765f7fdbf8ca48572b4` |
| `ytalk_3.3.0-9.debian.tar.xz` | `903a9c66bd127fe24160f2d31c10879b119f4bcab63dd4d61bd4e6ce05d6e53c` |

These match the checksums in Debian's `ytalk_3.3.0-9.dsc`. They were
downloaded from snapshot.debian.org:

* `https://snapshot.debian.org/archive/debian/20050312T000000Z/pool/main/y/ytalk/ytalk_3.3.0.orig.tar.gz`
* `https://snapshot.debian.org/archive/debian/20150515T155226Z/pool/main/y/ytalk/ytalk_3.3.0-9.dsc`
* `https://snapshot.debian.org/archive/debian/20150515T155226Z/pool/main/y/ytalk/ytalk_3.3.0-9.debian.tar.xz`

The `.dsc` carries a PGP signature, which was not verified when the
history was built; the checksums above are what tie the files to it.

## How the history was built

Debian source packages in the `3.0 (quilt)` format are an upstream
tarball plus a series of patches. The git history was generated from
them:

1. `master`: the `.orig.tar.gz` extracted as one commit, tagged
   `upstream/3.3.0`.
2. `debian`: each patch in `debian/patches/series` applied in order
   with `patch -p1`, one commit per patch. The commit subject comes
   from the patch's `Subject:` or `Description:` header and the body
   names the patch file and its `From:`/`Author:`.
3. A final commit adding `debian/` (without `patches/`), tagged
   `debian/3.3.0-9`.

Afterwards the `debian/3.3.0-9` tree was compared with a fresh
`dpkg-source -x ytalk_3.3.0-9.dsc`; the two are identical apart from
quilt's own `.pc/` directory and `debian/patches/` (see Reproducing).

## What the history does not tell you

* The commits up to `debian/3.3.0-9` were created by a script. Their
  author is the placeholder `re-talk import <import@localhost>` and
  their dates are the day the import was done, **not** the original
  authors or dates. The real authors are named in the patch headers
  and in the commit messages.
* Upstream's own history (before 3.3.0) is not included.

## Reproducing

    dpkg-source -x ytalk_3.3.0-9.dsc extracted
    mkdir pristine
    git archive debian/3.3.0-9 | tar -x -C pristine
    diff -r extracted pristine

Expect exactly two differences: quilt's `.pc/` directory and
`debian/patches/`, both present in `extracted` only. The patches are
already applied in the git tree, as commits.
