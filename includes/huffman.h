/*
 * File: huffman.h
 * Project: future stream
 * Created Date: Saturday March 30th 2019
 * Author: DaGai  <binghan2836@163.com>
 * -----
 * Last Modified: Saturday March 30th 2019 8:38:22 pm
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

    HuffmanNode(WeightType w,ValueType v):weight(w),value(v){}
    
    unsigned int weight;
    HuffmanNode *links[KWay];
    HuffmanNode *parents;

    Type value;
};


template <const int KWay,class Ty>
class Huffman
{
    
    typedef HuffmanNode<KWay,Ty> NodeType;
    typedef std::unique_ptr<NodeType> Node;
    typedef typename NodeType::WeightType WeightType;
    typedef typename NodeType::ValueType ValueType;//define huffman held value type
    
    static const int _dimension = KWay;
    std::priority_queue<Node,std::vector<Node>,std::greater<Node> > container;
public:
    static const int GetDimension() {return _dimension;}
    void Insert(WeightType weight,ValueType value);
    void Delete();

    std::string ToString();//display form small to large, sorted by weight in Huffman node

private:
    Node GetNode();
};

namespace std
{
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
    if(!container.empty())
    {
        return std::move(const_cast<Node &>(container.top()));
    }
    else
    {
        
        return nullptr;
    }
    
}


template <const int KWay,class Ty>
void Huffman<KWay,Ty>::Insert(WeightType weight,ValueType value)
{
    container.push(Node(new NodeType(weight,value)));
}

template <const int KWay,class Ty>
std::string Huffman<KWay,Ty>::ToString()
{
    std::stringstream  str;
    while(!container.empty())
    {
        //here need a right value behavor.
        //ugly, but can work
        Node i(std::move(const_cast<Node &>(container.top())));

        str << "weight: " << i->weight << "  value " << i->value << std::endl;
        container.pop();
    }

    return str.str();
}