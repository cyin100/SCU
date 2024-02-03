datatype tree = empty | node of (tree * int * tree);

fun insert empty x = node (empty, x, empty)
    | insert (node(left, data, right)) x =
        if x < data then
            node(insert left x, data, right)
        else if x > data then
            node(left, data, insert right x)
        else
            node(left, data, right);

fun member empty x = false
    | member (node(left, data, right)) x =
        if x < data then
            member left x
        else if x > data then
            member right x
        else
            true;