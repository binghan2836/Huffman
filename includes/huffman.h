/*
 * File: huffman.h
 * Project: future stream
 * Created Date: Saturday March 30th 2019
 * Author: DaGai  <binghan2836@163.com>
 * -----
 * Last Modified: Saturday March 30th 2019 2:21:16 pm
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

//
template <const int KWay,class Type>
struct HuffmanNode
{
    int weight;
    Type value;
    HuffmanNode left[KWay];
    HuffmanNode *parents;
};


template <const int KWay,class Ty>
class Huffman
{
    static const int _dimension = KWay;

public:
    typedef Ty ValueType;//define huffman held value type
    typedef HuffmanNode<KWay,Ty> NodeType;

    static const int GetDimension() {return _dimension;}
    void Insert();
    void Delete();
};