#include <inttypes.h>
#include <malloc.h>
#include <assert.h>
#include <iso646.h>

#ifndef NULL
#define NULL (void *)0
#endif
#define Campareable int
#define CampareablePoint Campareable *

struct SegmentTree
{
    int32_t __right;
    int32_t __left;
    int_least64_t __sum;
    int lazy;
    struct SegmentTree *left;
    struct SegmentTree *right;
};

static struct SegmentTree *__segment_tree_build(CampareablePoint source, int32_t start, int32_t end)
{
    if (start > end)
    {
        return NULL;
    }

    struct SegmentTree *root = (struct SegmentTree *)malloc(sizeof(struct SegmentTree));
    root->__left = start;
    root->__right = end;
    if (start == end)
    {
        root->__left = root->__right = start;
        root->__sum = source[start];
        root->right = root->left = NULL;
        return root;
    }
    else
    {
        root->left = __segment_tree_build(source, start, (start + end) / 2);
        root->right = __segment_tree_build(source, (start + end) / 2 + 1, end);
        root->__sum = root->left->__sum + root->right->__sum;
    }

    return root;
}

void segment_tree_init(struct SegmentTree **st, CampareablePoint source, int32_t length)
{
    assert(length > 0);
    assert(*st == NULL);
    assert(sizeof(CampareablePoint) == sizeof(struct SegmentTree *));
    (*st) = __segment_tree_build(source, 0, length - 1);
}

void segment_tree_update(struct SegmentTree *st, uint32_t l, uint32_t r, char tag, int value)
{
    // 一个最基本的认识在于 l与r小于st最大的区间
    st->__left > l &&st->__right < r ? (l = st->__left), (r = st->__right) : (void *)0;

    // 没有交集

    int t = ((st->__left - l) * (st->__right - r));
    if (t > 0)
    {
        return;
    }

    st->__sum += (r - l + 1) * value;
    // 包含关系
    if (l == st->__left && r == st->__right)
    {
        st->lazy += value;
        return;
    }

    if (st->lazy != 0)
    {
        st->left->lazy += st->lazy;
        st->right->lazy += st->lazy;
        st->left->__sum += st->lazy * (st->left->__right - st->left->__left);
        st->right->__sum += st->lazy * (st->right->__right - st->right->__left);
        st->lazy = 0;
    }
    // 此时说明被夹的区间在左半边
    if (st->right->__left > r)
    {
        // 传递懒标记
        segment_tree_update(st->left, l, r, 'a', value);
        return;
    }

    // 此时说明被夹的区间在右半边
    if (st->left->__right < l)
    {
        segment_tree_update(st->right, l, r, 'a', value);
        return;
    }

    // 这种情况就肯定会出现了 包含了左右区间；
    //我们做个断言
    assert(st->right->__left < r && st->left->__right > l);
    segment_tree_update(st->right, r, l, 'a', value);
    segment_tree_update(st->left, r, l, 'a', value);
}

int segment_tree_query(struct SegmentTree *st, uint32_t l, uint32_t r)
{
    ((st->__left > l) && (st->__right < r)) ? (l = st->__left), (r = st->__right) : (void *)0;
    // 没有交集

    int t = (st->__left - l) * (st->__right - r);
    if (t > 0)
    {
        return 0;
    }

    if (st->__left == l and st->__right == r)
    {
        return st->__sum;
    }

    if (st->lazy != 0)
    {
        st->left->lazy += st->lazy;
        st->right->lazy += st->lazy;
        st->left->__sum += st->lazy * (st->left->__right - st->left->__left);
        st->right->__sum += st->lazy * (st->right->__right - st->right->__left);
        st->lazy = 0;
    }

    int result1 = segment_tree_query(st->left, l, r);
    int result2 = segment_tree_query(st->right, l, r);

    return result1 + result2;
}
