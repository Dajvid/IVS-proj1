//======== Copyright (c) 2017, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     White Box - Tests suite
//
// $NoKeywords: $ivs_project_1 $white_box_code.cpp
// $Author:     David Sedlák <xsedla1d@stud.fit.vutbr.cz>
// $Date:       $2017-01-04
//============================================================================//
/**
 * @file white_box_tests.cpp
 * @author David Sedlák
 *
 * @brief Implementace testu prace s maticemi.
 */

#include "gtest/gtest.h"
#include "white_box_code.h"

//============================================================================//
// ** ZDE DOPLNTE TESTY **
//
// Zde doplnte testy operaci nad maticemi. Cilem testovani je:
// 1. Dosahnout maximalniho pokryti kodu (white_box_code.cpp) testy.
// 2. Overit spravne chovani operaci nad maticemi v zavislosti na rozmerech
//    matic.
//============================================================================//
class mat_1x1setup : public ::testing::Test
{
protected:
    Matrix mat;
};

class mat_2x2setup : public ::testing::Test
{
protected:
    Matrix mat = Matrix(2, 2);
};

class mat_3x3setup : public ::testing::Test
{
protected:
    Matrix mat = Matrix(3, 3);
};

class mat_4x4setup : public ::testing::Test
{
protected:
    Matrix mat = Matrix(4, 4);
};

class mat_binary_op_fixture : public ::testing::Test
{
protected:
    Matrix mat2x2A = Matrix(2, 2);
    Matrix mat2x2B = Matrix(2, 2);
    Matrix mat2x3C = Matrix(2, 3);
    Matrix mat3x2D = Matrix(3, 2);
    Matrix mat2x2E = Matrix(2, 2);

    virtual void SetUp() {
        EXPECT_ANY_THROW(Matrix mat = Matrix(0, 4));
        std::vector<std::vector<double>> matA = {{2, 10}, {4, -16}};
        std::vector<std::vector<double>> matB = {{-11, 55}, {4, 151}};
        std::vector<std::vector<double>> matC = {{10, 15, 8}, {1, 22, 16}};
        std::vector<std::vector<double>> matD = {{44, 18}, {5, 11}, {22, 61}};

        mat2x2A.set(matA);
        mat2x2B.set(matB);
        mat2x2E.set(matA);
        mat2x3C.set(matC);
        mat3x2D.set(matD);
    };
};

class mat_equation_fixture : public ::testing::Test
{
protected:
    Matrix zero_mat = Matrix(3, 3);
    Matrix mat1x1 = Matrix(1, 1);
    Matrix mat2x2 = Matrix(2, 2);
    Matrix mat3x3 = Matrix(3, 3);
    Matrix mat4x4 = Matrix(4, 4);
    Matrix mat3x2 = Matrix(3, 2);

    double res_vec1x1 = 10;
    std::vector<std::vector<double>> res {{10}, {5, 2}, {3, 0, 12}, {3, 5, 1, -4}};
    std::vector<std::vector<double>> roots {{2}, {1, 3}, {3.5, 1, 2.5}, {1, -1, 0, 3}};

    virtual void SetUp() {
        std::vector<std::vector<double>> mat2x2_val = {{2, 1}, {-1, 1}};
        std::vector<std::vector<double>> mat3x3_val = {{2, 1, -2}, {1, -1, -1}, {1, 1, 3}};
        std::vector<std::vector<double>> mat4x4_val = {{2, 2, -3, 1}, {1, 2, 4, 2}, {-1, 1, -1, 1}, {1, -1, 2, -2}};

        mat1x1.set(0, 0, 5);
        mat2x2.set(mat2x2_val);
        mat3x3.set(mat3x3_val);
        mat4x4.set(mat4x4_val);
    }
};

TEST_F(mat_2x2setup, test_mutator)
{
    std::vector<std::vector<double>> val = {{18, 1620, 125}, {-108, -2196}};

    /* initial values */
    EXPECT_DOUBLE_EQ(mat.get(0, 0), 0);
    EXPECT_DOUBLE_EQ(mat.get(0, 1), 0);
    EXPECT_DOUBLE_EQ(mat.get(1, 0), 0);
    EXPECT_DOUBLE_EQ(mat.get(1, 1), 0);

    /* valid set */
    EXPECT_TRUE(mat.set(0, 0, 2));
    EXPECT_TRUE(mat.set(0, 1, 10));
    EXPECT_TRUE(mat.set(1, 0, -4));
    EXPECT_TRUE(mat.set(1, 1, 1.4));

    /* invalid set */
    EXPECT_FALSE(mat.set(-1, -1, 1));
    EXPECT_FALSE(mat.set(0, -1, 1));
    EXPECT_FALSE(mat.set(1, -1, 1));
    EXPECT_FALSE(mat.set(2, -1, 1));

    EXPECT_FALSE(mat.set(-1, 0, 1));
    EXPECT_FALSE(mat.set(-1, 1, 1));
    EXPECT_FALSE(mat.set(-1, 2, 1));

    EXPECT_FALSE(mat.set(0, 2, 1));
    EXPECT_FALSE(mat.set(1, 2, 1));
    EXPECT_FALSE(mat.set(2, 2, 1));

    EXPECT_FALSE(mat.set(2, 0, 1));
    EXPECT_FALSE(mat.set(2, 1, 1));

    EXPECT_FALSE(mat.set(val));
    /* check */
    EXPECT_DOUBLE_EQ(mat.get(0, 0), 2);
    EXPECT_DOUBLE_EQ(mat.get(0, 1), 10);
    EXPECT_DOUBLE_EQ(mat.get(1, 0), -4);
    EXPECT_DOUBLE_EQ(mat.get(1, 1), 1.4);
    EXPECT_ANY_THROW(mat.get(-4, 5));
}

TEST_F(mat_binary_op_fixture, test_binary_op)
{
    Matrix mat;
    EXPECT_ANY_THROW(Matrix(-4, -5));
    std::vector<std::vector<double>> mul_res = {{18, 1620}, {-108, -2196}};

    /* op == */
    EXPECT_FALSE(mat2x2A == mat2x2B);
    EXPECT_ANY_THROW(mat2x2A == mat2x3C);
    EXPECT_TRUE(mat2x2A == mat2x2A);
    EXPECT_TRUE(mat2x2A == mat2x2E);

    /* op +, * */
    Matrix result = Matrix(2, 2);
    result = mat2x2A + mat2x2A;
    EXPECT_ANY_THROW(mat2x2A + mat2x3C);
    EXPECT_ANY_THROW(mat2x2A * mat3x2D);
    EXPECT_TRUE(result == mat2x2A * 2);
    result.set(mul_res);
    EXPECT_TRUE(result == mat2x2A * mat2x2B);

}

TEST_F(mat_equation_fixture, test_equation)
{
    std::vector<double> result = mat1x1.solveEquation(res[0]);
    EXPECT_DOUBLE_EQ(result[0], roots[0][0]);

    result = mat2x2.solveEquation(res[1]);
    EXPECT_DOUBLE_EQ(result[0], roots[1][0]);
    EXPECT_DOUBLE_EQ(result[1], roots[1][1]);

    result = mat3x3.solveEquation(res[2]);
    EXPECT_DOUBLE_EQ(result[0], roots[2][0]);
    EXPECT_DOUBLE_EQ(result[1], roots[2][1]);
    EXPECT_DOUBLE_EQ(result[2], roots[2][2]);

    result = mat4x4.solveEquation(res[3]);
    EXPECT_DOUBLE_EQ(result[0], roots[3][0]);
    EXPECT_DOUBLE_EQ(result[1], roots[3][1]);
    EXPECT_DOUBLE_EQ(result[2], roots[3][2]);
    EXPECT_DOUBLE_EQ(result[3], roots[3][3]);

    EXPECT_ANY_THROW(mat3x2.solveEquation(res[1]));
    EXPECT_ANY_THROW(mat2x2.solveEquation(res[0]));
    EXPECT_ANY_THROW(zero_mat.solveEquation(res[2]));
}


/*** Konec souboru white_box_tests.cpp ***/
