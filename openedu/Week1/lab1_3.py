from edx_io import edx_io

with edx_io() as io:
    # read input
    n = io.next_int()
    arr = [io.next_int() for i in range(n)]

    # list for saving intermediate indices
    indices = []

    # perform soring
    for i in range(n):
        for j in range(i - 1, -1, -1):
            if arr[j] > arr[j+1]:
                # if the order is wrong, swap 'em all!
                arr[j], arr[j+1] = arr[j+1], arr[j]
            else:
                # else remember the index or the inserted element, as requested
                # need j+1, indexing from 1
                indices.append(j + 2)
                # and go for inserting the next element
                break
        else:
            # if we reached the beginning, put 1 as index
            indices.append(1)

    # write results
    io.writeln(indices)
    io.writeln(arr)
