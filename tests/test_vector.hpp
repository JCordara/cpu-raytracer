/*
 * Unit tests for vector container class
 * Using custom eztest framework, see eztest_macros.h for implementation detail
 */

TEST_START(test_construction)

    vector<int> v0;
    CHECK_EQ(v0.size(), 0, "Default construction size wrong")
    CHECK_EQ(v0.capacity(), VECTOR_DEFAULT_SIZE, "Default construction capacity wrong")

    vector<int> v1(4);
    CHECK_EQ(v1.size(), 0, "Capacity reserve construction size wrong")
    CHECK_EQ(v1.capacity(), 4, "Capacity reserve construction capacity wrong")

TEST_END(test_construction)


TEST_START(test_append)

    vector<int> v;
    v.append(5);
    CHECK_EQ(v.size(), 1, "Size incorrect after appending to empty vector")
    CHECK_TRUE(v.capacity() >= v.size(), "Capacity is less than vector length after appending to empty vector")
    CHECK_EQ(v[0], 5, "Element access operator returns incorrect value after appending to empty vector")

    v.append(8);
    v.append(10);
    CHECK_EQ(v.size(), 3, "Size incorrect after appending multiple values")
    CHECK_TRUE(v.capacity() >= v.size(), "Capacity is less than vector length after appending multiple values")
    CHECK_EQ(v[0], 5,  "1st element incorrect after appending multiple values")
    CHECK_EQ(v[1], 8,  "2nd element incorrect after appending multiple values")
    CHECK_EQ(v[2], 10, "3rd element incorrect after appending multiple values")

TEST_END(test_append)


TEST_START(test_prepend)

    vector<int> v;
    v.prepend(5);
    CHECK_EQ(v.size(), 1, "Size incorrect after prepending to empty vector")
    CHECK_TRUE(v.capacity() >= v.size(), "Capacity is less than vector length after prepending to empty vector")
    CHECK_EQ(v[0], 5, "Element access operator returns incorrect value after prepending to empty vector")

    v.prepend(8);
    v.prepend(10);
    CHECK_EQ(v.size(), 3, "Size incorrect after prepending multiple values")
    CHECK_TRUE(v.capacity() >= v.size(), "Capacity is less than vector length after prepending multiple values")
    CHECK_EQ(v[0], 10, "1st element incorrect after prepending multiple values")
    CHECK_EQ(v[1], 8,  "2nd element incorrect after prepending multiple values")
    CHECK_EQ(v[2], 5,  "3rd element incorrect after prepending multiple values")

TEST_END(test_prepend)


TEST_START(test_insert)

    vector<int> v;
    v.insert(0, 5);
    CHECK_EQ(v.size(), 1, "Size incorrect after inserting into empty vector")
    CHECK_TRUE(v.capacity() >= v.size(), "Capacity is less than vector length after inserting into empty vector")
    CHECK_EQ(v[0], 5, "Element access operator returns incorrect value after inserting into empty vector")

    v.insert(1, 8);
    CHECK_EQ(v.size(), 2, "Size incorrect after inserting 2nd value at end of single item vector")
    CHECK_TRUE(v.capacity() >= v.size(), "Capacity is less than vector length after inserting 2nd value at end of single item vector")
    CHECK_EQ(v[0], 5, "1st element incorrect after inserting item at end of single item vector")
    CHECK_EQ(v[1], 8, "2nd element incorrect after inserting item at end of single item vector")

    v.insert(1, 10);
    CHECK_EQ(v.size(), 3, "Size incorrect after inserting item in between values")
    CHECK_TRUE(v.capacity() >= v.size(), "Capacity is less than vector length after inserting item in between values")
    CHECK_EQ(v[0], 5,  "1st element incorrect after after inserting item in between values")
    CHECK_EQ(v[1], 10, "2nd element incorrect after after inserting item in between values")
    CHECK_EQ(v[2], 8,  "3rd element incorrect after after inserting item in between values")
    
    v.insert(0, 0);
    CHECK_EQ(v.size(), 4, "Size incorrect after inserting item at beginning")
    CHECK_TRUE(v.capacity() >= v.size(), "Capacity is less than vector length after inserting item at beginning")
    CHECK_EQ(v[0], 0,  "1st element incorrect after after inserting item at beginning")
    CHECK_EQ(v[1], 5,  "2nd element incorrect after after inserting item at beginning")
    CHECK_EQ(v[2], 10, "3rd element incorrect after after inserting item at beginning")
    CHECK_EQ(v[3], 8,  "4th element incorrect after after inserting item at beginning")

TEST_END(test_insert)


TEST_START(test_iterator)

    vector<int> v;
    v.append(0);
    v.append(1);
    v.append(2);
    v.append(3);
    v.append(4);
    v.append(5);
    
    int ix = 0;
    for (int& i : v) {
        CHECK_EQ(i, v[ix], "Iterator returns incorrect value")
        ix++;
    }

TEST_END(test_iterator)
