/*
 * File: huffman_test.cc
 * Project: future stream
 * Created Date: Saturday March 30th 2019
 * Author: DaGai  <binghan2836@163.com>
 * -----
 * Last Modified: Sunday March 31st 2019 4:47:49 pm
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

#include "huffman.h"
#include <string>
#include <iostream>
#include <memory>
#include "gtest/gtest.h"
#include "parse.h"
TEST(HffmanTest, CreateNode)
{
    Huffman<2,char>  huff2;
    EXPECT_TRUE(huff2.GetDimension()==2);

    Huffman<3,char>  huff3;
    EXPECT_TRUE(huff3.GetDimension()==3);
}

template<class Ty>
void InsertNode(Ty &huf)
{
    huf.Insert((unsigned int)100,'A');

    huf.Insert((unsigned int)20,'B');

    huf.Insert((unsigned int)56,'C');

    huf.Insert((unsigned int)67,'D');
}


TEST(HffmanTest, Insert)
{
    Huffman<3,char> huf;

    InsertNode(huf);
    std::string str = huf.ToString();
    std::cout << str.c_str();
    EXPECT_TRUE(str == "weight: 20  value B\nweight: 56  value C\nweight: 67  value D\nweight: 100  value A\n");    
}

TEST(HuffmanTest, Build)
{
    Huffman<3,char> huf;

    InsertNode(huf);

    Huffman<3,char>::Leaf *leaf = huf.Build();

    EXPECT_TRUE(leaf->GetWeight() == 243);
}

const char * SONNET = 
"When I do count the clock that tells the time,\n"
"And see the brave day sunk in hideous night,\n"
"When I behold the violet past prime,\n"
"And sable curls all silver'd o'er with white,\n"
"When lofty trees I see barren of leaves,\n"
"Which erst from heat did canopy the herd,\n"
"And summer's green, all girded up in sheaves,\n"
"Born on the bier with white and bristly beard,\n"
"Then of thy beauty do I question make,\n"
"That thou among the wastes of time must go,\n"
"Since sweets and beauties do themselves forsake,\n"
"And die as fast as they see others grow,\n"
"And nothing 'gainst Time's scythe can make defence,\n"
"Save breed, to brave him when he takes thee hence.\n";

TEST(ParseContent,Parse)
{
    Parse parse;
    parse.Statistics("aaaaddddhhhh");

    std::string str = parse.ToString();
    std::cout << str.c_str() << "\n";

    EXPECT_TRUE(str == "a, 4\nd, 4\nh, 4\n");
}


//Octous test
TEST(ParseContent,BuildHuffman)
{
    Parse parse;
    parse.Statistics(SONNET);

    Huffman<8,char> huf;

    parse.Create(huf);

    Huffman<8,char>::Leaf *leaf = huf.Build();
    EXPECT_TRUE(627 == leaf->GetWeight());
}