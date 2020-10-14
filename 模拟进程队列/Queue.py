class Node:
    def __init__(self, data='', pre=None, post=None):
        self.data = data
        self.pre = pre
        self.post = post


class DoubleLinkedList:
    def __init__(self):
        self.head = Node()
        self.tail = Node()
        self.head.post = self.tail
        self.tail.pre = self.head
        self.length = 0

    def is_empty(self):
        return self.length == 0

    def is_in_queue(self, value=''):
        if self.is_empty():
            return False
        p = self.head
        while p.data != value and p != self.tail:
            p = p.post
        if p == self.tail:
            return False
        return True

    def append_node(self, value=''):
        if self.is_in_queue(value):
            print("进程 %s 已存在" % value)
        else:
            new_node = Node(value)
            p = self.head
            while p.post != self.tail:
                p = p.post
            new_node.post = self.tail
            new_node.pre = p
            p.post = new_node
            self.tail.pre = new_node
            self.length += 1
            print("进程 %s 入列成功" % value)

    def delete_node(self, value=''):
        if self.is_empty():
            print("进程队列为空")
            return False
        slow = self.head
        fast = self.head.post
        while fast.data != value and fast != self.tail:
            slow = slow.post
            fast = fast.post
        if fast.data == value:
            slow.post = fast.post
            fast.post.pre = slow
            self.length -= 1
            print("进程 %s 已删除" % value)
        else:
            print("进程 %s 不存在" % value)

    def in_queue(self):
        origin_str = input(">>>")
        origin_str = origin_str.split()
        for i in origin_str:
            self.append_node(i)

    def out_queue(self):
        origin_str = input(">>>")
        origin_str = origin_str.split()
        for i in origin_str:
            self.delete_node(i)

    def print_queue(self):
        p = self.head
        while p != self.tail:
            print("%s" % p.data, end=' ')
            p = p.post
        print("\n")


def show_menu():
    queue = DoubleLinkedList()
    while True:
        print('''请输入你的选择：
        \b\b1. 输入入队队列
        \b\b2. 输入出队队列
        \b\b3. 打印当前队列
        \b\b4. 离开程序''')
        choice = input('>>>')
        if choice == '1':
            print("请输入入队队列")
            queue.in_queue()
            print("\n")
        elif choice == '2':
            print("请输入出队队列")
            queue.out_queue()
            print("\n")
        elif choice == '3':
            queue.print_queue()
        elif choice == '4':
            exit(0)
        else:
            print("输入错误，请重新输入")


show_menu()
