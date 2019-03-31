/*
 * File: huffman.h
 * Project: future stream
 * Created Date: Saturday March 30th 2019
 * Author: DaGai  <binghan2836@163.com>
 * -----
 * Last Modified: Sunday March 31st 2019 3:01:58 pm
 * Modified By:   the developer formerly known as DaGai
 * -----
 * MIT License
 * 
 * Copyright (c) 2019 binghan2836@163.com
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is furnished to do
 * so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 * -----
 * HISTORY:
 * Date          By    Comments
 * ----------    ---    ----------------------------------------------------------
 */
#include "config.h"
#include <queue>
#include <vector>
#include <memory>
#include <string>
#include <sstream>
#ifdef OUTPUT2CONSOLE
#include <iostream>
#endif
#include <assert.h>

template <const int KWay,class Type>
struct HuffmanLeaf
{
    typedef unsigned int WeightType;
    typedef Type ValueType;//define huffman held value type
    typedef HuffmanLeaf*(*LinkType);

    WeightType weight;
    ValueType value;
public:
    /**
     * @brief Construct a new Huffman Item object
     * 
     */
    HuffmanLeaf():weight(0),value(ValueType()){}
    /**
     * @brief Construct a new Huffman Item object
     * 
     * @param w 
     * @param v 
     */
    HuffmanLeaf(WeightType w,ValueType v):weight(w),value(v){}
    /**
     * @brief Destroy the Huffman Leaf object virtual destruct function
     * 
     */
    virtual ~HuffmanLeaf(){}
    virtual LinkType GetLinks(){return NULL;}

    WeightType GetWeight(){return weight;}    
    ValueType  GetValue(){return value;}
};


template <const int KWay,class Type>
struct HuffmanNode:public HuffmanLeaf<KWay,Type>
{
    HuffmanLeaf<KWay,Type> *links[KWay];

    HuffmanNode():HuffmanLeaf<KWay,Type>(){}

    HuffmanNode(typename HuffmanLeaf<KWay,Type>::WeightType w):
    HuffmanLeaf<KWay,Type>(w, typename HuffmanLeaf<KWay,Type>::ValueType()){}

    /**
     * @brief Get the Links object
     * 
     * @return * HuffmanLeaf[] 
     */
    typename HuffmanLeaf<KWay,Type>::LinkType GetLinks(){return links;}
};

template <const int KWay,class Ty>
class Huffman
{
public:
    //give Leaf define to user.
    typedef HuffmanLeaf<KWay,Ty> Leaf;
private:
    typedef HuffmanNode<KWay,Ty> Node;
    typedef std::unique_ptr<Leaf> Item;
    typedef typename Leaf::WeightType WeightType;
    typedef typename Leaf::ValueType ValueType;//define huffman held value type
    
    static const int _dimension = KWay;

    /**
     * @brief sort all node as ascending order
     * 
     */
    typedef std::priority_queue<Item,std::vector<Item>,std::greater<Item> > Sorter;
    Sorter sorter;
    /**
     * @brief This vector will hold all node in running context. and will destrcut and release space when app over.
     * 
     */
    typedef std::vector<Item> Container;
    Container container;
public:
    static const int GetDimension() {return _dimension;}
    void Insert(WeightType weight,ValueType value);

    Leaf* Build();

    void Delete();

    std::string ToString();//display form small to large, sorted by weight in Huffman node

private:

    Item GetNode();

    /**
     * @brief Get the Padding Length, need to keep it be a full tree.
     * 
     * @return int 
     */
    typename Sorter::size_type GetPaddingLength();

    /**
     * @brief Create a New Item object
     * 
     * @param it
     * @return Item 
     */
    Item CreateNewNode(typename Container::iterator it);
};


namespace std
{
    /**
     * @brief overload less compare, or only to compare pointor address.
     * 
     * @tparam KWay 
     * @tparam Type 
     */
    template <const int KWay,class Type>
	struct less<HuffmanLeaf<KWay,Type> *>
	{
		bool operator()(const HuffmanLeaf<KWay,Type>* n1, const HuffmanLeaf<KWay,Type>* n2) const
		{	// apply operator< to operands
			return n1->weight < n2->weight;
		}
	};
}

template <const int KWay,class Ty>
typename Huffman<KWay,Ty>::Item Huffman<KWay,Ty>::GetNode()
{
    if(!sorter.empty())
    {
        Item itme(std::move(const_cast<Item &>(sorter.top())));
        sorter.pop();
        return std::move(itme);
    }
    else
    {
        return nullptr;
    }
    
}

template <const int KWay,class Ty>
void Huffman<KWay,Ty>::Insert(WeightType weight,ValueType value)
{
    sorter.push(Item(new Leaf(weight,value)));
}

template <const int KWay,class Ty>
std::string Huffman<KWay,Ty>::ToString()
{
    std::stringstream  str;
    while(!sorter.empty())
    {
        /**
         * @brief this way can cut off const attribute, and a right value move behavor
         * 
         */
        Item i(std::move(const_cast<Item &>(sorter.top())));
        str << "weight: " << i->weight << "  value " << i->value << std::endl;
        sorter.pop();
    }

    return str.str();
}

template<const int KWay,class Ty>
typename Huffman<KWay,Ty>::Sorter::size_type Huffman<KWay,Ty>::GetPaddingLength()
{
    switch (GetDimension())
    {
        case 2:
            return 0;
        default:
            {
                typename Sorter::size_type size = sorter.size();
                typename Sorter::size_type tmp = size - GetDimension();
                /**
                 * @brief get how many pad nodes we need 
                 * 
                 */
                return (tmp % (GetDimension() -1));
            }
    }
}

template <const int KWay,class Ty>
typename Huffman<KWay,Ty>::Item Huffman<KWay,Ty>::CreateNewNode(typename Huffman<KWay,Ty>::Container::iterator it)
{
    Node* node = new Node();

    Leaf* leaf = nullptr;
    for(int i = 0;i < GetDimension(); i++)
    {
        /**
         * @brief a little fuzzy, it pointor to a node, node pointor to nodeitem
         * 
         */
        leaf = (*(it +i)).get();
        node->links[i] = leaf;
        node->weight += leaf->weight;
        std::cout << leaf->weight << "  ";
    }
    std::cout << node->weight << " \n";
    return Item(std::move(node));
}

template <const int KWay,class Ty>
typename Huffman<KWay,Ty>::Leaf* Huffman<KWay,Ty>::Build()
{
    if(!sorter.size())
    {
        return nullptr;
    }

    //add some default nodes to ensure this is a full kway tree.
    typename Sorter::size_type pad = GetPaddingLength();
    std::cout << "pad " << pad;
    while(pad)
    {
        sorter.push(Item(new Leaf()));
        pad --;
    }
    
    //continue to create other nodes
    int loop = ((sorter.size()) - GetDimension())/(GetDimension() - 1) + 1;
    std::cout << " loop " << loop  << " size " << sorter.size() << "\n";
    for(int i = 0; i < loop;i++)
    {
        std::cout << "loop " << i << ":\n";
        for(int j =0;j <  GetDimension();j++)
        {
            Item tmp(std::move(GetNode()));
            assert(tmp);
            if(tmp)
            {
                container.push_back(std::move(tmp));
            }
        }
        typename Container::iterator it = container.begin();
        sorter.push(std::move(CreateNewNode(it + i * GetDimension())));
    }

    //get root
    assert(sorter.size() == 1);

    Item root = GetNode();

    Leaf *leaf = root.get();
    container.push_back(std::move(root));

    return leaf;
}
