This is `purepath`.

With no arguments, it prints the value of the `$PATH` environment
variable with duplicates removed, maintaining the original order.

With one argument, it uses the argument as the path to be purified.

**BUG** It dies with a segmentation fault if a `':'` character appears
at the end of the given path, or if there are two consecutive `':'`
characters.
