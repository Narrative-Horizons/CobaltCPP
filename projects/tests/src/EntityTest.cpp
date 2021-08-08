#include <gtest/gtest.h>

#include <cobalt/entities/entity.hpp>

struct TestComponent
{
	TestComponent()
		: TestComponent(0)
	{
	}

	TestComponent(int value)
		: value(value)
	{
	}

	int value;
};

TEST(EntityTest, EqualityBothDefault)
{
	using cobalt::Entity;

	Entity lhs;
	Entity rhs;

	ASSERT_EQ(lhs, rhs);
}

TEST(EntityTest, EqualitySameFromRegistry)
{
	using cobalt::Entity;
	using cobalt::Registry;

	Registry r;
	Entity lhs = r.create();
	Entity rhs = lhs;

	ASSERT_EQ(lhs, rhs);
}

TEST(EntityTest, InequalityNotSameFromRegistry)
{
	using cobalt::Entity;
	using cobalt::Registry;

	Registry r;
	Entity lhs = r.create();
	Entity rhs = r.create();

	ASSERT_NE(lhs, rhs);
}

TEST(EntityTest, InequalityNotSameFromRegistryAndDefault)
{
	using cobalt::Entity;
	using cobalt::Registry;

	Registry r;
	Entity lhs = r.create();
	Entity rhs;

	ASSERT_NE(lhs, rhs);
}

TEST(EntityTest, InequalityNotSameDefaultAndFromRegistry)
{
	using cobalt::Entity;
	using cobalt::Registry;

	Registry r;
	Entity lhs;
	Entity rhs = r.create();

	ASSERT_NE(lhs, rhs);
}

TEST(RegistryTest, CreateSingleEntity)
{
	using cobalt::Registry;

	Registry r;
	auto ent = r.create();

	ASSERT_EQ(r.alive(), 1);
}

TEST(RegistryTest, CreateThenDestroy)
{
	using cobalt::Registry;

	Registry r;
	auto ent = r.create();
	
	r.release(ent.id());

	ASSERT_EQ(r.alive(), 0);
}

TEST(RegistryTest, CreateDefaultCheckContains)
{
	using cobalt::Registry;

	Registry r;

	auto ent = r.create();
	ASSERT_FALSE(r.contains<TestComponent>(ent.id()));
	ASSERT_FALSE(ent.contains<TestComponent>());
}

TEST(RegistryTest, CreateDefaultAssignDefaultFromEntity)
{
	using cobalt::Registry;

	Registry r;

	auto ent = r.create().assign(TestComponent());

	ASSERT_TRUE(r.contains<TestComponent>(ent.id()));
	ASSERT_TRUE(ent.contains<TestComponent>());

	ASSERT_EQ(ent.get<TestComponent>().value, 0);
}

TEST(RegistryTest, CreateDefaultAssignValueFromEntity)
{
	using cobalt::Registry;

	Registry r;

	auto ent = r.create().assign(TestComponent(1));

	ASSERT_TRUE(r.contains<TestComponent>(ent.id()));
	ASSERT_TRUE(ent.contains<TestComponent>());

	ASSERT_EQ(ent.get<TestComponent>().value, 1);
}

TEST(RegistryTest, CreateDefaultAssignDefaultFromRegistry)
{
	using cobalt::Registry;

	Registry r;

	auto ent = r.create();
	r.assign(ent.id(), TestComponent());

	ASSERT_TRUE(r.contains<TestComponent>(ent.id()));
	ASSERT_TRUE(ent.contains<TestComponent>());

	ASSERT_EQ(ent.get<TestComponent>().value, 0);
}

TEST(RegistryTest, CreateAssignThenRemoveFromEntity)
{
	using cobalt::Registry;

	Registry r;

	auto ent = r.create();
	ent.assign(TestComponent());

	ASSERT_TRUE(r.contains<TestComponent>(ent.id()));
	ASSERT_TRUE(ent.contains<TestComponent>());

	ent.remove<TestComponent>();

	ASSERT_FALSE(r.contains<TestComponent>(ent.id()));
	ASSERT_FALSE(ent.contains<TestComponent>());
}

TEST(RegistryTest, CreateAssignThenRemoveFromRegistry)
{
	using cobalt::Registry;

	Registry r;

	auto ent = r.create();
	r.assign(ent.id(), TestComponent());

	ASSERT_TRUE(r.contains<TestComponent>(ent.id()));
	ASSERT_TRUE(ent.contains<TestComponent>());

	r.remove<TestComponent>(ent.id());

	ASSERT_FALSE(r.contains<TestComponent>(ent.id()));
	ASSERT_FALSE(ent.contains<TestComponent>());
}

TEST(RegistryTest, CreateAssignTheReassignFromEntity)
{
	using cobalt::Registry;

	Registry r;

	auto ent = r.create().assign(TestComponent());

	ASSERT_TRUE(r.contains<TestComponent>(ent.id()));
	ASSERT_TRUE(ent.contains<TestComponent>());

	ASSERT_EQ(ent.get<TestComponent>().value, 0);

	ent.assign(TestComponent(1));

	ASSERT_TRUE(r.contains<TestComponent>(ent.id()));
	ASSERT_TRUE(ent.contains<TestComponent>());

	ASSERT_EQ(ent.get<TestComponent>().value, 1);
}

TEST(RegistryTest, CreateAssignTheReassignFromRegistry)
{
	using cobalt::Registry;

	Registry r;

	auto ent = r.create();
	r.assign(ent.id(), TestComponent());

	ASSERT_TRUE(r.contains<TestComponent>(ent.id()));
	ASSERT_TRUE(ent.contains<TestComponent>());

	ASSERT_EQ(r.get<TestComponent>(ent.id()).value, 0);

	ent.assign(TestComponent(1));

	ASSERT_TRUE(r.contains<TestComponent>(ent.id()));
	ASSERT_TRUE(ent.contains<TestComponent>());

	ASSERT_EQ(ent.get<TestComponent>().value, 1);
}

TEST(RegistryTest, CreateReplaceContainsFromEntity)
{
	using cobalt::Registry;

	Registry r;

	auto ent = r.create().assign(TestComponent());

	ASSERT_TRUE(r.contains<TestComponent>(ent.id()));
	ASSERT_TRUE(ent.contains<TestComponent>());

	ASSERT_EQ(ent.get<TestComponent>().value, 0);

	ent.replace(TestComponent(1));

	ASSERT_TRUE(r.contains<TestComponent>(ent.id()));
	ASSERT_TRUE(ent.contains<TestComponent>());

	ASSERT_EQ(ent.get<TestComponent>().value, 1);
}

TEST(RegistryTest, CreateReplaceContainsFromRegistry)
{
	using cobalt::Registry;

	Registry r;

	auto ent = r.create();
	r.assign(ent.id(), TestComponent());

	ASSERT_TRUE(r.contains<TestComponent>(ent.id()));
	ASSERT_TRUE(ent.contains<TestComponent>());

	ASSERT_EQ(r.get<TestComponent>(ent.id()).value, 0);

	r.replace(ent.id(), TestComponent(1));

	ASSERT_TRUE(r.contains<TestComponent>(ent.id()));
	ASSERT_TRUE(ent.contains<TestComponent>());

	ASSERT_EQ(r.get<TestComponent>(ent.id()).value, 1);
}

TEST(RegistryTest, CreateReplaceDoesNotContainFromEntity)
{
	using cobalt::Registry;

	Registry r;

	auto ent = r.create();

	ASSERT_FALSE(r.contains<TestComponent>(ent.id()));
	ASSERT_FALSE(ent.contains<TestComponent>());

	ent.replace(TestComponent(1));

	ASSERT_FALSE(r.contains<TestComponent>(ent.id()));
	ASSERT_FALSE(ent.contains<TestComponent>());
}

TEST(RegistryTest, CreateReplaceDoesNotContainFromRegistry)
{
	using cobalt::Registry;

	Registry r;

	auto ent = r.create();

	ASSERT_FALSE(r.contains<TestComponent>(ent.id()));
	ASSERT_FALSE(ent.contains<TestComponent>());

	ent.replace(TestComponent(1));

	ASSERT_FALSE(r.contains<TestComponent>(ent.id()));
	ASSERT_FALSE(ent.contains<TestComponent>());
}

TEST(RegistryTest, TryGetContains)
{
	using cobalt::Registry;

	Registry r;

	auto ent = r.create().assign(TestComponent());

	ASSERT_TRUE(ent.contains<TestComponent>());

	ASSERT_NE(ent.tryGet<TestComponent>(), nullptr);
	ASSERT_EQ(ent.tryGet<TestComponent>()->value, 0);
}

TEST(RegistryTest, TryGetDoesNotContain)
{
	using cobalt::Registry;

	Registry r;

	auto ent = r.create();

	ASSERT_FALSE(ent.contains<TestComponent>());

	ASSERT_EQ(ent.tryGet<TestComponent>(), nullptr);
}
