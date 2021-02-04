#include "st.h"

int main()
{

    struct SegmentTree *st = NULL;
    int c[] = {1, 2, 3, 4, 5, 6};
    segment_tree_init(&st, (void *)c, 6);
    int queryValue0 = segment_tree_query(st, 3, 4);
    int queryValue1 = segment_tree_query(st, 5, 5);

    segment_tree_update(st, 3, 4, 'a', 8);
}