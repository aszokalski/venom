from example import MyClass


class MyClassAltered(MyClass):
    def one(self):
        return 1

    def add(self, a, b):
        return a + b + self.one()


if __name__ == "__main__":
    cl = MyClassAltered()
    print(cl.add(1, 2))
    print(cl.sub(1, 2))
