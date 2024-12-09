#include "tmatrix.h"

#include <gtest.h>

template <typename T>
class TestTDynamicVector : public ::testing::Test
{
public:
	T* tmp1;
	T* tmp2;

	TDynamicVector<T>* vec;
	TDynamicVector<T>* v0;
	TDynamicVector<T>* v1;
	TDynamicVector<T>* v2;


	void SetUp()
	{
		tmp1 = new T[10]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
		v1 = new TDynamicVector<T>(tmp1, 10);

		tmp2 = new T[10]{ 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
		v2 = new TDynamicVector<T>(tmp2, 10);

		vec = new TDynamicVector<T>(*v1);
		v0 = nullptr;

	}
	void TearDown()
	{
		delete vec; delete v0; delete v1; delete v2;
		delete[] tmp1; tmp1 = nullptr;
		delete[] tmp2; tmp2 = nullptr;

	}

	void BuildDynamicVector(size_t s = 5)
	{
		vec = new TDynamicVector<T>(s);
		v0 = new TDynamicVector<T>(*vec);

	}
};

TYPED_TEST_CASE_P(TestTDynamicVector);

TYPED_TEST_P(TestTDynamicVector, can_create_vector_with_positive_length)
{
	ASSERT_NO_THROW(this->BuildDynamicVector(5));
}


TYPED_TEST_P(TestTDynamicVector, throws_when_create_vector_with_negative_length)
{
	ASSERT_ANY_THROW(this->BuildDynamicVector(-5));
}

TYPED_TEST_P(TestTDynamicVector, can_create_copied_vector)
{
	ASSERT_NO_THROW(this->BuildDynamicVector());
}

TYPED_TEST_P(TestTDynamicVector, copied_vector_is_equal_to_source_one)
{
	EXPECT_EQ((*(this->vec)), (*(this->v1)));
}

TYPED_TEST_P(TestTDynamicVector, copied_vector_has_its_own_memory)
{
	EXPECT_NE((this->vec), (this->v1));
}

TYPED_TEST_P(TestTDynamicVector, can_get_size)
{
	EXPECT_EQ(10, (this->vec->size()));
}


TYPED_TEST_P(TestTDynamicVector, throws_when_set_element_with_negative_index)
{
	ASSERT_ANY_THROW(this->vec->at(-1) = 4);
}

TYPED_TEST_P(TestTDynamicVector, throws_when_set_element_with_too_large_index)
{
	ASSERT_ANY_THROW(this->vec->at(30));
}

TYPED_TEST_P(TestTDynamicVector, can_assign_vector_to_itself)
{
	*(this->vec) = *(this->vec);

	EXPECT_EQ(*(this->vec), *(this->vec));
}

TYPED_TEST_P(TestTDynamicVector, can_assign_vectors_of_equal_size)
{
	*(this->vec) = *(this->v2);

	EXPECT_EQ(*(this->vec), *(this->v2));
}


REGISTER_TYPED_TEST_CASE_P(TestTDynamicVector, can_create_vector_with_positive_length, throws_when_create_vector_with_negative_length,
	can_create_copied_vector, copied_vector_is_equal_to_source_one, copied_vector_has_its_own_memory, can_get_size, throws_when_set_element_with_negative_index,
	throws_when_set_element_with_too_large_index, can_assign_vector_to_itself, can_assign_vectors_of_equal_size);

typedef::testing::Types<int, double> VectorTypes;

INSTANTIATE_TYPED_TEST_CASE_P(VectorTypesInstantiation, TestTDynamicVector, VectorTypes);



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

