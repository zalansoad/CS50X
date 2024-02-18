class Jar:
    def __init__(self, capacity=12):
        if capacity < 0:
            raise ValueError("Negative integer")
        self._capacity = capacity
        self._size = 0

    def __str__(self):
        jar_content = "🍪" * self._size
        return jar_content

    def deposit(self, n):
        if (n + self._size) > self._capacity:
            raise ValueError("Exceeds capacity")
        else:
            self._size = self._size + n

    def withdraw(self, n):
        if (self._size - n) < 0:
            raise ValueError("Cannot withdraw this much")
        else:
            self._size = self._size - n

    @property
    def capacity(self):
        return self._capacity

    @property
    def size(self):
        return self._size

def main():
        jar = Jar()
        print("Jar capacity: ", end ="")
        print(str(jar._capacity))
        print()
        print("Jar content: ", end ="")
        print(str(jar))
        print()
        print("Jar content: ", end ="")
        jar.deposit(5)
        print(str(jar))
        print()
        print("Jar content: ", end ="")
        jar.withdraw(3)
        print(str(jar))


main()