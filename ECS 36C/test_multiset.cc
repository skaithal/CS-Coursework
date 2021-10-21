/* Created by Sanjana Aithal */

#include <gtest/gtest.h>
#include "multiset.h"

TEST(Multiset, Empty) {
  Multiset<int> mset;

  // Should be fully empty 
  EXPECT_EQ(mset.Empty(), true);
  EXPECT_EQ(mset.Size(), 0);
  EXPECT_THROW(mset.Count(42), std::exception);
}

TEST(Multiset, OneKey_Insert) {
  Multiset<int> mset;

  // Test some insertion 
  mset.Insert(23);
  mset.Insert(42);
  mset.Insert(42);
  EXPECT_EQ(mset.Empty(), false);
  EXPECT_EQ(mset.Size(), 3);
  EXPECT_EQ(mset.Min(), 23);
  EXPECT_EQ(mset.Max(), 42);
  EXPECT_EQ(mset.Count(42), 2);
}

TEST(Multiset, Remove){
  Multiset<int> mset;

  //Insertion-->Removal
  mset.Insert(23);
  mset.Insert(43);
  mset.Insert(35);
  mset.Insert(23);

  EXPECT_EQ(mset.Count(23), 2);
  EXPECT_EQ(mset.Size(), 4);

  mset.Remove(23);
  EXPECT_EQ(mset.Count(23), 1);
  EXPECT_EQ(mset.Size(), 3);
  EXPECT_EQ(mset.Contains(23), true);

  mset.Remove(43);
  EXPECT_EQ(mset.Size(), 2);
  EXPECT_EQ(mset.Contains(43), false);

  mset.Remove(23);
  EXPECT_EQ(mset.Size(), 1);
  EXPECT_THROW(mset.Count(23), std::exception);

  mset.Remove(35);
  EXPECT_EQ(mset.Size(), 0);
  EXPECT_EQ(mset.Empty(), true);
}

TEST(Multiset, Size){
  Multiset<int> mset;

  //Insertion-->Removal(Random)-->Check Size

  mset.Insert(33);
  EXPECT_EQ(mset.Size(), 1);
  EXPECT_EQ(mset.Empty(), false);

  mset.Insert(2);
  EXPECT_EQ(mset.Size(), 2);
  EXPECT_EQ(mset.Contains(33), true);

  mset.Insert(5);
  mset.Remove(2);
  EXPECT_EQ(mset.Size(), 2);
  EXPECT_EQ(mset.Contains(2),false);

  mset.Insert(100);
  mset.Remove(5);
  mset.Remove(33);
  EXPECT_EQ(mset.Size(), 1);
  EXPECT_EQ(mset.Contains(100), true);

  mset.Remove(100);
  EXPECT_EQ(mset.Size(), 0);
  EXPECT_EQ(mset.Empty(), true);

}

TEST(Multiset, Empty_MultipleInsertions){
  Multiset<int> mset;

  //Insertion-->Removal(Random)-->Check Empty

  EXPECT_EQ(mset.Size(), 0);
  EXPECT_EQ(mset.Empty(), true);
  mset.Insert(33);
  mset.Insert(24);

  EXPECT_EQ(mset.Empty(), false);
  EXPECT_EQ(mset.Size(), 2);

  mset.Remove(24);
  EXPECT_EQ(mset.Size(), 1);
  EXPECT_EQ(mset.Empty(), false);

  mset.Remove(33);
  EXPECT_EQ(mset.Size(), 0);
  EXPECT_EQ(mset.Empty(), true);

}
TEST(Multiset, Contains){
  Multiset<int> mset;

  //Insertion-->Removal(Random)-->Check Contains

  mset.Insert(3);
  EXPECT_EQ(mset.Contains(3), true);
  EXPECT_EQ(mset.Contains(2), false);

  mset.Insert(5);
  mset.Insert(78);

  EXPECT_EQ(mset.Contains(5), true);
  EXPECT_EQ(mset.Contains(78), true);
  EXPECT_EQ(mset.Contains(56),false);
  EXPECT_EQ(mset.Contains(0), false);
  EXPECT_EQ(mset.Size(), 3);
  EXPECT_EQ(mset.Empty(), false);

}

TEST(Multiset, Count){
  Multiset<int> mset;

  //Insertion-->Removal(Random)-->Check Count

  mset.Insert(23);
  EXPECT_EQ(mset.Count(23), 1);
  EXPECT_EQ(mset.Size(), 1);

  mset.Insert(23);
  EXPECT_EQ(mset.Count(23),2);
  EXPECT_EQ(mset.Size(), 2);

  mset.Remove(23);
  EXPECT_EQ(mset.Count(23),1);

  mset.Remove(23);
  EXPECT_THROW(mset.Count(23), std::exception);
  EXPECT_EQ(mset.Size(), 0);
  EXPECT_EQ(mset.Empty(), true);

}


TEST(Multiset, Ceil){
  Multiset<int> mset;

  //Insertion --> Check Ceil

  mset.Insert(23);
  EXPECT_EQ(mset.Ceil(23), 23);
  EXPECT_THROW(mset.Ceil(24), std::exception);
  mset.Insert(12);
  mset.Insert(5);
  mset.Insert(8);
  mset.Insert(3);
  EXPECT_EQ(mset.Ceil(0), 3);
  EXPECT_EQ(mset.Ceil(4), 5);
  EXPECT_EQ(mset.Ceil(6), 8);
  EXPECT_EQ(mset.Ceil(10), 12);
  EXPECT_EQ(mset.Ceil(13), 23);
  EXPECT_THROW(mset.Ceil(24), std::exception);
  EXPECT_EQ(mset.Ceil(23), 23);

}

TEST(Multiset, Floor){
  Multiset<int> mset;

  //Insertion, Check Floor

  mset.Insert(23);
  mset.Insert(12);
  mset.Insert(5);
  mset.Insert(8);
  mset.Insert(3);

  EXPECT_THROW(mset.Floor(2), std::exception);
  EXPECT_EQ(mset.Floor(3), 3);
  EXPECT_EQ(mset.Floor(4), 3);
  EXPECT_EQ(mset.Floor(6), 5);
  EXPECT_EQ(mset.Floor(9), 8);
  EXPECT_EQ(mset.Floor(13), 12);
  EXPECT_EQ(mset.Floor(200), 23);
}


TEST(Multiset, Min){
  Multiset<int> mset;


  //Insertion, Check Min, Removal, Check Min

  EXPECT_THROW(mset.Min(), std::exception);

  mset.Insert(34);
  EXPECT_EQ(mset.Min(), 34);

  mset.Insert(5);
  mset.Insert(23);
  mset.Insert(2);

  EXPECT_EQ(mset.Min(),2);
  mset.Remove(2);
  EXPECT_EQ(mset.Min(), 5);
  mset.Remove(5);
  EXPECT_EQ(mset.Min(), 23);
  mset.Remove(23);
  EXPECT_EQ(mset.Min(),34);
}

TEST(Multiset, Max){
  Multiset<int> mset;

  //Insertion, Check Max, Removal, Check Max

  EXPECT_THROW(mset.Max(), std::exception);
  mset.Insert(23);
  EXPECT_EQ(mset.Max(), 23);
  mset.Insert(10);
  mset.Insert(23);
  mset.Remove(23);
  EXPECT_EQ(mset.Max(), 23);
  mset.Insert(54);
  EXPECT_EQ(mset.Max(), 54);
  mset.Insert(300);
  EXPECT_EQ(mset.Max(), 300);
  mset.Remove(300);
  mset.Remove(54);
  EXPECT_EQ(mset.Max(), 23);
}
int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}