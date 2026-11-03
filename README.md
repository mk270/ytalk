# ytalk (unofficial fork)

YTalk is a replacement for the Unix `talk` program that can talk to
several people at once and understands the different talk daemons in
use. This repository is an **unofficial fork** of the Debian package
`ytalk` 3.3.0-9. It is not affiliated with the original author, the
previous maintainers, or Debian. The upstream README is kept as
[`README`](README).

## Why this exists

The upstream project has been dormant for a long time and the Debian
package is orphaned (maintained by the Debian QA group). This fork
preserves the code with its history, makes it build with current
compilers, and fixes bugs found in a security review. See
[CHANGES.md](CHANGES.md) and [SECURITY.md](SECURITY.md).

## Building

You need a C compiler and the ncurses development files.

    ./configure
    make

It builds with gcc 15 in its default C mode. `src/ytalk -v` prints the
version.

## Tests

After `./configure`, `tests/run.sh [N]` builds the terminal emulation
with AddressSanitizer and UndefinedBehaviorSanitizer and feeds it
escape sequences as a hostile peer might (a fixed case plus N
generated streams, default 300). There are no automated tests of
networking or of the user interface.

## Branches and tags

| Ref | Contents |
| --- | --- |
| `master` | upstream 3.3.0 tarball, unmodified (one commit) |
| tag `upstream/3.3.0` | the same commit |
| `debian` | master plus each Debian patch as its own commit, then `debian/` |
| tag `debian/3.3.0-9` | the Debian package as released |
| `fixes` | this fork's changes, on top of `debian` |

How the history was reconstructed, and the checksums of the source
files, are in [PROVENANCE.md](PROVENANCE.md).

## Things to know before using it

* The talk protocols have no authentication or encryption. Anyone who
  can reach you can claim to be anyone. See SECURITY.md.
* A connected peer can ask your ytalk to contact other `name@host`
  addresses (import/export). You are asked first unless the
  `auto-import` option is on; leave it off.
* The GitHub Actions workflow in `.github/workflows` has not been run
  yet; its commands were run locally.

## Licence

GNU General Public License, version 2 or (at your option) any later
version. See [COPYING](COPYING); the original copyright notices in the
source files are unchanged.

## Credits

Originally written by Britt Yenne. Later maintainers and contributors,
as listed in [AUTHORS](AUTHORS), include Andreas Kling, Jessica
Peterson, Roger Espel Llima, Alexander Rigbo, Benjamin Herr, Philipp
Kern, Matthew Vernon and Carl Edman. Debian patches are by the authors
named in each patch header (Matthew Johnson, Daniele Di Domizio and
Axel Beckert); the commit message of each patch commit records this.
