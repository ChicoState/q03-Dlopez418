/**
 * Unit Tests for the class
**/

#include <gtest/gtest.h>
#include "Guesser.h"

class GuesserTest : public ::testing::Test
{
	protected:
		GuesserTest(){} //constructor runs before each test
		virtual ~GuesserTest(){} //destructor cleans up after tests
		virtual void SetUp(){} //sets up before each test (after constructor)
		virtual void TearDown(){} //clean up after each test, (before destructor)
};

// Example "smoke test" (can be deleted)
TEST(GuesserTest, smoke_test)
{
  Guesser object("Secret");
  ASSERT_EQ( 1+1, 2 );
}

//Wrong match
TEST(GuesserTest, match)
{
	Guesser object("Secret");
	int match = object.match("Secretpassword");
	
	ASSERT_EQ(0,match);
}

//Locked after brute force guess
TEST(GuesserTest, brute_false_match)
{
	Guesser object("Secret");
	int match = object.match("Secretpassword");
	//int lock = object.match("Secret");
	ASSERT_FALSE(object.match("Secret"));
}

//Locked after 3 guesses
TEST(GuesserTest, guess_locked) 
{
	Guesser object("Secret");
	object.match("Secret1");
	object.match("Secret2");
	object.match("Secret3");
	ASSERT_FALSE(object.match("Secret"));
}

//Reset remaing to 3 after correct 
//guess
TEST(GuesserTest, remaining_locked)
{
	Guesser object("Secret");
	object.match("Secret1");
	object.match("Secret2");
	//Should match and reset remaining
	object.match("Secret");
	int count = object.remaining();
	ASSERT_EQ(3,count);
}

//Cut secret to 32 if over 32 char
TEST(GuesserTest, over_32) 
{
	Guesser object("123456789012345678901234567890123");
	ASSERT_TRUE(object.match("12345678901234567890123456789012"));
}

//Still counting down guesses after
//locking
TEST(GuesserTest, locked_countdown) 
{
	Guesser object("Secret");
	object.match("Secret1234");
	object.match("Secret1");
	int count = object.remaining();
	ASSERT_EQ(1,count);
}

//Should allow 3 guesses
//if not locked 
TEST(GuesserTest, No_lock)
{
	Guesser object("Secret");
	object.match("Secret1");
	object.match("Secret2");
	ASSERT_TRUE(object.match("Secret"));
}

