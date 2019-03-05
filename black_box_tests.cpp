//======== Copyright (c) 2017, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Red-Black Tree - public interface tests
//
// $NoKeywords: $ivs_project_1 $black_box_tests.cpp
// $Author:     David Sedlák <xsedla1d@stud.fit.vutbr.cz>
// $Date:       $2017-01-04
//============================================================================//
/**
 * @file black_box_tests.cpp
 * @author David Sedlák
 *
 * @brief Implementace testu binarniho stromu.
 */

#include <vector>

#include "gtest/gtest.h"

#include "red_black_tree.h"

//============================================================================//
// ** ZDE DOPLNTE TESTY **
//
// Zde doplnte testy Red-Black Tree, testujte nasledujici:
// 1. Verejne rozhrani stromu
//    - InsertNode/DeleteNode a FindNode
//    - Chovani techto metod testuje pro prazdny i neprazdny strom.
// 2. Axiomy (tedy vzdy platne vlastnosti) Red-Black Tree:
//    - Vsechny listove uzly stromu jsou *VZDY* cerne.
//    - Kazdy cerveny uzel muze mit *POUZE* cerne potomky.
//    - Vsechny cesty od kazdeho listoveho uzlu ke koreni stromu obsahuji
//      *STEJNY* pocet cernych uzlu.
//============================================================================//

class EmptyTree : public ::testing::Test
{
protected:
    BinaryTree tree;
};

/* EmptyTree */
TEST_F(EmptyTree, InsertNode_0)
{
    std::pair<bool, Node_t *> inserted, inserted_duplicit;
    std::vector<int> keys = {10, 12, 43, 18, 55, 60, 21, 23};
    std::vector<std::pair<bool, Node_t *>> result;

    inserted_duplicit = tree.InsertNode(10);
    EXPECT_TRUE(inserted_duplicit.first);
    EXPECT_EQ(inserted_duplicit.second->key, 10);

    inserted = tree.InsertNode(33);
    EXPECT_TRUE(inserted.first);
    EXPECT_EQ(inserted.second->key, 33);

    inserted = tree.InsertNode(-5);
    EXPECT_TRUE(inserted.first);
    EXPECT_EQ(inserted.second->key, -5);

    inserted = tree.InsertNode(10);
    EXPECT_FALSE(inserted.first);
    EXPECT_TRUE(inserted.second == inserted_duplicit.second);

    /* delete inserted nodes */
    tree.DeleteNode(10);
    tree.DeleteNode(33);
    tree.DeleteNode(-5);
    tree.DeleteNode(10);

    /* insert multiple nodes to empty tree */
    tree.InsertNodes(keys, result);
    for (int i = 0; i < result.size(); i++) {
        EXPECT_TRUE(result[i].first);
    }
}

TEST_F(EmptyTree, DeleteNode_0)
{
    EXPECT_FALSE(tree.DeleteNode(10));
    EXPECT_FALSE(tree.DeleteNode(10));
    EXPECT_FALSE(tree.DeleteNode(5));
    EXPECT_FALSE(tree.DeleteNode(-68));
    EXPECT_FALSE(tree.DeleteNode(91));

    EXPECT_FALSE(tree.GetRoot());
}

TEST_F(EmptyTree, FindNode_0)
{
    EXPECT_FALSE(tree.FindNode(10));
    EXPECT_FALSE(tree.FindNode(10));
    EXPECT_FALSE(tree.FindNode(5));
    EXPECT_FALSE(tree.FindNode(-68));
    EXPECT_FALSE(tree.FindNode(91));

    EXPECT_FALSE(tree.GetRoot());

    /* try to get all leaf nodes from empty tree */
    std::vector<Node_t *> result;
    Node_t node1, node2;
    tree.GetLeafNodes(result);
    EXPECT_TRUE(result.size() == 0);
    result.push_back(&node1);
    result.push_back(&node2);
    tree.GetLeafNodes(result);
    EXPECT_TRUE(result.size() == 0);

    /* try to get all nodes from empty tree */
    tree.GetAllNodes(result);
    EXPECT_TRUE(result.size() == 0);
    result.push_back(&node1);
    result.push_back(&node2);
    tree.GetAllNodes(result);
    EXPECT_TRUE(result.size() == 0);

    /* try to get all non-leaf nodes from empty tree */
    tree.GetNonLeafNodes(result);
    EXPECT_TRUE(result.size() == 0);
    result.push_back(&node1);
    result.push_back(&node2);
    tree.GetNonLeafNodes(result);
    EXPECT_TRUE(result.size() == 0);

    EXPECT_FALSE(tree.GetRoot());
}

/* NonEmptyTree */
class NonEmptyTree : public ::testing::Test
{
protected:
    BinaryTree tree;

    virtual void SetUp() {
        int values[] = { 680, -992, 552, 214, 531, -445, 993, 316, 625, 419, -415, 298, -626, -954, 130, -372, -616,
                         968, -720, -312 };

        for(int i = 0; i < 20; i++)
        {
            tree.InsertNode(values[i]);
        }
    }
};

TEST_F(NonEmptyTree, InsertNode_0)
{
    std::pair<bool, Node_t *> inserted, inserted_duplicit;
    std::vector<int> keys = {10, 12, 43, 18, 55, 60, 21, 23};
    std::vector<std::pair<bool, Node_t *>> result;

    inserted_duplicit = tree.InsertNode(-445);
    EXPECT_FALSE(inserted_duplicit.first);
    EXPECT_EQ(inserted_duplicit.second->key, -445);

    inserted_duplicit = tree.InsertNode(10);
    EXPECT_TRUE(inserted_duplicit.first);
    EXPECT_EQ(inserted_duplicit.second->key, 10);

    inserted = tree.InsertNode(33);
    EXPECT_TRUE(inserted.first);
    EXPECT_EQ(inserted.second->key, 33);

    inserted = tree.InsertNode(-5);
    EXPECT_TRUE(inserted.first);
    EXPECT_EQ(inserted.second->key, -5);

    inserted = tree.InsertNode(10);
    EXPECT_FALSE(inserted.first);
    EXPECT_TRUE(inserted.second == inserted_duplicit.second);

    /* insert multiple nodes to non empty tree */
    tree.InsertNodes(keys, result);
    EXPECT_FALSE(result[0].first);
    for (int i = 1; i < result.size(); i++) {
        EXPECT_TRUE(result[i].first);
    }
}

TEST_F(NonEmptyTree, DeleteNode_0)
{
    Node_t *root;

    EXPECT_FALSE(tree.DeleteNode(10));

    int values[] = { 680, -992, 552, 214, 531, -445, 993, 316, 625, 419, -415, 298, -626, -954, 130, -372, -616,
                     968, -720, -312 };

    for(int i = 0; i < 20; i++)
    {
        EXPECT_TRUE(tree.DeleteNode(values[i]));
        EXPECT_FALSE(tree.DeleteNode(values[i]));
    }

    EXPECT_FALSE(tree.GetRoot());
}

TEST_F(NonEmptyTree, FindNode_0)
{
    Node_t *found;
    std::vector<Node_t *> result;
    int values[] = { 680, -992, 552, 214, 531, -445, 993, 316, 625, 419, -415, 298, -626, -954, 130, -372, -616,
                     968, -720, -312 };

    for(int i = 0; i < 20; i++)
    {
        found = tree.FindNode(values[i]);
        EXPECT_TRUE(found);
        EXPECT_EQ(found->key, values[i]);
    }

    EXPECT_FALSE(tree.FindNode(10));
    EXPECT_FALSE(tree.FindNode(10));
    EXPECT_FALSE(tree.FindNode(5));
    EXPECT_FALSE(tree.FindNode(-68));
    EXPECT_FALSE(tree.FindNode(91));
    found = tree.GetRoot();
    EXPECT_TRUE(found);
    EXPECT_EQ(found->key, 419);

    tree.GetLeafNodes(result);
    EXPECT_EQ(result.size(), 21);
    tree.GetAllNodes(result);
    EXPECT_EQ(result.size(), 41);
    tree.GetNonLeafNodes(result);
    EXPECT_EQ(result.size(), 20);
}

/* Axioms */
class TreeAxioms : public ::testing::Test
{
protected:
    BinaryTree non_empty_non_pow2_tree, non_empty_pow2_tree, small_tree;

    virtual void SetUp() {
        int non_pow_values[] = {84, 89, -850, 854, 638, 438, 223, 71, -33, 392, 305, -666, -405, -498, -920, -219, -690, -257,
                                741, -768, -676, 749, -712, -77, -737, 163, -598, 652, 50, -753, -45, -126, 314, -745, 700,
                               -66, 560, 557, 490, 181};

        int pow_values[] = {564, -410, 521, -190, 521, -159, 18, -679, 444, -521, -326, -220, 635, 473, -654, 302, 1000, -751,
                        41, -290, -190, -423, -871, 184, -444, -308, -280, 640, 898, -674, 543, 359, 705, 946, 667, -506,
                        -294, -88, 3, 166, 765, 407, -777, 471, -682, -58, 994, 630, 512, 705, -157, 969, 383, 324, -417,
                        -221, -412, -243, -960, 136, 921, -942, -574, 776};

        for (int i = 0; i < 40; i++) {
            non_empty_non_pow2_tree.InsertNode(non_pow_values[i]);
        }
        for (int i = 0; i < 64; i++) {
            non_empty_pow2_tree.InsertNode(pow_values[i]);
        }

        small_tree.InsertNode(10);
        small_tree.InsertNode(15);
        small_tree.InsertNode(8);
        small_tree.InsertNode(4);
    }
};

TEST_F(TreeAxioms, Axiom1_0)
{
    std::vector<Node_t *> leaf_nodes;

    non_empty_pow2_tree.GetLeafNodes(leaf_nodes);

    for(int i = 0; i < leaf_nodes.size(); i++) {
        EXPECT_TRUE(leaf_nodes[i]->color == BinaryTree::BLACK);
    }

    non_empty_non_pow2_tree.GetLeafNodes(leaf_nodes);

    for(int i = 0; i < leaf_nodes.size(); i++) {
        EXPECT_TRUE(leaf_nodes[i]->color == BinaryTree::BLACK);
    }
}

TEST_F(TreeAxioms, Axiom2_0)
{
    std::vector<Node_t *> nodes;

    non_empty_pow2_tree.GetAllNodes(nodes);
    for(int i = 0; i < nodes.size(); i++) {
        if (nodes[i]->color == BinaryTree::RED) {
            EXPECT_TRUE(nodes[i]->pLeft->color == BinaryTree::BLACK);
            EXPECT_TRUE(nodes[i]->pRight->color == BinaryTree::BLACK);
        }
    }

    non_empty_non_pow2_tree.GetAllNodes(nodes);
    for(int i = 0; i < nodes.size(); i++) {
        if (nodes[i]->color == BinaryTree::RED) {
            EXPECT_TRUE(nodes[i]->pLeft->color == BinaryTree::BLACK);
            EXPECT_TRUE(nodes[i]->pRight->color == BinaryTree::BLACK);
        }
    }
}

int
get_black_node_count(Node_t *node)
{
    /* BLACK node is +1 */
    if (node->color == BinaryTree::BLACK) {
        if (node->pParent) {
            return(get_black_node_count(node->pParent) + 1);
        } else {
            return 1;
        }
    } else {
        if (node->pParent) {
            return(get_black_node_count(node->pParent));
        } else {
            return 0;
        }
    }
}

TEST_F(TreeAxioms, Axiom3_0)
{
    std::vector<Node_t *> leaf_nodes;
    int black_count = 0;

    non_empty_non_pow2_tree.GetLeafNodes(leaf_nodes);
    black_count = get_black_node_count(leaf_nodes[0]);
    for (int i = 0; i < leaf_nodes.size(); i++) {
        EXPECT_EQ(black_count, get_black_node_count(leaf_nodes[i]));
    }

    non_empty_pow2_tree.GetLeafNodes(leaf_nodes);
    black_count = get_black_node_count(leaf_nodes[0]);
    for (int i = 0; i < leaf_nodes.size(); i++) {
        EXPECT_EQ(black_count, get_black_node_count(leaf_nodes[i]));
    }
}

/*** Konec souboru black_box_tests.cpp ***/
