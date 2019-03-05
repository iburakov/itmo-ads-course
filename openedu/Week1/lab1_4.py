from edx_io import edx_io

with edx_io() as io:
    # read input
    n = io.next_int()
    incomes = [(io.next_float(), i + 1) for i in range(n)]

    # perform sorting
    # I tried Insertion Sort, even with Cython optimizations - time limit exceeded :(
    # bad time or variable limits, imo
    # thus using stable O(nlogn) sort here, they deserve it
    incomes.sort()

    # write results
    io.writeln((incomes[0][1], incomes[n // 2][1], incomes[-1][1]))
