/*
 * File: huffman.h
 * Project: future stream
 * Created Date: Saturday March 30th 2019
 * Author: DaGai  <binghan2836@163.com>
 * -----
 * Last Modified: Sunday March 31st 2019 10:20:11 am
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
#include <memory>
#include <string>
#include <sstream>

#include <iostream>

template <const int KWay,class Type>
struct HuffmanNode
{
    typedef unsigned int WeightType;
    typedef Type ValueType;//define huffman held value type

    /**
     * @brief Construct a new Huffman Node object
     * 
     */
    HuffmanNode():weight(0),value(ValueType()){}

    /**
     * @brief Construct a new Huffman Node object
     * 
     * @param w 
     * @param v 
     */
    HuffmanNode(WeightType w,ValueType v):weight(w),value(v){}
    
    unsigned int weight;
    HuffmanNode *links[KWay];
    HuffmanNode *parents;

    Type value;
};


template <const int KWay,class Ty>
class Huffman
{
    
    typedef HuffmanNode<KWay,Ty> NodeItem;
    typedef std::unique_ptr<NodeItem> Node;
    typedef typename NodeItem::WeightType WeightType;
    typedef typename NodeItem::ValueType ValueType;//define huffman held value type
    
    static const int _dimension = KWay;
    typedef std::priority_queue<Node,std::vector<Node>,std::greater<Node> > Sorter;
    Sorter sorter;
public:
    static const int GetDimension() {return _dimension;}
    void Insert(WeightType weight,ValueType value);

    NodeItem* Build();

    void Delete();

    std::string ToString();//display form small to large, sorted by weight in Huffman node

private:
    Node GetNode();

    /**
     * @brief Get the Padding Length, need to keep it be a full tree.
     * 
     * @return int 
     */
    typename Sorter::size_type GetPaddingLength();

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
	struct less<HuffmanNode<KWay,Type> *>
	{
        //typedef HuffmanNode<KWay,Type> Type;
		bool operator()(const HuffmanNode<KWay,Type>* n1, const HuffmanNode<KWay,Type>* n2) const
		{	// apply operator< to operands
			return n1->weight < n2->weight;
		}
	};
}

template <const int KWay,class Ty>
typename Huffman<KWay,Ty>::Node Huffman<KWay,Ty>::GetNode()
{
    if(!sorter.empty())
    {
        return std::move(const_cast<Node &>(sorter.top()));
    }
    else
    {
        return nullptr;
    }
    
}


template <const int KWay,class Ty>
void Huffman<KWay,Ty>::Insert(WeightType weight,ValueType value)
{
    sorter.push(Node(new NodeItem(weight,value)));
}

template <const int KWay,class Ty>
std::string Huffman<KWay,Ty>::ToString()
{
    std::stringstream  str;
    while(!sorter.empty())
    {
        /**
         * @brief this way can cut off const attribute, and a right value move 
         * 
         */
        Node i(std::move(const_cast<Node &>(sorter.top())));
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
typename Huffman<KWay,Ty>::NodeItem* Huffman<KWay,Ty>::Build()
{
    typename Sorter::size_type size = sorter.size();

    typename Sorter::size_type pad = GetPaddingLength();

    //add some default nodes to ensure this is a full kway tree.
    while(pad)
    {
        sorter.push(Node(new NodeItem()));
        pad --;
    }
    Node node = GetNode();
    while(node)

    return nullptr;
}
