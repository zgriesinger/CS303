#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include "Book.h"
#include "Binary_Search_Tree.h"
#include "omp.h"

using namespace std;

class Customer
{
public:
    Customer(int a_id, string a_name) : ID(a_id),name(a_name)
    {
        reviews.assign(251, 0); // Fill the vector with 0s to make changing items at indices easier CHANGE FOR PRES 251
        user_similarity.assign(10, 0); // Same as above 10
    }
    Customer() {}

    void set_rating(string ISBN, int rating, vector<Book>& books)
    {
        // We search for the given ISBN and set the rating of that book to be the rating given.
        for (int i = 0; i < books.size(); i++)
        {
            if (books[i].get_isbn() == ISBN)
            {
                //cout << ISBN << " " << books[i].get_isbn() << endl;
                reviews[i] = rating;
                books[i].set_review(rating, ID);
                return;
            }
        }
    }
    void calculate(vector<Customer>& customers, vector<Book>& books)
    {
        // Exact same as the book.h calculate but we are passing in the customers vector
        
        for (int i = 0; i < customers.size(); i++)
        {
            user_similarity[i] = calculate_cosine_sim(reviews, customers[i].get_reviews());
        }

        find_n_greatest(user_similarity, most_similar_users, 3);
        // This is where I will do some improvement to do the algorithm better, I will need to user average rating and max/mins
        int count = 1;
        for (int i = 0; i < 3; i++)
        {
            vector<int> closest_user_reviews = customers[most_similar_users[i]].get_reviews();
            for (int j = 0; j < reviews.size(); j++)
            {
                if ((closest_user_reviews[j] == 4 || closest_user_reviews[j] == 5) && (reviews[j] == 5 || reviews[j] == 4))
                {
                    if (books[j].get_closest_book() == -1)
                    {
                        continue;
                    }
                    vector<int> closest_book_indices;
                    find_n_greatest(books[j].get_book_similarity(), closest_book_indices, 10); //change for pres

                    for (int k = 0; k < closest_book_indices.size(); k++)
                    {
                        if (reviews[closest_book_indices[k]] == 0)
                        {
                            Recommended_Books.insert(closest_book_indices[k]);
                            count++;
                        }
                    }
                }
            }
        }



    }
    bool RecommendBooks(vector<Book>& books) // Acts as the wrapper function for the inorder traversal TraverseBooks()
    {
        if (Recommended_Books.getRoot() == NULL)
        {
            return false;
        }
        BTNode<int>* root = Recommended_Books.getRoot();
        int count = 1;
        TraverseBooks(books, root, count);
        return true;
        
    }

    void TraverseBooks(vector<Book>& books, BTNode<int>* root, int& count)
    {
        if (root == NULL)
            return;
        TraverseBooks(books, root->left, count);
        cout << count++ << ". " << books[root->data].get_title() << endl;
        TraverseBooks(books, root->right, count);
    }

    int get_id()
    {
        return ID;
    }

    string get_name()
    {
        return name;
    }

    vector<double> get_user_similarity()
    {
        return user_similarity;
    }

    vector<int> get_reviews()
    {
        return reviews;
    }

    void print_reviews()
    {
        for (int i = 0; i < reviews.size(); i++)
        {
            cout << reviews[i];
        }
        cout << endl;
    }
	
private:
    int ID;
    string name;
    vector<int> reviews;
    vector<double> user_similarity;
    vector<int> most_similar_users;
    Binary_Search_Tree<int> Recommended_Books;
};
