This is `purepath`.

With no arguments, it prints the value of the `$PATH` environment
variable with duplicates removed, maintaining the original order.
Elements that are not directories are removed.

With `-k`, elements that are not directories are kept.

With `-c`, elements starting with `/cygdrive/` are removed.

With one non-option argument, it uses the argument as the path to be purified.
