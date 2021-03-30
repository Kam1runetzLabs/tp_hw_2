import random


def generate_and_write_vectors(path: str) -> None:
    with open(path, "w+") as file:
        file.write(str(round(random.uniform(begin_range, end_range))))
