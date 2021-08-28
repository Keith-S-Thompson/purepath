This is `purepath`.

With no arguments, it prints the value of the `$PATH` environment
variable with duplicates removed, maintaining the original order.
Elements that are not directories are removed; the `-k` option
keeps all entries.

With one argument, it uses the argument as the path to be purified.
