## Primitive Types

### SqlPrimitive
Is basic representation of any type in SQL Tables.
It contains methods for converting to and from bytes and string.

If you want to create your own type, you should create a class that inherits from PrimitiveType.

Methods:
* toBytes() - returns byte representation of the SqlInt
* toString() - returns string representation of the SqlInt

Now these methods are not implemented yet

* * *

### SqlInt

Inherits from PrimitiveType.

It's size by default is 32 bits(4 bytes) and it supports all of standart operations like +, -, *, /, <, >, =, ==.
First byte contains sign and others are used for storing the value.
Value 00000000 is equal to 0.
Value 10000000 is equal to 0 too.

It tries to simulate the behaviour of integers in c++, so It can performo perations that are supported by c++ integers(+, -, *, /,+=, -=, *=, /=, %, &=, <, >, <=, >=, =, ==, !=, ++, --).

It can be casted to int.

Methods:

* toInt() - returns int representation of the SqlInt
* Abs(SqlInt value) - returns absolute value of the SqlInt

* * *

### SqlFloat

Inherits from PrimitiveType.

It's size by default is 64 bits(8 bytes) and it supports all of standart operations, that are supported by mine SqlInt, except %, %=, ++, --.
Inside it contains a common fraction.

There are two SqlInts inside it, one for storing denumerator and one for storing numerator.


* * *