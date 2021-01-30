'''

逆波兰表达式：

逆波兰表达式是一种后缀表达式，所谓后缀就是指算符写在后面。

平常使用的算式则是一种中缀表达式，如 ( 1 + 2 ) * ( 3 + 4 ) 。
该算式的逆波兰表达式写法为 ( ( 1 2 + ) ( 3 4 + ) * ) 。
逆波兰表达式主要有以下两个优点：

去掉括号后表达式无歧义，上式即便写成 1 2 + 3 4 + * 也可以依据次序计算出正确结果。
适合用栈操作运算：遇到数字则入栈；遇到算符则取出栈顶两个数字进行计算，并将结果压入栈中

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/evaluate-reverse-polish-notation
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
'''

'''
Lukasiewicz原来提出的是前缀表示，即把每一运算符置于其运算对象之前。
例如，中缀式a+b和(a+b)/c相应的前缀表示分别为+ab和/+abc。
因此，为了区分前缀和后缀表示，通常将后缀表示称为逆波兰表示。
因前缀表示并不常用，所以有时也将后缀表示就称为波兰表示。


/*
1. 一种解法有点像八皇后， 就是一直读 ，如果得到括号就将符号压栈，递归，递归结束 出站 结合

*/


'''

class Solution:
    def evalRPN(self, tokens: List[str]) -> int:
        f1 = lambda a,b:a+b
        f2 = lambda a,b:a-b
        f3 = lambda a,b:a*b
        f4 = lambda a,b:int(a/b)
        maps = {'+':f1,'-':f2,'*':f3,'/':f4}
        stack = []
        for i in tokens:
            if i in maps:
                a = stack.pop()
                b = stack.pop()
                stack.append(maps[i](b,a))
            else:
                i = int(i)
                stack.append(i)
        return stack[-1]
                