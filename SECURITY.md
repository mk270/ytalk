# Security

## Reporting a problem

**TODO (maintainer to fill in before publishing):** say here how to
report a vulnerability privately, for example GitHub's "Report a
vulnerability" feature once it is enabled on the repository, or an
email address.

## The protocol itself is not secure

ytalk speaks the traditional talk/ntalk protocols plus its own
extensions for conferences. None of them has authentication,
integrity checking, or encryption.

* The user name a peer announces is whatever the peer's client sent.
  Anyone who can reach you can claim to be anyone.
* Conversations and the names exchanged while setting them up are in
  plain text on the network.

* A Debian patch makes ytalk announce `$USER` as your name when that
  variable is set, instead of looking you up, so anyone running ytalk
  can announce any name.

This is a property of the protocols, not something a patch to this
code can fix. Use ytalk only on networks you trust, or through a tunnel.

## Options that matter

* **auto-import** (`FL_IMPORT`): when a connected peer sends an
  import/export packet for a third party, ytalk contacts that
  `name@host`. By default you are asked first. With auto-import on it
  happens silently, so any peer can steer your client to other hosts.
  Leave it off.
* **auto-invite** (`FL_INVITE`): ytalk listens on an auto-invite port
  unless started with `-i`. Anyone who can connect can make ytalk ask
  whether to talk to a given user; with auto-invite on, it does so
  without asking. Use `-i` if you do not need the feature.

## Fixed in this fork

* `vt100.c`: the numeric argument of an escape sequence was
  accumulated in a signed `int` with no limit, so a peer sending a
  long run of digits caused signed overflow (undefined behaviour).
  The value is now capped. Found by fuzzing under UBSan; `tests/run.sh`
  covers it.

The build conversion to real function prototypes is not a security fix
in itself, but it removes a class of mismatched-call bugs that K&R
declarations hide.

## Reviewed and found sound

* Packets from a peer (`v2_pack`, `v3_pack`, and the auto-invite
  packet) have their `name` and `host` fields terminated before use,
  and are formatted into correctly sized buffers.
* Window sizes sent by a peer are clamped to your own terminal's size
  (`set_win_region`), so a peer cannot make ytalk allocate large
  buffers that way.
* The unbounded-looking `strcpy`/`strcat` calls in `rc.c` and `cwin.c`
  are guarded by length checks or allocations of the right size.

## Not reviewed, or known limitations

* Beyond the VT100 fuzzing above, `term.c` and `menu.c` have not been
  read through for security problems.
* There are no automated tests of the network code or the interface.
* Many `write()` results are ignored (the compiler warns about them),
  so errors writing to a peer may go unnoticed.
* `strncpy` is used to fill fixed-width wire fields without
  terminating them; the receiving code terminates them, but a
  different implementation of the protocol might not.
