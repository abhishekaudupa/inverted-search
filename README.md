# Inverted Search

An inverted index is a database index storing a mapping from content, such as words or numbers, to its locations in a table, or in a document or a set of documents. The purpose of an inverted index is to allow fast full-text searches, at a cost of increased processing when a document is added to the database. The inverted file may be the database file itself, rather than its index. It is the most popular data structure used in document retrieval systems, used on a large scale for example in search engines. Additionally, several significant general-purpose mainframe-based database management systems have used inverted list architectures.

There are two main variants of inverted indexes: A **record-level inverted index** (or **inverted file index** or just **inverted file**) contains a list of references to documents for each word. A **word-level inverted index** (or **full inverted index** or **inverted list**) additionally contains the positions of each word within a document. The latter form offers more functionality, but needs more processing power and space to be created.

[Wikipedia Article](https://en.wikipedia.org/wiki/Inverted_index)

This project implements the former.
