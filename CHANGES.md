# Changes in this fork

Relative to the Debian package `ytalk` 3.3.0-9 (git tag
`debian/3.3.0-9`). Branch `fixes`, oldest first.

* **Use real prototypes so it builds as C23 (gcc 15).** K&R function
  definitions and empty-parenthesis declarations were converted to
  prototypes, with correct types for callbacks (file descriptor
  handlers, drained-data handlers, menu functions, signal handlers).
  `RETSIGTYPE`, which `configure` sets to `int`, is replaced by
  `void`. The build no longer needs `-std=gnu99`. Menu callbacks that
  take a `yuser *` or `char *` are cast where they are called.
* **Fix pointer-sign and unused-parameter warnings.** `raw_term()`
  takes `const void *` and `full_read()` takes `void *`.
* **Add CI** (GitHub Actions): a hardened build and a smoke test.
* **vt100: cap escape-sequence arguments** (see SECURITY.md), with
  `tests/run.sh`, which runs the terminal emulation under ASan and
  UBSan against generated hostile input.

## Relative to upstream 3.3.0

The Debian patches (tag `debian/3.3.0-9`) add: a man page fix;
logging of your own typed text to the output file as well as the
peer's; use of `$SHELL` when starting a shell; use of `$USER` as your
user name when it is set; support for user names longer than eight
characters; a spelling fix; and a man page macro fix. Each is its own
commit on the `debian` branch.
