from edx_io import edx_io

with edx_io() as io:
    # read input
    n = io.next_int()
    incomes = [io.next_int() for i in range(n)]

    # perform sorting swaps not to bloat io (selection sort)
    for i in range(n - 1):
        # find min value and its index
        mi = incomes.index(min(incomes[i:]), i)

        # swap current and min
        if mi != i:
            incomes[mi], incomes[i] = incomes[i], incomes[mi]
            io.writeln(f"Swap elements at indices {i + 1} and {mi + 1}.")

    # write results
    io.writeln("No more swaps needed.")
    io.writeln(incomes)
