from edx_io import edx_io

with edx_io() as io:
    io.writeln(io.next_int() + io.next_int() ** 2)
