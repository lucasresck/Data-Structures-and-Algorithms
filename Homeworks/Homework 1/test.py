import numpy as np


def insert_sort(a):
    pass


def merge_sort(a):
    pass


def is_sorted(a):
    return false


def main():
    ns = np.linspace(10000, 100000, 10)

    for n in ns:
        # create and fill an array with random numbers
        # a = ...

        # call insert_sort and  calculate the time
        sorted_a = insert_sort(a)
        if not is_sorted(sorted_a):
            print("ERROR")

        # call merge_sort and  calculate the time
        sorted_a = merge_sort(a)
        if not is_sorted(sorted_a):
            print("ERROR")

        print("%d %f %f" % (n, t1, t2))


if __name__ == "__main__":
    main()
