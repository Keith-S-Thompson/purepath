This is `purepath`.

Usage: purepath [-k] [path]

With no arguments, it prints the value of the `$PATH` environment
variable with duplicates removed, maintaining the original order.
Elements that are not directories are removed.

With `-k`, elements that are not directories are kept.

With one non-option argument, it uses the argument as the path to
be purified.

If the environment variable `$DELETE_CYGDRIVE_FROM_PATH` is set,
elements starting with `/cygdrive/` are removed.  This is a workaround
for performance issues under Cygwin on Windows in a large domain,
where certain searches can be very slow.
