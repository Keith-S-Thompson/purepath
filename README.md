This is `purepath`.

With no arguments, it prints the value of the `$PATH` environment
variable with duplicates removed, maintaining the original order.
Elements that are not directories are removed.

With `-k`, elements that are not directories are kept.

With `-c`, elements starting with `/cygdrive/` are removed.

With `-C`, elements starting with `/cygdrive/` are removed if and only
if the environment variable `$DELETE_CYGDRIVE_FROM_PATH` is set.

(The `-c` and `-C` options deal with performance issues under Cygwin
on Windows in a large domain, where certain searches can be very slow.)

With one non-option argument, it uses the argument as the path to be purified.
