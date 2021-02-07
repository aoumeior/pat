# 红黑树
红黑树在上节已露过脸了，它和AVL树堪称双璧（虽然历史上红黑树与B树的渊源可能更深）。

红黑树的节点同样有平衡因子：
```go
    type node struct {
        key         int
        black       bool        //平衡因子
        parent      *node
        left, right *node
    }
```

## 注水的艺术
　　不同于AVL树的一本正经，红黑树走的是猥琐路线。我们不是想要一棵平衡树吗？好，先来一棵完美的平衡树，它从根到叶的所有路径都等长。我们把这棵树称为黑树。但是，黑树实在太完美了，我们很难从它身上捞到什么好处。于是，我们要对黑树进行注水。注进去的点，我们称之为红点，注过水的黑树就成了红黑树。  
　　不过，注水还有些讲究。有点像视频中过渡帧依赖于关键帧，在红黑树中，红点只允许出现在黑点之后。这确保了树中最长路径（半红半黑）的长度不会超过最短路径（全黑）长度的两倍，与AVL树有异曲同工之妙。

## 插入与再平衡
如上所述，插入红点。如果该点落在黑点之后，那么万事大吉，否则需要根据其叔父节点的颜色分两种情况考虑。
```
    ------------红叔模式------------
    =      bG      |      rG      =
    =     /  \     |     /  \     =
    =   rP    rU   |   bP    bU   =
    =   |          |   |          =
    =   rC         |   rC         =
```
　　对于叔父为红点的情况，改变父辈和祖辈节点的颜色就可以解决。不过，祖父与曾祖间可能需要继续协调，因而变色次数为O(logN)级。
```
    ------------------LR型-----------------    ------------------LL型-----------------
    |        bG        |        bC        |    |        bG        |        bP        |
    |       /  \       |       /  \       |    |       /  \       |       /  \       |
    |     rP    bU     |     rP    rG     |    |     rP    bU     |     rC     rG    |
    |    / \           |    / \    / \    |    |    /  \          |          /  \    |
    |      rC          |       u  v   bU  |    |  rC    x         |         x    bU  |
    |     /  \         |                  |
    |    u    v        |                  |
```
　　对于叔父节点不是红点的情况，依据三代关系可进一步分为四种情形。鉴于对称性，我们只分析其中两种，而它们都可以通过一次旋转变换解决。

```go
    func (tr *Tree) rebalanceAfterInsert(P *node, key int32) {
        for !P.black {                                          //双红，需要处理
            G := P.parent                                       //G != nil
            super := G.parent
            if key < G.key {
                U := G.right
                if U != nil && !U.black {                       //红叔模式，变色解决
                    P.black, U.black = true, true
                    if super != nil {                           //遇根终止
                        G.black = false
                        P = G.parent
                        continue                                //否则上溯
                    }
                } else {                                        //黑叔模式，旋转解决
                    if key < P.key {                            //LL
                        G.left, P.right = G.tryHook(P.right), P.hook(G)
                        G.black, P.black = false, true
                        tr.hookSubTree(super, P)
                    } else {                                    //LR
                        C := P.right
                        P.right, G.left = P.tryHook(C.left), G.tryHook(C.right)
                        C.left, C.right = C.hook(P), C.hook(G)
                        G.black, C.black = false, true
                        tr.hookSubTree(super, C)
                    }
                }
            } else {
                //...
            }
            break                                               //变色时才需要循环
        }
    }
```

## 删除与再平衡
```go
    func (tr *Tree) Remove(key int32) bool {
        //...
        if victim.parent == nil {
            //...
        } else {
            root := victim.parent
            //...
            if victim.black {                                   //红victim随便删，黑的要考虑
                if orphan != nil && !orphan.black {             //或者红子变黑顶上
                    orphan.black = true                 
                } else {                                        //剩下情况：victim黑，orphan也黑
                    tr.rebalanceAfterDelete(root, victim.key)   //此时victim的兄弟必然存在
                }
            }
            target.key = victim.key
        }
        return true
    }
```
红黑树的删除就是要设法留住黑点。当被删除的点或其遗孤是红点时不需太多考虑，否则要来一番移花接木。
```
    ----------------红叔模式----------------
    =        bG        |        bU        =
    =       /  \       |       /  \       =
    =     bO    rU     |     rG    bR     =
    =          /  \    |    /  \          =
    =        bL    bR  |  bO    bL        =
```
当遗孤的叔父为红点时，不好直接处理，但我们可以通过一次旋转变出一个黑叔父来。
```
    ------------------双黑------------------
    |        xG        |        bG        |
    |       /  \       |       /  \       |
    |     bO    bU     |     bO    rU     |
    |          /  \    |          /  \    |
    |        bL    bR  |        bL    bR  |

    ------------------中红------------------
    |        xG        |        xL        |
    |       /  \       |       /  \       |    ----------------中黑外红----------------
    |     bO    bU     |     bG    bU     |    |        xG        |        xU        |
    |          /  \    |    /  \  /  \    |    |       /  \       |       /  \       |
    |        rL    xR  |  bO   u  v   xR  |    |     bO    bU     |     bG    bR     |
    |       /  \       |                  |    |          /  \    |    /  \          |
    |      u    v      |                  |    |        bL    rR  |  bO    bL        |
```
　　当遗孤的叔父为黑点时，依据堂兄弟节点的颜色有三类情形：双黑、中红、中黑外红。其中双黑可以通过变色解决，如果这个过程中祖父节点的颜色发生变化，还会产生连锁效应。其它两种情形都需要一次旋转变换。  
　　红叔模式的变换不会导致双黑情形，所以整个删除过程的旋转次数不超过两次（O(1)，不同于AVL树的O(logN)），但是变色次数仍可到O(logN)。

```go
    func (tr *Tree) rebalanceAfterDelete(G *node, key int) {
        for {
            super := G.parent
            if key < G.key {
                U := G.right                                    //U != nil
                L, R := U.left, U.right
                if !U.black {                                   //红叔模式
                    G.right, U.left = G.hook(L), U.hook(G)      //红叔下必是两个实体黑
                    U.black, G.black = true, false
                    tr.hookSubTree(super, U)
                    continue                                    //变出黑叔后再行解决
                } else {
                    if L == nil || L.black {
                        if R == nil || R.black {                //双黑，变色解决
                            U.black = false
                            if G.black && super != nil {
                                G = super
                                continue                        //上溯
                            }
                            G.black = true
                        } else {                                //中黑外红
                            G.right, U.left = G.tryHook(L), U.hook(G)
                            U.black, G.black, R.black = G.black, true, true
                            tr.hookSubTree(super, U)
                        }
                    } else {                                    //中红
                        U.left, G.right = U.tryHook(L.right), G.tryHook(L.left)
                        L.right, L.left = L.hook(U), L.hook(G)
                        L.black, G.black = G.black, true
                        tr.hookSubTree(super, L)
                    }
                }
            } else {
                //...
            }
            break                                               //个别情况需要循环
        }
    }
```


对于完全随机的数据，普通的二分搜索树很好用；
二分搜索树的缺点就是极端情况下退化成链表；
对于查询较多的使用情况，AVL树很好用；
红黑树牺牲了平衡性，但统计性能更优（综合增删改查所有的操作）；


作者：陈Chris
链接：https://www.zhihu.com/question/45329574/answer/616230063
来源：知乎
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。

## 回答第一个问题：红黑树的根节点为什么要是黑的？
答案：因为麻烦。假设你有一个红色的根节点，现在，你要加入一个新的节点，按照要求，这个节点必须是黑色的，因为不能有连续的红色，然后，会变成下图这样
<img src="https://pic4.zhimg.com/50/v2-81e124f449c48dcfe9f0c9f92ccae514_hd.jpg?source=1940ef5c" data-caption="" data-size="normal" data-rawwidth="156" data-rawheight="123" class="content_image" width="156"/>但是这个时候，你发现问题了吗？他不符合要求，每条路径上的黑色节点的数量必须是一样的。左边的路径黑色的节点数量为0，右边的路径黑色节点数量为1.这个时候，唯一能做的就是进行变色或者旋转，把根节点变成黑色的，把子节点变成红色的。如下图<img src="https://pic2.zhimg.com/50/v2-49622b9f6f259c8c68e4d320b0341247_hd.jpg?source=1940ef5c" data-caption="" data-size="normal" data-rawwidth="127" data-rawheight="117" class="content_image" width="127"/>既然加入第二个节点后就会必须要把根节点变成黑色的，那为什么不一开始就要求根节点是黑色的。
## 第二个问题：为什么从每个叶子到根的所有路径上不能有两个连续的红色节点？
答案：为了保证树的平衡，保证最长的路径最多是最短路径的的两倍。想象一下，由于每条路径上的黑色节点都必须相等，所以最短的路径肯定是全是黑色节点。那最长的路径呢，如果要求红色的点不能连续，那最长的路径肯定是红黑相隔，由于根节点是黑色的，所以，最长的路径应该是黑色节点和红色节点一样多，也就是黑色节点的两倍。