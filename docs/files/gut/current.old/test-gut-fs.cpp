#include "gut.h"
#include "gut-fs.h"

TEST("return true on the same file") {
	CHECK(gut::fs::areTextFileEqual("file1.txt", "file1.txt"));
	CHECK(gut::fs::areTextFileEqual("file2.txt", "file2.txt"));
}

TEST("return true on identical files") {
	CHECK(gut::fs::areTextFileEqual("file1.txt", "file1-copy.txt"));
}

TEST("return false on different files") {
	CHECK(!gut::fs::areTextFileEqual("file1.txt", "file1-partial.txt"));
	CHECK(!gut::fs::areTextFileEqual("file1-partial.txt", "file1.txt"));
	CHECK(!gut::fs::areTextFileEqual("file1.txt", "file1-without-trailing-empty-line.txt"));
	CHECK(!gut::fs::areTextFileEqual("file1-without-trailing-empty-line.txt", "file1.txt"));
	CHECK(!gut::fs::areTextFileEqual("file1.txt", "file2.txt"));
	CHECK(!gut::fs::areTextFileEqual("file2.txt", "file1.txt"));
}

TEST("return false on an empty vs. non-empty files") {
	CHECK(!gut::fs::areTextFileEqual("file1.txt", "empty.txt"));
	CHECK(!gut::fs::areTextFileEqual("empty.txt", "file1.txt"));
}

TEST("return false if a file does not exist") {
	CHECK(!gut::fs::areTextFileEqual("file1.txt", "file_.txt"));
	CHECK(!gut::fs::areTextFileEqual("file_.txt", "file1.txt"));
}

TEST("return true if the string matches a whole line") {
	CHECK(gut::fs::contains("file1.txt", "Lorem ipsum dolor sit amet, consectetur adipiscing elit."));
}

TEST("return false if the string does not match a whole line") {
	CHECK(!gut::fs::contains("file1.txt", "Lorem ipsum dolor sit amet"));
}

TEST("return falise if a file does not contain the string") {
	CHECK(!gut::fs::contains("file1-partial.txt", "Lorem ipsum dolor sit amet"));
}

