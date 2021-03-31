import os
import random


def write_vectors(vectors: list, f_name: str) -> None:
    with open(f_name, "w+") as file:
        for vector in vectors:
            file.write(vector)


def generate_vector_coords(count: int) -> str:
    vector = str()
    for _ in range(count):
        vector += str(random.uniform(0, 1234))
        vector += " "
    vector += "\n"
    return vector


def main():
    f_name = os.environ['VECTORS_PATH']
    vectors_count = int(os.environ['VECTORS_COUNT'])
    vectors_dims = int(os.environ['VECTORS_DIMS'])

    vectors = list()
    for _ in range(vectors_dims):
        vectors.append(generate_vector_coords(vectors_count))

    write_vectors(vectors, f_name)


if __name__ == "__main__":
    main()
