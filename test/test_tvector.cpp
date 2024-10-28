#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicVector, can_create_vector_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicVector<int> v(5));
}

TEST(TDynamicVector, cant_create_too_large_vector)
{
  ASSERT_ANY_THROW(TDynamicVector<int> v(MAX_VECTOR_SIZE + 1));
}

TEST(TDynamicVector, throws_when_create_vector_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicVector<int> v(-5));
}

TEST(TDynamicVector, can_create_copied_vector)
{
  TDynamicVector<int> v(10);

  ASSERT_NO_THROW(TDynamicVector<int> v1(v));
}

TEST(TDynamicVector, copied_vector_is_equal_to_source_one)
{
	int* a = new int[10] {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	TDynamicVector<int> v(a, 10);
	delete[] a;
	TDynamicVector<int> v1(v);
	EXPECT_EQ(v, v1);
}

TEST(TDynamicVector, copied_vector_has_its_own_memory)
{
	int* a = new int[10] {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	TDynamicVector<int> v(a, 10);
	delete[] a;
	TDynamicVector<int> v1(v);
	TDynamicVector<int>* pv = &v;
	TDynamicVector<int>* pv1 = &v1;
	EXPECT_NE(pv, pv1);
}

TEST(TDynamicVector, can_get_size)
{
  TDynamicVector<int> v(4);

  EXPECT_EQ(4, v.size());
}

//TEST(TDynamicVector, can_set_and_get_element)
//{
//  TDynamicVector<int> v(4);
//  v[0] = 4;
//
//  EXPECT_EQ(4, v[0]);
//}

TEST(TDynamicVector, throws_when_set_element_with_negative_index)
{
	TDynamicVector<int> v(4);
	ASSERT_ANY_THROW(v.at(-1) = 4);
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index)
{
	TDynamicVector<int> v(4);
	ASSERT_ANY_THROW(v.at(5) = 4);
}


TEST(TDynamicVector, can_assign_vector_to_itself)
{
	TDynamicVector<int> v1(10);
	TDynamicVector<int> v2(10);
	v1[1] = v2[1] = 1;
	v1 = v1;

	EXPECT_EQ(v1, v2);
}

TEST(TDynamicVector, can_assign_vectors_of_equal_size)
{
	int* a = new int[10] {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	TDynamicVector<int> v(a, 10);
	delete[] a;
	int* b = new int[10] {1, 2, 3, 4, 5, 6, 7, 8, 9, 11};
	TDynamicVector<int> v1(b, 10);
	delete[] b;
	v = v1;
	EXPECT_EQ(v, v1);
}

TEST(TDynamicVector, assign_operator_change_vector_size)
{
	int* a = new int[10] {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	TDynamicVector<int> v(a, 10);
	delete[] a;
	int* b = new int[11] {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
	TDynamicVector<int> v1(b, 11);
	delete[] b;
	v = v1;
	EXPECT_EQ(v.size(), v1.size());
}

TEST(TDynamicVector, can_assign_vectors_of_different_size)
{
	int* a = new int[10] {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	TDynamicVector<int> v(a, 10);
	delete[] a;
	int* b = new int[8] {1, 2, 3, 4, 5, 6, 7, 8};
	TDynamicVector<int> v1(b, 8);
	delete[] b;
	v1 = v;
	EXPECT_EQ(v, v1);
}

TEST(TDynamicVector, compare_equal_vectors_return_true)
{
	int* a = new int[10] {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	TDynamicVector<int> v(a, 10);
	TDynamicVector<int> v1(a, 10);
	delete[] a;
	EXPECT_EQ(1, v == v1);
}

TEST(TDynamicVector, compare_vector_with_itself_return_true)
{
	int* a = new int[10] {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	TDynamicVector<int> v(a, 10);
	delete[] a;
	EXPECT_EQ(1, v == v);
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal)
{
	TDynamicVector<int> v1(10);
	TDynamicVector<int> v2(5);

	EXPECT_FALSE(v1 == v2);
}

TEST(TDynamicVector, can_add_scalar_to_vector)
{
	int val = 3;
	int* a = new int[3] {1, 2, 3};
	TDynamicVector<int> v(a, 3);
	delete[] a;
	int* b = new int[3] {4, 5, 6};
	TDynamicVector<int> v1(b, 3);
	delete[] b;
	EXPECT_EQ(v + val, v1);
}

TEST(TDynamicVector, can_subtract_scalar_from_vector)
{
	int val = 3;
	int* a = new int[3] {4, 5, 6};
	TDynamicVector<int> v(a, 3);
	delete[] a;
	int* b = new int[3] {1, 2, 3};
	TDynamicVector<int> v1(b, 3);
	delete[] b;
	EXPECT_EQ(v - val, v1);
}

TEST(TDynamicVector, can_multiply_scalar_by_vector)
{
	int val = 3;
	int* a = new int[3] {1, 2, 3};
	TDynamicVector<int> v(a, 3);
	delete[] a;
	int* b = new int[3] {3, 6, 9};
	TDynamicVector<int> v1(b, 3);
	delete[] b;
	EXPECT_EQ(v * val, v1);
}

TEST(TDynamicVector, can_add_vectors_with_equal_size)
{
	int* a = new int[3] {2, 3, 4};
	TDynamicVector<int> v(a, 3);
	delete[] a;
	int* b = new int[3] {1, 2, 3};
	TDynamicVector<int> v1(b, 3);
	delete[] b;
	int* c = new int[3] {1, 1, 1};
	TDynamicVector<int> v2(c, 3);
	delete[] c;
	EXPECT_EQ(v, v1 + v2);
}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size)
{
	int* a = new int[3] {1, 2, 3};
	TDynamicVector<int> v(a, 3);
	delete[] a;
	int* b = new int[4] {1, 2, 3, 4};
	TDynamicVector<int> v1(b, 4);
	delete[] b;
	ASSERT_ANY_THROW(v + v1);
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size)
{
	int* a = new int[3] {4, 3, 2};
	TDynamicVector<int> v(a, 3);
	delete[] a;
	int* b = new int[3] {1, 1, 1};
	TDynamicVector<int> v1(b, 3);
	delete[] b;
	int* c = new int[3] {5, 4, 3};
	TDynamicVector<int> v2(c, 3);
	delete[] c;
	EXPECT_EQ(v, v2 - v1);
}

TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size)
{
	int* a = new int[3] {1, 2, 3};
	TDynamicVector<int> v(a, 3);
	delete[] a;
	int* b = new int[4] {1, 2, 3, 4};
	TDynamicVector<int> v1(b, 4);
	delete[] b;
	ASSERT_ANY_THROW(v - v1);
}

TEST(TDynamicVector, can_multiply_vectors_with_equal_size)
{
	int sum = 32;
	int* a = new int[3] {1, 2, 3};
	TDynamicVector<int> v(a, 3);
	delete[] a;
	int* b = new int[3] {4, 5, 6};
	TDynamicVector<int> v1(b, 3);
	delete[] b;
	EXPECT_EQ(v * v1, sum);
}

TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size)
{
	int* a = new int[3] {1, 2, 3};
	TDynamicVector<int> v(a, 3);
	delete[] a;
	int* b = new int[4] {4, 5, 6, 7};
	TDynamicVector<int> v1(b, 4);
	delete[] b;
	ASSERT_ANY_THROW(v * v1);
}

