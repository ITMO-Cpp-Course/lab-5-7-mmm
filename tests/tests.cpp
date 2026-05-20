#include "documentbuilder.hpp"
#include "invertedindex.hpp"
#include <catch2/catch_all.hpp>

TEST_CASE("Adding documents and basic search", "[index][add][search]")
{
    InvertedIndex index;
    auto doc = DocumentBuilder::build(1, "test1.txt", "hello world");
    index.add_document(std::move(doc));

    SECTION("Search for an existing word")
    {
        auto result = index.search("hello");
        REQUIRE(result.size() == 1);
        REQUIRE(result.count(1) == 1);
    }

    SECTION("Search for a missing word")
    {
        auto result = index.search("sixseven");
        REQUIRE(result.empty());
    }
}

TEST_CASE("Accurate counting of occurrences and normalization of the register", "[index][count][token]")
{
    InvertedIndex index;
    auto doc = DocumentBuilder::build(1, "test2.txt", "Cat, cat! And again cat.");
    index.add_document(std::move(doc));

    SECTION("Counting words in lowercase")
    {
        REQUIRE(index.get_word_count("cat", 1) == 3);
    }

    SECTION("Query for a word that is not in the document")
    {
        REQUIRE(index.get_word_count("puck", 1) == 0);
    }
}

TEST_CASE("Deleting documents from the index", "[index][remove]")
{
    InvertedIndex index;
    auto doc1 = DocumentBuilder::build(1, "doc1.txt", "apple banana");
    auto doc2 = DocumentBuilder::build(2, "doc2.txt", "banana orange");

    index.add_document(std::move(doc1));
    index.add_document(std::move(doc2));

    REQUIRE(index.search("banana").size() == 2);

    SECTION("Complete document deletion and word clearing")
    {
        index.remove_document(1);
        auto res_banana = index.search("banana");

        REQUIRE(res_banana.size() == 1);
        REQUIRE(res_banana.count(2) == 1);
        REQUIRE(res_banana.count(1) == 0);

        REQUIRE(index.search("apple").empty());
    }
}